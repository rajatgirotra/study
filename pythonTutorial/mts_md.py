#!/usr/bin/env python

import argparse
import os
# import sys
# import threading
from multiprocessing import Process, Queue
import tempfile
import subprocess as sp
import datetime
import glob
import re


def get_exlusions(source, weeksprior):
    exclusionList = []
    allPaths = glob.glob(source + '/*.md.gz')
    allFiles = [os.path.basename(x) for x in allPaths]
    # print (allFiles)

    # get current date
    today = datetime.date.today()
    # get trade date based on weeksprior
    beginDate = today - datetime.timedelta(weeks=weeksprior)
    beginDateInt = int(beginDate.strftime('%Y%m%d'))

    # exclude all files older than bot
    pattern = '(?i).*\.(\d{8})\.md.gz$'
    prog = re.compile(pattern)
    for file in allFiles:
        result = prog.match(file)
        if (result is None):
            print('File %s is not a market data file. Putting in exclusionList'
                  % file)
            exclusionList.append(file)
        else:
            fileDate = int(result.group(1))
            if (fileDate < beginDateInt):
                print('File %s is older than %i. Putting in exclusionList'
                      % (file, beginDateInt))
                exclusionList.append(file)

    # print(exclusionList)
    return exclusionList


def synchronize_do(source, destination, exclusionList, q):
    try:
        returnList = []
        # temporary file to log synchronization activity
        file = tempfile.NamedTemporaryFile(mode='w+', delete=False)

        cmd = 'rsync '
        options = ' -azh --progress --size-only --log-file='
        logFile = file.name
        options += logFile
        options += ' '
        for excludeFile in exclusionList:
            options += ' '
            options += ' --exclude '
            options += excludeFile
        # options += ' --exclude'
        options += ' '
        # options += ' --exclude '.join(exclusionList)
        options += ' '
        options += '--delete-excluded'
        options += ' '
        options += os.path.join(source, '')
        options += ' '
        options += os.path.join(destination, '')

        cmd += options
        print (cmd)

        # execute rsync
        try:
            output = sp.check_output(cmd, shell=True, universal_newlines=True,
                                     stderr=sp.STDOUT)
            returnList.insert(0, True)
            returnList.insert(1, output)
            returnList.insert(2, file.name)
        except sp.CalledProcessError:
            returnList.insert(0, False)
            returnList.insert(1, output)
            returnList.insert(2, file.file)
    except:
        returnList.insert(0, False)
        returnList.insert(1, 'Unexpected error occurred during\
                  market data synchronization to destination %s' % destination)
        returnList.insert(2, file.name)
    finally:
        q.put(returnList)


if (__name__ == "__main__"):
    # create argument parser and parse sys.argv
    parser = argparse.ArgumentParser(
        description='Synchronize market data/tick data across machines')

    # add arguments to the parser
    parser.add_argument('--source', required=True)
    parser.add_argument('-d', '--destination', nargs='+')
    parser.add_argument('-w', '--weeksprior', default=10, type=int)

    # parse
    args = parser.parse_args()

    # get files to exclude during synchronization
    exclusionList = get_exlusions(args.source, args.weeksprior)

    # for each destination,
    # create a separate thread of execution to synchronize market data
    destMap = {}
    for dest in args.destination:
        q = Queue()
        p = Process(target=synchronize_do,
                    args=(args.source, dest, exclusionList, q))
        destMap[p] = (dest, q)
        p.start()

    # print(destMap)
    for process, destination in destMap.items():
        dest = destination[0]
        retList = destination[1].get()
        process.join()
        assert(len(retList) >= 3)
        if(retList[0] is False):
            print('Market Data Synchronization Failed for destination %s' % dest)
            #print('Error %s and File %s' % (retList[1], retList[2]))
        retList[2].close()

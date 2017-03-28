#!/usr/bin/env python

import logging
import logging.handlers
import sys

# # very simple, by default, logging api logs message to the console
# # also by default, logging level is set to WARNING, so all INFO and DEBUG
# # level logs will not be printed.
# logging.warning('This is a warning message')
# logging.info('This is an info message')


# # to log to a disk file, use the logging.basicConfig function
# # read the documentation on python.org. Also all the logging functions
# # like logger.info(), logger.debug() etc call basicConfig first.
# # the basicConfig function ensures that there is atleast one handler attached
# # to the logger before any calls to logger.info(), logger.debug(). Otherwise
# # if there is no handler attached to the logger, events will not be processed.
# # after the first call to basicConfig, all subsequent calls are NO-OP.
# # Also in some version of python, there is a shortcoming by which if multiple threads
# # start logging simlutaneously, then the basicConfig() function gets called multiple
# # time's which attached multiple handlers to the logger. So the same event gets logged
# # multiple times. So best is to call basicConfig upfront before starting any threads.
# # Also you already know about the different objects in the python logging API.
# # You have Logger Objects, then you have Handlers attached to loggers,
# # then you have Formatter classes (each handler will have a formatter class),
# # then you have LogRecords and also Filters, you'll learn about them soon.
# # to run the next 4 lines of code, you'll need to comment the top 2, as the
# # basicConfig would have already run as part of the first logging statement.
# # by default, basicConfig creates a StreamHandler with a default Formatter
# # which logs to the sys.stderr
# logging.basicConfig(filename='example.log', level=logging.DEBUG)
# logging.debug('This message should go to the log file example1')
# logging.info('So should this to example1')
# logging.warning('And this, too to example1')

# a good option is to get the logger level from command line as an argument
# --logLevel=INFO etc. We use python build-in function getAttr() function.
# For a class X with a member(read attribute) foo, getAttr() will return value
# of x.foo
# Similar to above, you'll need to comment all lines above to run the next set
# of statements.
# loglevel=sys.argv[1]
# numeric_level = getattr(logging, loglevel.upper(), None)
# if not isinstance(numeric_level, int):
#     raise ValueError('Invalid log level: %s' % loglevel)
# logging.basicConfig(filename='example2.log', level=numeric_level, filemode='w') #filemode='w' will discard old log file
# logging.debug('This message should go to the log file example2')
# logging.info('So should this example2')
# logging.warning('And this, too example2')
# logging.warning('%s C style format printing %d', 'Hello', 5)

# using a particular format of message can also be configured easily in the basicConfig function
# Look at attributes of LogRecord class. You have a no. of options
# on what you can configure in the format.
# logging.basicConfig(format='%(levelname)s:%(asctime)s:%(lineno)d:%(message)s', level=logging.DEBUG)
# logging.debug('This message should appear on stdout')

# The python logging tutorial is a good example of setting up logging
# Its shows a workflow of how logging is done. Very informative. Based on that information
# we can configure logging. Below is just a sample from there.
# create logger
logger = logging.getLogger('simple_example')
logger.setLevel(logging.DEBUG)

#create a Console handler and set level to debug
ch = logging.handlers.RotatingFileHandler('example.log', mode='w', maxBytes=(5*1024*1024), backupCount=5)
ch.setLevel(logging.INFO)

#create formatter
args = ('RajatGirotra', 5)
print(args)

formatter = logging.Formatter(fmt='%(asctime)s:%(levelname)s:%(filename)s:%(module)s:%(name)s:%(message)s',\
                              datefmt='%H:%M:%S')
ch.setFormatter(formatter)


logger.addHandler(ch)

def foo():
    raise ValueError('dummy value error')


d = {'user_defined':'someUDText'}

try:
    logger.debug    ('Debug Message')
    logger.info     ('Info Message')
    logger.warn     ('Warn Message')
    logger.error    ('Error Message')
    logger.critical ('Critical Message')
    logger.critical ('Critical Message:%s %d', *args, extra=d)
    #logger.debug    ('Debug Message'   ,  *args, extra=d)
    #logger.info     ('Info Message'    ,  *args, extra=d)
    #logger.warn     ('Warn Message'    ,  *args, extra=d)
    #logger.error    ('Error Message'   ,  *args, extra=d)
    #logger.critical ('Critical Message',  *args, extra=d)
    #logger.critical ('Critical Message:%s %d', *args, extra=d)
    foo()
except:
    logger.exception('exception has occurred')
    #logger.error('exception has occurred', *args, exc_info=True, extra=d)
    #stack_info is supported from python 3.2 onwards.
    #logger.error('exception has occurred', *args, exc_info=True, stack_info=True, extra=d)


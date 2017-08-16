import logging
import logging.handlers
import os

def _setupLogging():
    #print('setting up logging')
    #logging.basicConfig(filename='module.log',level=logging.DEBUG)    
    logger = logging.getLogger() # will return you the root logger.
    #print ('in __init__.py, name is %s' %  __name__)
    logger.setLevel(logging.INFO)
    fileHandler = logging.handlers.RotatingFileHandler(
        'module.log', mode='a', maxBytes=5*1024, backupCount=100)
    formatter = logging.Formatter('%(asctime)s %(levelname)s %(filename)s %(funcName)s %(threadName)s: %(message)s')
    fileHandler.setFormatter(formatter)
    logger.addHandler(fileHandler)

_setupLogging()
print(os.path.abspath(__file__))

import logging
import logging.handlers


def setupLogging():
    print('setting up logging')
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)
    fileHandler = logging.handlers.RotatingFileHandler(
        'module.log', mode='a', maxBytes=5*1024, backupCount=100)
    formatter = logging.Formatter('%(asctime)s %(levelname)s %(filename)s %(funcName)s %(threadName)s: %(message)s')
    fileHandler.setFormatter(formatter)
    logger.addHandler(fileHandler)

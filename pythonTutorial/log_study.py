import logging


logging.basicConfig(filename='app.log', filemode='a', level=logging.DEBUG, format='%(asctime)s %(message)s')

logging.debug('This is a debug level message')
logging.info('This is a info level message')
logging.warn('This is a warn level message')
logging.error('This is a error level message')
logging.critical('This is a critical level message')

import logging
from logging.config import dictConfig


LOG_SETTINGS = {
    'version': 1,
    'root': {
        'level': 'NOTSET',
        #'handlers': ['console', 'file', 'smtp', 'mongodb'],
        'handlers': ['console', 'file'],
    },
    'handlers': {
        'console': {
            'class': 'logging.StreamHandler',
            'level': 'INFO',
            'formatter': 'detailed',
            'stream': 'ext://sys.stdout',
        },
        'file': {
            'class': 'logging.handlers.RotatingFileHandler',
            'level': 'INFO',
            'formatter': 'detailed',
            'filename': 'MyProject.log',
            'mode': 'a',
            'maxBytes': 10485760,
            'backupCount': 5,
        },
        'smtp': {
            'class': 'logging.handlers.SMTPHandler',
            'level': 'ERROR',
            'formatter': 'email',
            'mailhost': 'localhost',
            'fromaddr': 'alerts@calazan.com',
            'toaddrs': ['admin@calazan.com', 'support@calazan.com'],
            'subject': '[My Project] Error encountered.',
        },
#        'mongodb': {
#            'class': 'log4mongo.handlers.MongoHandler',
#            'level': 'DEBUG',
#            'host': 'localhost',
#            'port': 27017,
#            'database_name': 'myproject',
#            'collection': 'logs',
#            'username': 'logger',
#            'password': 'password',
#        },
    },
    'formatters': {
        'detailed': {
            'format': '%(asctime)s %(module)-17s line:%(lineno)-4d ' \
            '%(levelname)-8s %(message)s',
        },
        'email': {
            'format': 'Timestamp: %(asctime)s\nModule: %(module)s\n' \
            'Line: %(lineno)d\nMessage: %(message)s',
        },
    },
}

log_config = dictConfig(LOG_SETTINGS)

logging.debug('This is a debug message!')
logging.info('This is an info message!')
logging.error('This is an error message!')

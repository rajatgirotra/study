import logtest
import logging

logtest.setupLogging()
logger = logging.getLogger(__name__)


def mainFunc():
    print('in mainFunc', __name__)


mainFunc()

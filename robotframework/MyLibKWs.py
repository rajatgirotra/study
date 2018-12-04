# please read 18_* .txt
# I'll create my own keyword library and try to demonstrate logging and other features

import time
from robot.api.deco import keyword

class MyLibKWs(object):
    """ Make a habit to include some documentation. """

    def __init__(self):
        """ Make a habit to include some documentation. """
        self._name = 'MyLibKWs'

    @keyword('Try to login with username and password', tags=['logintest'])
    def login(self, user, password):
        """ Make a habit to include some documentation. """
        print('*TRACE* TRACE Level Log')
        print('*DEBUG* DEBUG Level Log')
        print('*INFO* INFO Level Log')
        print('*WARN* WARN Level Log')
        print('*ERROR* ERROR Level Log')
        now_ms = time.time() * 1000
        print('*TRACE:%d* TRACE Level Log with timestamp' % now_ms)
        print('*DEBUG:%d* DEBUG Level Log with timestamp' % now_ms)
        print('*INFO:%d* INFO Level Log with timestamp' % now_ms)
        print('*WARN:%d* WARN Level Log with timestamp' % now_ms)
        print('*ERROR:%d* ERROR Level Log with timestamp' % now_ms)

    def example_keyword(argument):
        """*DEPRECATED!!* Use keyword `Other Keyword` instead.

        This keyword does something to given ``argument`` and returns results.
        """
        return None

# the alternate and better approach is to use the robot api logger library. It is much neater.
# from robot.api import logger.
# logger.debug(msg)
# logger.info(msg)

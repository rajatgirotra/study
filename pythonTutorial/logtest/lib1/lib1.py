import logging

_logger = logging.getLogger(__name__)


def foo():
    _logger.critical('Critical log')
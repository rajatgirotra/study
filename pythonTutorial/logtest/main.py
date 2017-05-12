import logging
from .lib1 import lib1

_logger = logging.getLogger(__name__)
_logger.info('From main.py')
print __package__
lib1.foo()

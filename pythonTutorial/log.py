#!/usr/bin/env python

import logging
import logging.handlers
import sys

# # very simple, by default, logging api logs message to the console
# # also by default, logging level is set to WARNING, so all INFO and DEBUG
# # level logs will not be printed.
# logging.warning('This is a warning message')
# logging.info('This is an info message')
# Note that these(debug(), warn(), info()) above are logging module level functions.
# We also have same functions in the logger class.

# Classes in looging API
# Logger, Handlers, Filters and Formatters. 
# Loggers are created using logging.getLogger(__name__)
# Many different type of Handlers exist already. Like RotatingFileHandler, StreamHandler, FileHandler, EmailHandler, SocketHandler etc etc.
# you can attach handlers to loggers using logger.addHandler() and removeHandler().
# Filters can be attached to both handlers and loggers. If even one filter attached to a handler or logger returns false, the log msg will not be output.
# Formatters are attached to handlers using addFormatter and they specify the output format.


# # to log to a disk file, use the logging.basicConfig function
# You can specify the following to basicConfig
# 1) filename - to log to a file
# 2) filemode - to create a new one or append to the existing file
# 3) level - Default level of the root logger.
# 4) dateformat - Format of the date to display in the logs
# and some more arguments.
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

# Logger objects are hierarchical. So
# logging.getLogger('foo.bar.baz') is a child of logging.getLogger('foo.bar')
# Also by default log message are propagted to parent loggers. And we have the root logger at the top of the hierarchy.
# there is not much to say. You have read this several times. We should always let propagate to TRUE and let the root logger
# do all the logging. For any specific logging, you can attach handlers to individual loggers.

# Logger configuration can be done in three ways.
# 1) Using code (addHandler(), addFilter(), addFormatter() type functions)
# 2) using fileConfig(). This is like an .ini file which contains sections on logging options, handlers to use. levels to use, filter formats etc.
# 3) dictConfig() - This is also preferred one. So study it. Just a dict of all the logging options you want to have.

# in all your python scripts/module just say
# import logging
# _logger = logging.getLogger(__name__) and start logging using logger.(debug()|warn()|info()) etc.
# _ in variable means it will not be imported be default when you do "from mymodule import *"

# using a particular format of message can also be configured easily in the basicConfig function
# Look at attributes of LogRecord class. You have a no. of options
# on what you can configure in the format.
# logging.basicConfig(format='%(levelname)s:%(asctime)s:%(lineno)d:%(message)s', level=logging.DEBUG)
# logging.debug('This message should appear on stdout')

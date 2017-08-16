# Very simple. We'll only study dictConfig() and use that always.
# logging.config has a callable called dictConfigClass. by default it is set to DictConfigurtor. This DictConfigurator object is created by passeing the config you have provided, then the configure() method is called. So you can also provide your own Configurator class which must have a configure method.

# in python library, we have
def dictConfig(config):
    dictConfigClass(config).configure()

# Format of the dictConfig is based on a schema. right now only version 1 of the schema is defined by python. dictConfig should be a dictionary with the following keys
# 1) version
# 2) formatters - The value is again a dict where the key is formatter id and value is a dict (we'll call it configuring dict) describing config options.
# 3) handlers - same as formatters
# 4) filters - same as formatters
# 5) loggers - same as formatters
# 6) root - root logger configuration. Same configuring dict as loggers except that the propagate flag will always be false.
# 7) incremental - True if this config is incremental. False otherwise. Default is False.
# 8) disable_existing_loggers - By default is True, which means all other loggers in your modules should be disabled.

# configuring dict keys for:
# 1) formatters - format and datefmt
# 2) filters - name
# 3) handlers - class(fully qualified handler class name), level, formatter(formatter id), filters(filter id)
# 4) loggers - level, propagate, filters, handlers

#example for handlers:
#handlers:
#  console:
#    class : logging.StreamHandler
#    formatter: brief
#    level   : INFO
#    filters: [allow_foo]
#    stream  : ext://sys.stdout
#  file:
#    class : logging.handlers.RotatingFileHandler
#    formatter: precise
#    filename: logconfig.log
#    maxBytes: 1024
#    backupCount: 3

# You formatter, filter, handler configuring dict can have a special key '()': example
#handlers:
#  file:
#    # configuration of file handler goes here
#
#  custom:
#    (): my.package.MyHandler
#    alternate: cfg://handlers.file

#and

#formatters:
#  brief:
#    format: '%(message)s'
#  default:
#    format: '%(asctime)s %(levelname)-8s %(name)-15s %(message)s'
#    datefmt: '%Y-%m-%d %H:%M:%S'
#  custom:
#      (): my.package.customFormatterFactory
#      bar: baz
#      spam: 99.9
#      answer: 42

# in which case python will not create an object of logging.Formtater, logging.Handler, logging.Filter, but rather create an object of a user defined class specified as the value for '()' key and pass all other configuring dict key-value as the c'tor arguments. So example
# my.package.customFormatterFactory(bar='baz', spam=99.9, answer=42) will be called.

from celery import Celery

# create a celery instance
# include is a list of modules to look into for your tasks.
app = Celery('proj', backend='rpc://', broker='pyamqp://', include=['proj.tasks'])

# configure task results to be purged after 3600 second
app.conf.update(
    result_expires=3600,
)

# you can also start Celery workers by executing this python file from the command line
# in this case app.start() will be called. so you can pass command line arguments also
# to celery. The other way of calling celery you've seen already
# celery -A celery_proj worker -l info

# the -A/--app argument can be:
# module.path:attribute (where isinstance(attribute, Celery) must be True OR
# module.path in which case Celery will search for an attribute
# module.path.app OR
# module.path.celery OR
# module.path.<anyAttribute> of type Celery
# module.path.celery.app  ( in our case, this will hit)
# module.path.celery.celery
if __name__ == '__main__':
    if __name__ == "__main__":
        app.start()

# Also note the output when you start a worker. Celery shows you
# The tasks loaded, the number of parallel threads (along with API used),
# the backend, and broker information, the Q info and the events info

# Typically you should always start Celery workers in the background
# read Celery multi module to learn how we can do this

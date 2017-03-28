from celery import Celery

# the first thing we need to do is create a Celery app/instance. A celery app is the main entry point into
# using celery. It can take a plethora of arguments, we'll explore as we learn more.
# the first argument here is the name of the app (usually the name of the python file
# the broker argument is the message broker we want to use
# backend is also a RabbitMQ store (some kind of data store) used to store results of tasks.
app = Celery('tasks', broker='pyamqp://', backend='rpc://')


# creating a simple task
@app.task
def add(x, y):
    return x + y

@app.task
def test_exception():
    raise ValueError('test_exception raised a ValueError')

# After this we can start celery worker which will listen to the message broker Q for tasks request and process
# them To start we use the celery command

# celery help
# celery command help

# celery [GlobalOptions] command [commandOptions]
# start the celery worker using
# celery -A <appNAme> worker --loglevel=info


#read main.py next
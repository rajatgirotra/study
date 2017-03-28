# import tasks created in tasks.py
from tasks import add, test_exception

# schedule a task to be run
result = add.delay(4, 4)
print (type(result))  # celery.result.AsyncResult

# check if result is ready
print ('add result is available (True/False) %s', result.ready())

# calling get will be a blocking call, and will return after the task has executed.
x = result.get(timeout=10)
print ('result of add task is %s', x)
# if you get an exception like AttributeError: 'DisabledBackend' object has no attribute '_get_task_meta_for'
# this means celery worker is running without a backend. You need to enable backend


# get by default will throw the same exception as thrown by your task. You can disable this by setting
# propagate=False
try:
    result = test_exception.delay()
    result = add.delay(4, 4)
    # result.get()  # with no arguments you should see the same exception getting caught as thrown by test_exception
    result.get(propagate=False) # with propagate=False, the exception will not be thrown, but you can access
    # the result.traceback which will give you the exception string if any. Also with propagate resulg.get()
    # will return as usual. If no exception is thrown result.traceback will be None. So by default, it looks
    # like good practice to set propagate to False and always log the exception if traceback is not None
    print(result.ready()) # will return True with propagate=False
except Exception as e:
    print e


# by default, the delay method returns an AsyncResult object, which can be used to
# 1) get the state of the task
# 2) Wait for the task to finish
# 3) get the return value of the callable, or the exception, or timeout error.
# very similar to the way we have in std::promise<>

# also by default, celery needs to be provided a backend (some kind of a store) to store task results
# etc. For backend also, we have multiple options available. We continue to use RabbitMQ as a backend too.

# Read configuration.txt next
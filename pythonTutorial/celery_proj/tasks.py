from .celery import app


# Submitting tasks in Celery is very easy. Three functions are available
# 1) taskName.delay(args)
# 2) taskName.apply_async((tuple_of_args), other_args)
# other args can be like queue name to schedule the task onto, countdown after which task to start etc etc.
# 3) taskName(args) --> to call synchronously.

@app.task
def sum(x, y):
    return x+y


@app.task
def difference(x, y):
    return x-y


@app.task
def mul(x, y):
    return x*y


@app.task
def xsum(*numbers):
    x = 0
    for n in numbers:
        x += n
    return x

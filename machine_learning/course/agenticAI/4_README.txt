Please read upto lab_4 and then this one.
before moving to lab_5, where we start using OpenAI agents SDK, lets just see how coroutines work in python. Why? most of these SDK's provide abstractions over LLM agents call which are very heavy on IO. So these SDK's mostly implement these calls as python coroutines. coroutines are just a way to do cooperative multi tasking in python. Under the hood, there is an event loop which maintains a list of coroutine which is waiting for CPU. It will pick up any coroutine and run it, until the coroutine wants to do some IO work. Then the IO continues but the event loop will pick up the next coroutine to be run on the CPU.

Coroutines are defined using the "async" keyword and they are called using the "await" keyword.

The await keyword in Python is specifically designed to be used within functions defined as asynchronous using the async keyword.
Attempting to use await outside of an async function will result in a SyntaxError.
This restriction is due to how asynchronous programming works in Python. When a function is marked with async, it becomes a coroutine, which is a special type of function that
can be paused and resumed. await is used to pause the execution of a coroutine until the awaited task (usually another coroutine) is complete.
This allows other tasks to run concurrently while the awaited task is pending.
The async keyword signals to the interpreter that the function is designed to work with asynchronous operations and that await will be used. 
Therefore, await is only valid inside these specially marked functions.

async def do_something():
   return "Done"

result = dp_something()  # result will be a coroutine object only. The coroutine is not yet called here.

final_output = await result() # will run your coroutine (when in jupyter notebook)
or
final_output = asyncio.run(result()) # will run your coroutine (inside a python module)

Under the hood, python runs all async functions in an event loop. Whenever, an async function goes to perform some I/O, it will schedule the next async function in the list.


The await keyword is typically only valid inside async functions in Python.
However, Jupyter notebooks and similar interactive environments provide an exception to this rule, allowing the use of await at the top level of a cell. 
This behavior is enabled by the "autoawait" feature, which is a built-in mechanism that automatically wraps top-level await calls within an implicit async context.
This allows you to use asynchronous operations directly in your notebook cells without defining an explicit async function."

In python, you would typically use asyncio.run(<Async function/Coroutine>) to run an coroutine.
But when inside a coroutine, it can use the "await" keyword.
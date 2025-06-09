Please read upto lab_4 and then this one.
before moving to lab_5, where we start using OpenAI agents SDK, lets just see how coroutines work in python. Why? most of these SDK's provide abstractions over LLM agents call which are very heavy on IO. So these SDK's mostly implement these calls as python coroutines. coroutines are just a way to do cooperative multi tasking in python. Under the hood, there is an event loop which maintains a list of coroutine which is waiting for CPU. It will pick up any coroutine and run it, until the coroutine wants to do some IO work. Then the IO continues but the event loop will pick up the next coroutine to be run on the CPU.

Coroutines are defined using the "async" keyword and they are called using the "await" keyword. Example:

async def do_something():
   return "Done"

result = dp_something()  # result will be a coroutine object only. The coroutine is not yet called here.

final_output = await result() # will run your coroutine.

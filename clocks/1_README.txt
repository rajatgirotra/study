About Clocks a.ka. timers
eal 
What is Frequency:
It is just a measure of how frequently an event is occuring per unit of time.
For example: 5 times in a minute, once every hour etc.

Frequency is typically measured in Hertz (HZ). 1 Hz means 1 time in one second.
1000Hz means 1000 times in one second.

A CPU clock speed of 2GHz means  2*1000000000 times (or cycles) per second.

Every system has a system timer (called the Programmable Interval Timer, PIT) which is a programmable piece of hardware that issues an interrupt to the CPU at a fixed frequency.
This fixed frequency comes from the kernel source and is programmed into the hardware.

When the CPU gets interrupted thru the TIMER INTERRUPT it runs the timer interrupt service handler which updates the system time and performs
periodic work. The frequency at which the system timer goes off is called the tick rate. Because the kernel knows the preprogrammed tick rate,
it knows the amount of time passed between two successive interrupts. This time is called a tick ie each time a timer interrupt is raises, it is a tick.
For example, if the kernel knows the pre-programmed tick rate is 1000 (ie frequency configured is 1000 times a second, then the time between each 
interrupt is 1 millisecond). because 1ms * 1000 = 1000 ms = 1s.

The tick rate is a static value defined in kernel source. Eg

#define HZ 1000

With a HZ value of 100, this means that the system time will be updated every 10 ms. That is the maximum resolution that can be provided.
With HZ value of 1000,, this resolution increases to 1ms ie 10 fold better. 
"Resolution" is nothing but the smallest possible increase of time that the clock model allows.
Note the resolution increases by the same factor as the tick rate increases. So if tick rate (ie HZ increases from 100 to 1000 ie by a factor 10
the resolution also increases by the same factor).

Now let say you read a clock repeatedly which has a resolution of 1ms. However, even if you read continuously in a loop. you wont be able to read
values like 2000ms, 2001ms, 2002ms, because CPU will always have lots of work to do. So let say you read a clock 1000 times, and each time you record
the difference in time read last time. So you calculate standard deviation on these values and SAY THAT IS MY PRECISION.
and the average of those values is JITTER.

Jiffies - Just so you know. We dont want to go deeper into it yet. Jiffies is a counter in kernel code used to store the numner of ticks (ie number
of times the timer interrupt has been raised since the system boot time). So it is very easy to calculate the system uptime in seconds.
jiffies / Hz, so simple.

The programmable clocks/timers are implemented typically using a crystal oscillator. You have a register known as the holding register.
The value from the holding register is loaded into the another register. This value is decremented by the oscillator each time it generates
a pulse. When the values reaches zero a timer interrupt is raised and the value from the holding register is loaded again for the next tick.

Real Time Clock or Hardware Clock. - Every system has a real time or hardware clock which is running from a battery source even when the computer 
is switched off. Typically this same battery is also used to store the BIOS settings.

When a system is booted, linux kernel reads the time from this clock into an internal variable called xtime.
After that it normally does not reference the RTC again.

Look at "man hwclock" to play with it. It basically manipulates the /dev/rtc device file.

Not important but good to know that on each interrupt the timer routine will carry out some tasks which are architecture independent and some
which are architecture dependent.
Eg

1) Take a xtime_lock and update the wall clock in xtime variable (xtime is a timespec data structure shown below).
2) Periodically save the wall clock to the RTC
3) Do process scheduling by invoking the scheduler.
4) Calculate the load average etc.
5) Run any dynamic timers (kernel timers that may have expired).
6) It might do some profiling by updating the performance counters

The wall clock is held by the kernel in a data structure called timespec

struct timespec
{
    time_t tv_sec; //second from epoch
    long tv_nsec; //nanoseconds passed in the current second.
};


What are the time sources in OS

1) Typically the APIC timer (Async Programmable Interrupt Controller)
2) The CPU TSC (timestamp counters).

In kernel code many times you need to defer executing some code for a later time. For that, kernel supports dynamic timers which is just a data structure
to keep track of 1) What time we need to scheule something, 2) What function to call etc etc.
These are kernel timers and are very popular in kernel programming.
We'll read more about them in a bit.

Now Linux Kernel can be configured at boot time to use any clock source described in 2_README.txt

To see what all clock source are available: do
cat /sys/devices/system/clocksource/clocksource0/available_clocksource
tsc hpet acpi_pm

To see what is the current clock source : do
cat /sys/devices/system/clocksource/clocksource0/current_clocksource

To set a new clock source, do:
echo hpet > /sys/devices/system/clocksource/clocksource0/current_clocksource

You should always use tsc as the clock source as it provides highest resolution
to configure it at boot time, add the following to grub.conf
clocksource=tsc

There were two problems with the tsc clocks in older CPU's

1) Each CPU had its own TSC, so each could have its own value sligtly different from others.
   So in order to benchmark code, you always had to pin your code to the same CPU
2) When the CPU power management code kicked in to save power, it altered the CPU frequency
   thereby altering the rate at which the TSC counter was ticking.

But both these problems are fixed in more recent kernel. Do:

cat /proc/cpuinfo | grep tsc
If it shows constant_tsc : It means TSC is synchronized across all cores in the system
If it show invariant_tsc : It means it ticks at a constant speed regardless of the CPU powermanagement code.

But Now how do you get time in user space??

You can use the clock_gettime() function which makes a system call into the kernel to get the time.


The clock_gettime() functions takes a clock id. The different values are shown below.
Remember each of these CLOCK id's will eventually use one hardware counter listed in 2_README.txt


CLOCK_REALTIME : System wide clock to get wall clock time. Subject to NTP adjustments. Ie. it
                 can jump backward or forward (stepped) and have its frequency adjusted (slewed) to match that of the NTP upstream servers.
                 CLOCK_REALTIME uses TSC normally.
CLOCK_REALTIME_COARSE: A lower resolution version of CLOCK_REALTIME

CLOCK_MONOTONIC : A clock that represents time from an arbitrary point (typically the system boot time).
                  Cannot be stepped by slewed due to NT adjustements. Ie it cannot move backwards but can have some frequenct adjustments.
                  CLOCK_MONTONIC uses HPET typically
CLOCK_MONOTONIC_RAW: A strictly increasing clock that cannot be slewed or stepped.
CLOCK_MONOTONIC_COARSE : A lower resolution version of CLOCK_MONOTONIC

CLOCK_PROCESS_CPUTIME_ID : A high resolution per process timer from CPU. This also uses TSC but gives the time taken by the process on that CPU.
CLOCK_THREAD_CPUTIME_ID : A thread specific CPU time clock. Same as above but gives the Time consumed by the thread.

We'll explore these in a while.

So this is how it works

1) Application calls clock_gettime(CLOCK_REALTIME)
2) glibc makes a system call into the kernel
3) kernel calls sys_clock_gettime()
4) sys_clock_gettime() calls getnstimeofday()
5) getnstimeofday() would return the added combination of xtime and __get_nsec_offset()
6) __get_nsec_offset() reads the clocksource hardware (in this case the TSC) and returns the time since xtime was last updated.

TSC is now any day better than HPET as:

1) TSC provides much smaller resolution than HPET
2) Its much cheaper (in terms of CPU cost) to read TSC than HPET, that's why TSC is preferred.
3) HPET was said to be more reliable than TSC because of the two problems TSC had but now
   with both resolved, it is a clear winner or HPET.

Also linux provides another function gettimeofday() which is implemented in user space vdso library (vsyscall method), and avoids a system call.
So prefer gettimeofday() to clock_gettime() as clock_gettime() will go into kernel

Basically kernel maps a page of code and a page of data out as user-readable, and userland executes it directly, avoiding the syscall overhead).

Lets next execute the clock_gettime() and gettimeofday() functions.

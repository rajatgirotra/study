All x86 microprocessors have a CLK (Clock) input pin, which received a clock signal from an external oscillator.
These microprocessors have a 64 bit Timestamp counter (TSC) which is increased at each clock signal.
This timer can be read using the rdtsc/rdtscp instruction.

The value in the TSC register depends on the clock signal, if the clock frequency is 1GHz, then the counter is incremented once per nanosecond.

You have seen that the PIT(Programmable Interrupt Timer) provides a resolution of upto 1ms with HZ configured at 1000.
So Linux now takes advantage of this CPU TSC counter to get a more accurate time measurement.

Basically There are multiple clock sources Linux can use to keep track of time.

1) PIT : You have already read about it in 1_README.txt. With a value of 1000 as HZ, resolution is 1ms
2) HPET: Hardware developed jointly be Intel and Microsoft called High Precesion Event Timer. This has a frequency of atleast
         10 Mhz, ie 10000000 Hz (10 to the power 7 times in one second), so resolution is 100 ns. HPET will completely replace PIT going forward.
3) Then you have ACPI_PM (the ACPI power management timer). Its frequency is fixed at 3.58 Mhz. So resolution is
   1000000000/3580000 = 279 nanosec.
4) And finally the CPU TSC timer. Resolution is based on Clock Speed. If clock speed is 1GHZ, resolution is 1ns
   and if clock speed is 2 GHZ, then resolution is 0.5 nanoseconds.

All the above are called as hardware counters and linux must use one of these finally to get keep track of time.

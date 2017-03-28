These days, network speeds have gone up tremendously.
Before we had 10Mb/s to 1Gb/s network speeds.
Now 10Gb/s (10 Gigabits/sec) speeds are pretty normal. This puts a lot of pressure on the system CPU, because CPU's
now have to deal with a lot of TCP/IP network traffic and do stuff like

1) handling our of order packets
2) making resource intensive copies of data from kernel to user space
3) handling the protocol headers
4) handling interrupts.

Linux system are by default not configured for high network speed scenarios, so have to be fine tuned.
If you dont your system could be processing a lot of work just doing I/O rather than application processing.
So the overall system throughput can be limited.

This is a vast topic, so I'll try to explain as much as I can how we can fine tune some of the system settings
to increase 

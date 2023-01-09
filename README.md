# ECE1175_Lab5
Lab 5 project for Embedded Systems class

Use the sysfs pseudo-filesystem to interact with the Linux kernel and manipulate Raspberry Pi CPU frequencies on the fly.

Hint: For more information about the sysfs pseudo-filesystem, please refer to the manual page: sysfs(5) (http://man7.org/linux/man-pages/man5/sysfs.5.html).

Use the information provided by sysfs to find out the available CPU frequencies allowed by the hardware. How many logical cores are there on your Raspberry Pi? What is the maximum CPU frequency supported by your Raspberry Pi? What about the minimum frequency supported?
Use the information provided by sysfs to find out the available CPU frequency governors on your system. What are the meanings of those governors? How will they affect the CPU frequencies? Please try with the following governors: "performance", "powersave" and "ondemand" and demonstrate how they impact the CPU frequency under different workload.
Use the interfaces provided by sysfs to set your Raspberry Pi to be running at certain CPU frequency. Specifically, please demonstrate that you may lock the CPU frequency to either the maximum frequency or the minimum frequency.
Show that the same amount of workload takes different amount of time to finish under different CPU frequencies.

Implement a customized userspace CPU frequency governor.

Please read through the description part of a Linux kernel patch email at https://lkml.org/lkml/2016/3/17/420 Links to an external site. carefully and understand how the newly-added "schedutil" frequency scaling governor initially works. We will mimic their way of using CPU utilization information as input for making CPU frequency decisions, except that everything happen in userspace rather than kernel space.
Assume that the CPU utilization information provided by the Raspberry Pi is frequency-invariant. The coefficient we use is the same as described in the lkml email.
Implement a custom userspace CPU frequency governor by specifying the "userspace" mode governor in sysfs and keep your program running in the background. Your userspace governor should periodically read system CPU utilization information and calculate the next_freq value based on that. To set the desired frequency, find out the nearest available CPU frequency as allowed by your Raspberry Pi and use the interfaces provided by sysfs to set the frequency.
Enable your custom CPU frequency governor on Raspberry Pi and test it with different workloads.

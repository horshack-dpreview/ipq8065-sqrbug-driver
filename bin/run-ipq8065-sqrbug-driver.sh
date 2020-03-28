#!/bin/sh

#
# Driver-based version of CPU load integrity test that fails on my
# Netgear X4S R7800.
#
# Command-line options:
#
# CountIterations=xxxx  [default = 50000]
# Flags=xxxxxxxx
#	Bit 0 - Don't perform yield() in between iterations
#	Bit 1 - Perform each iteration inside a local_irq_disable() block 
#
echo Running ipq8065-sqrbug-driver until it fails or 1000 successful iterations
dmesg -c > /dev/null
n=1
until [ $n -ge 1000 ]
do
    echo "Test iteration $n"
    insmod ./ipq8065-sqrbug-driver.ko "$@" 2>/dev/null
    dmesg | grep -q "ipq8065-sqrbug-driver: Mismatch"
    if [ $? -eq 0 ]; then
	dmesg
        break
    fi
    n=$((n+1))
done


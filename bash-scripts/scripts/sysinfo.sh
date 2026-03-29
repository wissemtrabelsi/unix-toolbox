#!/bin/bash

# System information report - works on Linux and macOS
echo "== CPU =="
if [[ "$OSTYPE" == "darwin"* ]]; then
    sysctl -n machdep.cpu.brand_string
    sysctl -n hw.cpufrequency 2>/dev/null || echo "Frequency: N/A"
else
    grep "Model name" /proc/cpuinfo | head -n 1 | cut -d ":" -f2
    grep "MHz" /proc/cpuinfo | head -n 1 | cut -d ":" -f2
fi

echo "== Memory =="
if [[ "$OSTYPE" == "darwin"* ]]; then
    vm_stat | grep "Pages free"
    sysctl -n hw.memsize | awk '{print $1/1024/1024/1024 " GiB total"}'
else
    free -h
fi

echo "== Disk Space (/) =="
df -h /

echo "== /home Partition =="
df -h /home 2>/dev/null || echo "No /home partition found"

echo "== Running Processes =="
ps aux | wc -l

echo "== OS and Kernel =="
uname -a
#!/bin/bash
pid=21870
interval=5
while true
do
    echo -n $(date +"%y-%m-%d_%H:%M:%S") >> proc_memlog.txt
    echo -n "  " >> proc_memlog.txt 
    cat /proc/$pid/status |grep -e VmRSS >> proc_memlog.txt
    echo $blank >> proc_memlog.txt
    sleep $interval
done

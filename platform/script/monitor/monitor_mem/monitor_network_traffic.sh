#!/bin/bash
#把带宽bit单位转换为人类可读单位
bit_to_human_readable(){
    #input bit value
    local trafficValue=$1

    if [[ ${trafficValue%.*} -gt 922 ]];then
        #conv to Kb
        trafficValue=`awk -v value=$trafficValue 'BEGIN{printf "%0.1f",value/1024}'`
        if [[ ${trafficValue%.*} -gt 922 ]];then
            #conv to Mb
            trafficValue=`awk -v value=$trafficValue 'BEGIN{printf "%0.1f",value/1024}'`
            echo "${trafficValue}Mb"
        else
            echo "${trafficValue}Kb"
        fi
    else
        echo "${trafficValue}b"
    fi
}
#实时流量
realTimeTraffic(){
    local eth=$1
    local clear=true
    local eth_in_peak=0
    local eth_out_peak=0
    local eth_in=0
    local eth_out=0

    while true;do
        echo -n "$eth--------Now--------Peak-----------" >> $2".log"
        echo  `date +"%Y-%m-%d_%H:%M:%S"` >> $2".log"
        traffic_be=(`awk -v eth=$eth -F'[: ]+' '{if ($0 ~eth){print $3,$11}}' /proc/net/dev`)
        sleep $3
        traffic_af=(`awk -v eth=$eth -F'[: ]+' '{if ($0 ~eth){print $3,$11}}' /proc/net/dev`)
        #计算速率
        eth_in=$(( (${traffic_af[0]}-${traffic_be[0]})*8/$3 ))
        eth_out=$(( (${traffic_af[1]}-${traffic_be[1]})*8/$3 ))
        #计算流量峰值
        [[ $eth_in -gt $eth_in_peak ]] && eth_in_peak=$eth_in
        [[ $eth_out -gt $eth_out_peak ]] && eth_out_peak=$eth_out
        printf "%-20s %-20s\n" "Receive:  $(bit_to_human_readable $eth_in)" "$(bit_to_human_readable $eth_in_peak)" >> $2".log"
        printf "%-20s %-20s\n" "Transmit: $(bit_to_human_readable $eth_out)" "$(bit_to_human_readable $eth_out_peak)" >> $2".log"
    done
}
main(){
    realTimeTraffic eth0 traffic_em1 10
}
main


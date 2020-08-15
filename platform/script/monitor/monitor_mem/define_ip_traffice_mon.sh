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
#流量和连接概览
trafficAndConnectionOverview(){
    local reg=""
    #eth 网卡名
    local eth=$1
    local select_ip=$3
    local out_file=$2
    echo `date +%Y-%m-%d_%H:%M:%S`"  start collect network traffic info 10s" >>$out_file
    echo -e "\n" >> $out_file
    #当前流量值
    local traffic_be=(`awk -v eth=$eth -F'[: ]+' '{if ($0 ~eth){print $3,$11}}' /proc/net/dev`)
    #tcpdump监听网络
    tcpdump -v -i $eth -tnn > /tmp/tcpdump_temp 2>&1 &
    sleep 10
    kill `ps aux | grep tcpdump | grep -v grep | awk '{print $2}'`

    #10s后流量值
    local traffic_af=(`awk -v eth=$eth -F'[: ]+' '{if ($0 ~eth){print $3,$11}}' /proc/net/dev`)
    #打印10s平均速率
    local eth_in=$(( (${traffic_af[0]}-${traffic_be[0]})*8/10 ))
    local eth_out=$(( (${traffic_af[1]}-${traffic_be[1]})*8/10 ))
    echo "network device $eth average traffic in 10s:" >> $out_file
    echo "$eth Receive: $(bit_to_human_readable $eth_in)/s" >> $out_file
    echo "$eth Transmit: $(bit_to_human_readable $eth_out)/s" >> $out_file

    local regTcpdump=$(ifconfig | grep -A 1 $eth | awk -F'[: ]+' '$0~/inet addr:/{printf $4"|"}' | sed -e 's/|$//' -e 's/^/(/' -e 's/$/)\\\\\.[0-9]+:/')

    #新旧版本tcpdump输出格式不一样,分别处理
    if awk '/^IP/{print;exit}' /tmp/tcpdump_temp | grep -q ")$";then
        #处理tcpdump文件
        awk '/^IP/{print;getline;print}' /tmp/tcpdump_temp > /tmp/tcpdump_temp2
    else
        #处理tcpdump文件
        awk '/^IP/{print}' /tmp/tcpdump_temp > /tmp/tcpdump_temp2
        sed -i -r 's#(.*: [0-9]+\))(.*)#\1\n    \2#' /tmp/tcpdump_temp2
    fi
    awk '{len=$NF;sub(/\)/,"",len);getline;print $0,len}' /tmp/tcpdump_temp2 > /tmp/tcpdump

    #统计在10s内占用带宽最大的前10个ip
    b_count=0
    echo -e "ip average traffic in 10s base on server:" >> $out_file
    awk -F'[ .:]+' -v regTcpdump=$regTcpdump '{if ($0 ~ regTcpdump){line=$2"."$3"."$4"."$5" > "$8"."$9"."$10"."$11":"$12}else{line=$2"."$3"."$4"."$5":"$6" > "$8"."$9"."$10"."$11};sum[line]+=$NF*8/10}END{for (line in sum){printf "%s %d\n",line,sum[line]}}' /tmp/tcpdump | grep $select_ip > /tmp/tmp_calc.log
    while read a b c d;do
        b_count=`expr $b_count + $d`
        echo "$a $b $c $(bit_to_human_readable $d)/s" >> $out_file
    done</tmp/tmp_calc.log
    echo "IP "$select_ip" on server all count = $(bit_to_human_readable $b_count)/s" >> $out_file
    echo -e "\n" >> $out_file
    b_count=0
    echo -e "ip average traffic in 10s base on client:" >> $out_file
    awk -F'[ .:]+' -v regTcpdump=$regTcpdump '{if ($0 ~ regTcpdump){line=$2"."$3"."$4"."$5":"$6" > "$8"."$9"."$10"."$11}else{line=$2"."$3"."$4"."$5" > "$8"."$9"."$10"."$11":"$12};sum[line]+=$NF*8/10}END{for (line in sum){printf "%s %d\n",line,sum[line]}}' /tmp/tcpdump | grep $select_ip > /tmp/tmp_calc.log
    while read a b c d;do
        b_count=`expr $b_count + $d`
        echo "$a $b $c $(bit_to_human_readable $d)/s" >> $out_file
    done</tmp/tmp_calc.log
echo "IP "$select_ip" on client all count = $(bit_to_human_readable $b_count)/s" >>$out_file
    echo -e "\n" >> $out_file
}

main(){
    while true; do
       trafficAndConnectionOverview eth0 ip_define.log $1
       sleep 1
    done
}
if [ $# -ne 1 ]; then
   echo "please input IP:PORT"
else
main $1
fi

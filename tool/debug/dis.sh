#!/bin/bash
##############################################
# Filename: dis.sh
# Desc:     disassemble a function
# Author:   yumin.gao
##############################################
 
routine=$1
func=$2
 
if [ -z "$routine" ]; then
    exit
fi
 
start=$(nm -n $routine | grep "$func" | awk '{print "0x"$1}')
end=$(nm -n $routine | grep -A1 "$func" | awk '{getline; print "0x"$1}')
 
if [ -z "$func" ]; then
    objdump -d $routine
else
    echo "start-address: $start, end-address: $end"
    objdump -d $routine --start-address=$start --stop-address=$end
fi

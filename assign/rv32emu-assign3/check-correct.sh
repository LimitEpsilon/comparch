#!/bin/bash

for order in 2 4 8 16
do             
    for major in col row
    do
        for cache_type in dir set
        do
            EMU_PROG=mat-$major$order
            NATIVE_PROG=native-mat-$major$order
            echo "[+] Compare: [./$NATIVE_PROG] vs. [./emu-rv32i-$cache_type-cache ./$EMU_PROG]"
            diff <(./$NATIVE_PROG) <(./emu-rv32i-$cache_type-cache ./$EMU_PROG|awk /./|grep -a -v ">>>") >/dev/null
            if [ $? != 0 ]
            then
                echo "[-] FAIL: Execution results seem to be wrong for [./emu-rv32i-$cache_type-cache $EMU_PROG]."
                exit -1
            fi
        done
    done
done

echo "[+] PASS: All execution results seem to be correct!"
exit 0

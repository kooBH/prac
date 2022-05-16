#!/bin/bash

list="$(ps -aux)"

#echo "$list"


echo "----------- 1 -"
while read -r p; do
  if grep -q "cuda:1" <<< $p; then
    a=${p[0]}
    idx=0
    for i in $a; do
      if [ $idx -eq 1 ]
        then
#          echo $i
           sudo kill -9 $i
      fi
      idx=$(($idx+1))
    done
  fi
done <<<"$list"
echo "------------3"

#echo =======





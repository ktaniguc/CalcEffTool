#!/bin/bash

alllist=$1
name=${alllist%.*}
DIR="/home/kayamash/CalcEffToollist/"$name
if [[ ! -d "$DIR" ]]; then
    mkdir -p "$DIR"
fi
cd $DIR
echo "cd to "$DIR

cp "/home/kayamash/CalcEffToollist/"$alllist .
#split -l 1 -a 3 -d --verbose $alllist ${name}"div"
split -l 10 -a 3 -d $alllist ${name}"div"

rm $alllist

echo "rename file"
for filename in ${name}*;do
    mv ${filename} ${filename}.list;
done
echo "finish!"



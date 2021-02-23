#!/bin/bash

execute="./run.sh"
for filenumber in {000..028};do
    sed -i -e "s/div000/div${filenumber}/g" run.sh
    sed -i -e "s/div000/div${filenumber}/g" CalcEffAlg_options.py
    eval $execute
    sleep 10s
    sed -i -e "s/div${filenumber}/div000/g" run.sh
    sed -i -e "s/div${filenumber}/div000/g" CalcEffAlg_options.py
done

#sed -i -e "s/data18_349327/mc16_426336/g" run.sh
#sed -i -e "s/data18_349327/mc16_426336/g" CalcEffAlg_options.py
#for filenumber in {000..104};do
#    sed -i -e "s/div000/div${filenumber}/g" run.sh
#    sed -i -e "s/div000/div${filenumber}/g" CalcEffAlg_options.py
#    eval $execute
#    sleep 1m
#    sed -i -e "s/div${filenumber}/div000/g" run.sh
#    sed -i -e "s/div${filenumber}/div000/g" CalcEffAlg_options.py
#done

#sed -i -e "s/mc16_426366/data18_349327/g" run.sh
#sed -i -e "s/mc16_426366/data18_349327/g" CalcEffAlg_options.py

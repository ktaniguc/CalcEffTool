#!/bin/sh

LIST=$1
ITE=$2
EXCLUDEDSITE=ANALY_BNL_LONG,ANALY_BNL_SHORT

#./getgrl.sh

for INPUT in `cat $LIST`;
do
  echo $INPUT
  OUTPUT=$INPUT
  OUTPUT=`echo ${OUTPUT} | sed -e "s:user.yyazawa.user.yyazawa:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:user.yyazawa.mc15_13TeV:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:mc15_13TeV:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_5TeV:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_hi:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_13TeV:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data16_13TeV:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:valid1:user.yyazawa:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.DAOD_MUON0.:.YYTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.recon.AOD.:.YYTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.merge.AOD.:.YYTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.AOD.:.YYTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:_EXT0::g"`

  OUTPUT=${OUTPUT/\//}_$ITE 
  echo $OUTPUT
  pathena CalcEffAlg_options.py \
  --inDS=${INPUT} \
  --outDS=${OUTPUT} \
  --nFilesPerJob=1 \
  --maxCpuCount=86400 \
  --mergeOutput \
  --extOutFile=test.root
done
  
# --destSE=TOKYO-LCG2_LOCALGROUPDISK \
# --excludedSite=${EXCLUDEDSITE} \
# --dbRelease=LATEST 

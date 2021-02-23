#!/bin/sh

LIST=$1
ITE=$2
#EXCLUDEDSITE=ANALY_BNL_LONG,ANALY_BNL_SHORT
EXCLUDEDSITE=BNL,ANALY_BNL_LONG,ANALY_BNL_SHORT,ANALY_CERN,ANALY_BU_ATLAS_Tier2_SL6,ANALY_CONNECT,ANALY_OU_OCHEP_SWT2,ANALY_AUSTRALIA,ANALY_SLAC,INFN,ANALY_RHUL_SL6,ANALY_TAIWAN,ANALY_TOKYO_ARC
#./getgrl.sh

for INPUT in `cat $LIST`;
do
  if [ "$INPUT" = "" ] ; then
    echo "skip $INPUT"
    continue
  fi
  echo $INPUT
  OUTPUT=$INPUT
  #OUTPUT=`echo ${OUTPUT} | sed -e "s:ktaniguc:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:user.ynoguchi:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:mc15_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:mc16_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_5TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_hi:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data15_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data16_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data17_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:data18_13TeV:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:valid1:user.ktaniguc:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.DAOD_MUON0.:.KTTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.recon.AOD.:.KTTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.merge.AOD.:.KTTAP.:g"`
  OUTPUT=`echo ${OUTPUT} | sed -e "s:.AOD.::g"`
  #OUTPUT=`echo ${OUTPUT} | sed -e "s:_EXT0::g"`

  OUTPUT=${OUTPUT/\//}_$ITE 
  echo $OUTPUT
  pathena CalcEffAlg_optionsGrid.py \
  --inDS=${INPUT} \
  --outDS=${OUTPUT} \
  --nFilesPerJob=10 \
  --maxCpuCount=86400 \
  --excludedSite=${EXCLUDEDSITE} \
  --extOutFile=test.root \
  --destSE=TOKYO-LCG2_LOCALGROUPDISK 
done
  
# --dbRelease=LATEST  
#  --mergeOutput \   # maybe available
#  /gpfs/fs2001/ynoguchi/PandaRun/CMake/pathena CalcEffAlg_optionsGrid.py \ #no longer work
#  --athenaTag=Athena,21.0.77  #do not use when you setup Athena

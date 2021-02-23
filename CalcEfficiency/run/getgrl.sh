#!/bin/sh


while getopts t: flag
do
  case $flag in
  t)
    if [ $OPTARG = "2016pF" ]; then
      LUMI=15019.8
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v81-pro20-10_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "2016pG" ]; then
      LUMI=18862.6
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v82-pro20-11_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "2016pI" ]; then
      LUMI=24799.9
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v82-pro20-13_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "2016pK" ]; then
      LUMI=27031.3
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v83-pro20-14_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "2016ALL" ]; then
      LUMI=33257.2
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "LATEST" ]; then
      LUMI=33257.2
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "NOMINAL" ]; then
      LUMI=33257.2
      GRLNAME=data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
    elif [ $OPTARG = "2015" ]; then
      LUMI=3368.33
      GRLNAME=data15_13TeV.periodAllYear_DetStatus-v75-repro20-01_DQDefects-00-02-02_PHYS_StandardGRL_All_Good_25ns.xml
    fi
    ;;
  esac
done

if [ -z $GRLNAME ]; then
  echo "Automatically set 2016ALL as the NOMINAL choice"
  LUMI=33257.2
  GRLNAME=data16_13TeV.periodAllYear_DetStatus-v83-pro20-15_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml
fi

echo "TARGET GRL: $GRLNAME ( $LUMI /pb )"
wget http://atlasdqm.web.cern.ch/atlasdqm/grlgen/All_Good/$GRLNAME
mv $GRLNAME ./current_grl.xml


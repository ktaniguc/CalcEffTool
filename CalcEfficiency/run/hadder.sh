#!/bin/sh

TYPE=YYTAP
ID=jpzv70
USER=yyazawa

while getopts t:i: flag
do
  case $flag in
  t)
    TYPE=$OPTARG
    echo "TARGET TYPE: $TYPE"
    ;;
  i)
    ID=$OPTARG
    echo "TARGET ID: $ID"
    ;;
  esac
done

if [ "$TYPE" = "NONE" ]; then
  exit 1
fi
if [ "$ID" = "NONE" ]; then
  exit 1
fi

mkdir -p ${TYPE}
echo `find -name "user.*${TYPE}${ID}*_EXT0"` > list/target.tmp.list

sed -i -e "s/\ /\n/g" list/target.tmp.list
cut -f 4 -d . list/target.tmp.list > list/dsid.tmp.list
sort list/dsid.tmp.list | uniq > list/udsid.tmp.list
for DSID in `cat list/udsid.tmp.list`;
do
  find -name "user.*${DSID}*mumupi_${ID}*_EXT0" 
  if [ `echo ${DSID} | grep ^00` ]; then
    mkdir -p ${TYPE}/DATA
    if [ ${DSID} -gt 296938 -a ${DSID} -lt 300280 ]; then
      mkdir -p ${TYPE}/DATA/periodA
      hadd -f ${TYPE}/DATA/periodA/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 300344 -a $DSID -lt 300909 ]; then
      mkdir -p ${TYPE}/DATA/periodB
      hadd -f ${TYPE}/DATA/periodB/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 301911 -a $DSID -lt 302394 ]; then
      mkdir -p ${TYPE}/DATA/periodC
      hadd -f ${TYPE}/DATA/periodC/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 302736 -a $DSID -lt 303561 ]; then
      mkdir -p ${TYPE}/DATA/periodD
      hadd -f ${TYPE}/DATA/periodD/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 303637 -a $DSID -lt 303893 ]; then
      mkdir -p ${TYPE}/DATA/periodE
      hadd -f ${TYPE}/DATA/periodE/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 303942 -a $DSID -lt 304495 ]; then
      mkdir -p ${TYPE}/DATA/periodF
      hadd -f ${TYPE}/DATA/periodF/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 305379 -a $DSID -lt 306449 ]; then
      mkdir -p ${TYPE}/DATA/periodG
      hadd -f ${TYPE}/DATA/periodG/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 307125 -a $DSID -lt 308085 ]; then
      mkdir -p ${TYPE}/DATA/periodI
      hadd -f ${TYPE}/DATA/periodI/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 309374 -a $DSID -lt 309760 ]; then
      mkdir -p ${TYPE}/DATA/periodK
      hadd -f ${TYPE}/DATA/periodK/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ $DSID -gt 310014 -a $DSID -lt 311482 ]; then
      mkdir -p ${TYPE}/DATA/periodL
      hadd -f ${TYPE}/DATA/periodL/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    fi
  else
    if [ ${DSID} -eq 303561 -o ${DSID} -eq 303562 ]; then
      mkdir -p ${TYPE}/MC_WTAU3MU_OLD
      hadd -f ${TYPE}/MC_WTAU3MU_OLD/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ ${DSID} -eq 303563 -o ${DSID} -eq 303564 ]; then
      mkdir -p ${TYPE}/MC_DSTAU3MU_OLD
      hadd -f ${TYPE}/MC_DSTAU3MU_OLD/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ ${DSID} -eq 303565 -o ${DSID} -eq 303566 ]; then
      mkdir -p ${TYPE}/MC_DSPHIPI_OLD
      hadd -f ${TYPE}/MC_DSPHIPI_OLD/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ ${DSID} -eq 303567 -o ${DSID} -eq 303568 ]; then
      mkdir -p ${TYPE}/MC_HFTAU3MU_OLD/bb
      hadd -f ${TYPE}/MC_HFTAU3MU_OLD/bb/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    elif [ ${DSID} -eq 303569 -o ${DSID} -eq 303570 ]; then
      mkdir -p ${TYPE}/MC_HFTAU3MU_OLD/cc
      hadd -f ${TYPE}/MC_HFTAU3MU_OLD/cc/${DSID}_${ID}.root user.$USER.${DSID}*${TYPE}${ID}*_EXT0/*
    fi
  fi
done

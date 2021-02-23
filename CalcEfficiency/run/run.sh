#!/bin/bash
#OUTPUT_DIR="$TestArea/output"
USE_BSUB="1" ### 0: no use lsf batch  1: use lsf batch
SEPARATE="1" ### 0: use all files in 1 job 1: one job per one file( only work with batch job )
BSUB_QUE="30m"
GRL_NAME="current_grl.xml"

if [ "$TestArea" = "" ] ; then
  echo "TestArea is missing"
  exit 1
fi

#source $TestArea/build/$CMTCONFIG/setup.sh

if [ $USE_BSUB = 1 ] ; then
  echo "Batch will be used..." && sleep 1
else
  echo "local job will be used..." && sleep 2
fi

if [ "$1" = "" ] ; then
  if [ "$USE_BSUB" = "1" ] ; then
    bsub -q $BSUB_QUE -o log.out athena.py CalcEffAlg_options.py
  else
    athena.py CalcEffAlg_options.py &> log_1101_01 &
  fi
  exit 0
fi

LIST_NAME=$1
if [ -f "$LIST_NAME" ] ; then
  echo $LIST_NAME
  if [ "$USE_BSUB" = "1" ] ; then
    if [ "$SEPARATE" = "0" ] ; then
      echo "athena.py -c 'LocalInputFileList=\"$LIST_NAME\"' CalcEffAlg_options.py" > tmp_athena_run.sh
      cat tmp_athena_run.sh
      bsub -q $BSUB_QUE -o log_1101 < tmp_athena_run.sh
    else
      for FILE in `cat $LIST_NAME`
      do
        TEMP_DIR=`echo "$FILE" | sed -e "s:/:_:g"`
        DIR="Output/$TEMP_DIR"
        mkdir -p $DIR
        echo "$FILE" > $DIR/tmp.list
        cp "$GRL_NAME" $DIR/
        cd $DIR
        #TMP_LIST="$DIR/tmp.list"
        TMP_LIST="tmp.list"
        echo "athena.py -c 'LocalInputFileList=\"$TMP_LIST\"' $TestArea/CalcEfficiency/run/CalcEffAlg_options.py" > tmp_athena_run.sh
        cat tmp_athena_run.sh
        bsub -q $BSUB_QUE -o log_1225_05 < tmp_athena_run.sh
        cd -
      done
    fi
  else
    echo "athena.py -c 'LocalInputFileList=\"$LIST_NAME\"' CalcEffAlg_options.py &> log1 &" > tmp_athena_run.sh
    cat tmp_athena_run.sh
    sh tmp_athena_run.sh
  fi
  #athena.py -c "LocalInputFileList=\"$LIST_NAME\"" CalcEffAlg_options.py &> log &
fi

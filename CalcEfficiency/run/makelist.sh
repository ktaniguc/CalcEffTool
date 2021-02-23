#!/bin/sh

ISSIM="false"
OUTPUT=output.list
TAG="*"

while getopts s:d:i:t:g:o: flag
do
  case $flag in
  s)
    ISSIM=$OPTARG
    echo "TARGET TYPE: MC"
    ;;
  d)
    DATATYPE=$OPTARG
    echo "Data format should be: $DATATYPE"
    ;;
  i)
    DSID=$OPTARG
    echo "RUNNUMBER or DSID is limited as $DSID"
    ;;
  t)
    TAG=$OPTARG
    echo "RECO TAG(m or p) is limited as $TAG"
    ;;
  g)
    GRL=$OPTARG
    echo "REFERNCED GRL is $GRL"
    ;;
  o)
    OUTPUT=$OPTARG
    echo "OUTPUT LIST is $OUTPUT"
    ;;
  esac
done

if [ -e $OUTPUT ]; then
  rm $OUTPUT
fi

if [ $ISSIM = "true" ]; then
  if [ $DATATYPE = "AOD" ]; then
    echo "search for mc15_13TeV.$DSID*merge*.${DATATYPE}.*r$TAG"
    rucio list-dids "mc15_13TeV.$DSID*merge*.${DATATYPE}.*r$TAG" >> tmp.tmplist
  else
    echo "search for mc15_13TeV.$DSID*merge*.${DATATYPE}.*p$TAG"
    rucio list-dids "mc15_13TeV.$DSID*merge*.${DATATYPE}.*p$TAG" >> tmp.tmplist
  fi
  sed -i -e '/_tid/d' tmp.tmplist
  sed -n '/mc15_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -n '/mc15_13TeV\:/d' tmp2.tmplist
else
  if [ $DATATYPE = "AOD" ]; then
    echo "search for data15(16)_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG"
    rucio list-dids "data15_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" >> tmp.tmplist
    rucio list-dids "data16_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" >> tmp.tmplist
  else
    echo "search for data15(16)_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*p$TAG"
    rucio list-dids "data15_13TeV.00$DSID*physics_Main*merge*.${DATATYPEi}.*p$TAG" >> tmp.tmplist
    rucio list-dids "data16_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*p$TAG" >> tmp.tmplist
  fi
  sed -i -e '/_tid/d' tmp.tmplist
  sed -n '/data15_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data15_13TeV\://g' tmp2.tmplist
  sed -n '/data16_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data16_13TeV\://g' tmp2.tmplist
fi

if [ ! -e  tmp2.tmplist ]; then
  echo "dataset list is not created!"
  exit 1
else 
  cut -f 2 -d \  tmp2.tmplist > dataset.tmplist
  if [ ! $GRL = "" ]; then
    cp $GRL targetgrl.xml
    sed -n 12p targetgrl.xml > grldsid.tmplist
    sed -i -e "s/,/\n/g" grldsid.tmplist
    sed -i -e "s/>/\n/g" grldsid.tmplist
    sed -i -e "s/</\n/g" grldsid.tmplist
    sed -i -e "/Metadata/d" grldsid.tmplist
    sed -i -e "/^[  ]*$/d" grldsid.tmplist
    for GRLRUN in `cat grldsid.tmplist`;
    do
      grep "$GRLRUN" dataset.tmplist > check.tmplist
      LINECOUNT=`wc -l check.tmplist | cut -f 1 -d \ ` 
      #echo $LINECOUNT
      if [ $LINECOUNT -eq 1 ]; then 
        sed -n "/$GRLRUN/p" dataset.tmplist >> $OUTPUT
      elif [ $LINECOUNT -ge 2 ]; then 
        cat check.tmplist | awk -F . '{ print $NF }' > duplicated.tmplist
        FTAG=0
        MTAG=0
        PTAG=0
        for TAGCOMP in `cat duplicated.tmplist`;
        do
          TMPFTAG=`echo $TAGCOMP | cut -f 1 -d _`
          TMPFTAG=`echo $TMPFTAG | sed -e s/f//g`
          TMPMTAG=`echo $TAGCOMP | cut -f 2 -d _`
          TMPMTAG=`echo $TMPMTAG | sed -e s/m//g`
          TMPPTAG=`echo $TAGCOMP | cut -f 3 -d _`
          TMPPTAG=`echo $TMPPTAG | sed -e s/p//g`
          #echo $GRLRUN, $TAGCOMP 
          #echo $TMPFTAG:$FTAG, $TMPMTAG:$MTAG
          if [ $DATATYPE != "AOD" ]; then
            if [ $TMPFTAG -ge $FTAG -a $TMPMTAG -ge $MTAG -a $TMPPTAG -ge $PTAG ]; then
              FTAG=$TMPFTAG
              MTAG=$TMPMTAG
              PTAG=$TMPPTAG
            fi
          else
            if [ $TMPFTAG -ge $FTAG -a $TMPMTAG -ge $MTAG ]; then
              FTAG=$TMPFTAG
              MTAG=$TMPMTAG
            fi
          fi
        done
        #echo "$GRLRUN is duplicated!(maybe corrected)" >> $OUTPUT
        if [ $DATATYPE = "AOD" ]; then
          sed -n "/f${FTAG}_m${MTAG}/p" check.tmplist >> $OUTPUT
        else
          sed -n "/f${FTAG}_m${MTAG}_p${PTAG}/p" check.tmplist >> $OUTPUT
        fi
      else 
        echo "$GRLRUN is not found"
      fi
    done
  fi
fi

rm -f *.tmplist


# sample command
# ./makelist.sh -d AOD -o grid_data_2016_xAOD.list -g ../current_grl.xml 
# ./makelist.sh -d DAOD_BPHY7 -o grid_data_2016_BPHY7.list -t 2840 -g ../current_grl.xml

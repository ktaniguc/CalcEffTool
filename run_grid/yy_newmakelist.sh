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
    echo "search for data16_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG"
    #rucio list-dids "data15_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" >> tmp.tmplist
    rucio list-dids "data16_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" >> tmp.tmplist
    #rucio list-dids "data17_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" | grep -v "_lb" > tmp.tmplist
    rucio list-dids "data18_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*m$TAG" | grep -v "_lb" > tmp.tmplist
    #cat tmp.tmplist
  else
    echo "search for data15(16)_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*p$TAG"
    rucio list-dids "data15_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*p$TAG" >> tmp.tmplist
    rucio list-dids "data16_13TeV.00$DSID*physics_Main*merge*.${DATATYPE}.*p$TAG" >> tmp.tmplist
    rucio list-dids "data17_13TeV.00$DSID*physics_Main*deriv*.${DATATYPE}.*p$TAG" | grep -v "*.lb*" >> tmp.tmplist
  fi
  #sed -i -e '/_tid/d' tmp.tmplist
  sed -n '/data15_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data15_13TeV\://g' tmp2.tmplist
  sed -n '/data16_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data16_13TeV\://g' tmp2.tmplist
  sed -n '/data17_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data17_13TeV\://g' tmp2.tmplist
  sed -n '/data18_13TeV/p' tmp.tmplist >> tmp2.tmplist
  sed -i -e 's/data18_13TeV\://g' tmp2.tmplist
  echo "if1"
fi
if [ ! -e  tmp2.tmplist ]; then
  echo "dataset list is not created!"
  exit 1
else 
  echo "if2"
  cut -f 2 -d \  tmp2.tmplist > dataset.tmplist
  if [ ! $GRL = "" ]; then
    cp $GRL targetgrl.xml
    sed -n 11p targetgrl.xml > grldsid.tmplist
    #sed -n 12p targetgrl.xml > grldsid.tmplist
    sed -i -e "s/,/\n/g" grldsid.tmplist
    sed -i -e "s/>/\n/g" grldsid.tmplist
    sed -i -e "s/</\n/g" grldsid.tmplist
    sed -i -e "/Metadata/d" grldsid.tmplist
    sed -i -e "/^[  ]*$/d" grldsid.tmplist
    for GRLRUN in `cat grldsid.tmplist`;
    do
      grep "$GRLRUN" dataset.tmplist > check.tmplist
      LINECOUNT=`wc -l check.tmplist | cut -f 1 -d \ ` 
      cat check.tmplist
      echo "LINECOUNT=$LINECOUNT"
      if [ $LINECOUNT -eq 1 ]; then 
        sed -n "/$GRLRUN/p" dataset.tmplist >> $OUTPUT
      elif [ $LINECOUNT -ge 2 ]; then 
        cat check.tmplist | awk -F . '{ print $NF }' > duplicated.tmplist
        FTAG=0
        MTAG=0
        PTAG=0
        ISNONTID=0
        for TAGCOMP in `cat duplicated.tmplist`;
        do
          if [ ! `echo "TAGCOMP" | grep "_tid" ` ] ;then
            ISNONTID=1
          fi
          echo "TAGCOMP=$TAGCOMP, ISNONTID=$ISNONTID"
        done
        for TAGCOMP in `cat duplicated.tmplist`;
        do
          if [ $(( $ISNONTID )) -eq 1 ] ; then
            if [ `echo "TAGCOMP" | grep "_tid"` ] ; then
              continue
            fi
          fi
          TMPFTAG=`echo $TAGCOMP | cut -f 1 -d _`
          TMPFTAG=`echo $TMPFTAG | sed -e s/f//g`
          TMPMTAG=`echo $TAGCOMP | cut -f 2 -d _`
          TMPMTAG=`echo $TMPMTAG | sed -e s/m//g`
          TMPPTAG=`echo $TAGCOMP | cut -f 3 -d _`
          TMPPTAG=`echo $TMPPTAG | sed -e s/p//g`
          #echo "TMPFTAG=$TMPFTAG, TMPMTAG=$TMPMTAG, TMPPTAG=$TMPPTAG"
          #echo $GRLRUN, $TAGCOMP 
          #echo $TMPFTAG:$FTAG, $TMPMTAG:$MTAG
          if [ $DATATYPE = "AOD" ] ;then
            if [ $TMPFTAG -ge $FTAG -a $TMPMTAG -ge $MTAG ]; then
              FTAG=$TMPFTAG
              MTAG=$TMPMTAG
              PTAG=$TMPPTAG
            fi
          else 
            if [ $TMPFTAG -ge $FTAG -a $TMPMTAG -ge $MTAG ]; then
              FTAG=$TMPFTAG
              MTAG=$TMPMTAG
              PTAG=$TMPPTAG
            elif [ $TMPPTAG ]; then
              if [ "$TMPPTAG" -ge "$PTAG" -a "$DATATYPE" != "AOD" ]; then
                PTAG=$TMPPTAG
              fi
            fi
          fi
        done
        echo "FTAG=$FTAG, MTAG=$MTAG, PTAG=$PTAG"
        #echo "$GRLRUN is duplicated!(maybe corrected)" >> $OUTPUT
        if [ $DATATYPE = "AOD" ]; then
          sed -n "/f${FTAG}_m${MTAG}$/p" check.tmplist >> $OUTPUT
        else
          if [ $(( $ISNONTID )) -eq 1 ] ; then
            sed -n "/f${FTAG}_m${MTAG}_p${PTAG}$/p" check.tmplist >> $OUTPUT
          else
            sed -n "/f${FTAG}_m${MTAG}_p${PTAG}/p" check.tmplist >> $OUTPUT
          fi
        fi
      else 
        echo "$GRLRUN is not found"
      fi
    done
  fi
fi
rm -f *.tmplist

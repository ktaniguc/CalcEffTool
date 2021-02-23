# echo "setup CalcEfficiency MyNewPackage-00-00-01 in /gpfs/home/yfukuhar/work/CalcEffTool"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.7.3/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtCalcEfficiencytempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtCalcEfficiencytempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=CalcEfficiency -version=MyNewPackage-00-00-01 -path=/gpfs/home/yfukuhar/work/CalcEffTool  -no_cleanup $* >${cmtCalcEfficiencytempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=CalcEfficiency -version=MyNewPackage-00-00-01 -path=/gpfs/home/yfukuhar/work/CalcEffTool  -no_cleanup $* >${cmtCalcEfficiencytempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtCalcEfficiencytempfile}
  unset cmtCalcEfficiencytempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtCalcEfficiencytempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtCalcEfficiencytempfile}
unset cmtCalcEfficiencytempfile
return $cmtsetupstatus


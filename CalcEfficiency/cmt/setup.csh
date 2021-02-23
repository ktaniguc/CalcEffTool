# echo "setup CalcEfficiency MyNewPackage-00-00-01 in /gpfs/home/yfukuhar/work/CalcEffTool"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.7.3/CMT/v1r25p20140131
endif
source ${CMTROOT}/mgr/setup.csh
set cmtCalcEfficiencytempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtCalcEfficiencytempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=CalcEfficiency -version=MyNewPackage-00-00-01 -path=/gpfs/home/yfukuhar/work/CalcEffTool  -no_cleanup $* >${cmtCalcEfficiencytempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=CalcEfficiency -version=MyNewPackage-00-00-01 -path=/gpfs/home/yfukuhar/work/CalcEffTool  -no_cleanup $* >${cmtCalcEfficiencytempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtCalcEfficiencytempfile}
  unset cmtCalcEfficiencytempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtCalcEfficiencytempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtCalcEfficiencytempfile}
unset cmtCalcEfficiencytempfile
exit $cmtsetupstatus


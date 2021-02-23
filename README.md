# CalcEffTool
------------------------------------
Author: Yukitaka yazawa [yyazawa / CalcEffTool](https://gitlab.cern.ch/yyazawa/CalcEffTool)
Email: yukitaka.yazawa[at]cern.ch

This is a package for calculating muon trigger efficiency.
This package is created by dkobayas(https://gitlab.cern.ch/dkobayas/CalcEffTool).
Compiling with cmake is available.

## Install
------------------------------------
On lxplus:

```sh
$ git clone ssh://git@gitlab.cern.ch:7999/ktaniguc/CalcEffTool.git
$ cd CalcEffTool/
#export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
#alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
$ setupATLAS
$ source setup.sh
$ ./compile.sh clean  #if you want to recompile, then "./compile.sh noCmake"
```

## How To Use
------------------------------------
```sh
$ cd run
$ vim your-aod-files.list
$ cat your-aod-files.list
/you-path-to-data/AOD.pool.root.1
/you-path-to-data/DAOD_MUON0.pool.root.1
$ vim CalcEffAlg_options.py
# edit joboption file to set the list
$ head -n 1 CalcEffAlg_options.py
LocalInputFileList="your-aod-files.list"
$ ./run.sh
```

## How to submit to grid
------------------------------------
### setup
```sh
$ source setup.sh
$ ./compile.sh clean    #if you have already compiled, you do not need this line
$ source setup_grid.sh
$ voms-proxy-init -voms atlas
$ cd run_grid
```
### change the shell script "sub_pathena.sh"
- you have to change "user.ktaniguc" to your name.
- It's not able to be decided freely but the name displayed when typing "voms-proxy-info --all | grep nickname"

### change the "CalcEffAlg_optionsGrid.py"
if the AOD file in acf.FilesInput does not exist, you have to change this to other existing AOD file with path
```python
#-----------------------------------------------------------------------------
# Input Datasets
#-----------------------------------------------------------------------------
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags as acf
if not acf.EvtMax.is_locked():
  acf.EvtMax=-1
#acf.FilesInput = InputFileList
acf.FilesInput += [
        "/home/knoguchi/CalcEffTool/run/mc16_13TeV/AOD.19041919._000001.pool.root.1" #change if does not exist!
]
```

### How to search input AOD file
- [ATLAS Metadata Interface](https://ami.in2p3.fr/)
* click the "Dataset browser"
* choose MC or data
* Data type -> AOD
* Keyword -> Jpsi, Z, W, etc.... as you want
* Keyword -> muon, 2muon, etc...
* click "View selection"
* copy the file name

- on the run_grid directory ...
```sh
echo input-file-name > test.list
```

### submit
```sh
./sub_pathena.sh test.list mySimpleTest
```
the 2nd argumment is added to output name. For example, "user.ktaniguc.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.KTTAP.e3601_s3126_r11590_mySimpleTest/"

### How to create good-runs list
```sh
cd run_grid/
$ lsetup rucio
$ ./yy_newmakelist.sh -d AOD -o (list_name) -g (GRL)
```
(GRL) is like data16_13TeV.periodAllYear_HEAD_Unknown_PHYS_StandardGRL_All_Good_25ns.xml 

## Notice about data17
------------------------------------
Option data17 was added in job option file.
It changes trigger from "HLT_mu20_2mu0noL1_JpsimumuFS" to "HLT_mu20_2mu2noL1_JpsimumuFS", which is the only running trigger in data17.

If you want to measure L1 MU20 and MU21 triggers in data17, you must write it as MU15 and MU20 in addMesChain function respectively(not MU20 and MU21), because current L1 trigger state was not reflected yet.

Different method to check the active state of trigger element was used in data17, so this option should be made empty for data16.

## Branch names
------------------------------------
| branch name | description |
|:------------:|:------------:|
| mes_n | number of trigger chains to measure |
| mes_name | names of trigger chains |
| tag_proc | id of procedure to tag muons <br> ( 1:J/&psi; tag & probe passing HLT_mu20_2mu2noL1_JpsimumuFS(intend to calculate efficiency L1 and L2, <br> 2:J/&psi; tap pass HLT_mu20_2mu4_JpsimumuL2(intend to calculate efficiency of EF, <br> 3:Z tap ) |
| sumReqdRL1 | sum of dR threshold between Level1 and offline (tag + probe) |
| sumReqdREF | sum of dR threshold between Event Filter and offline (tag + probe) |
| tag_ReqdRL1 | dR threshold between Level1 and offline of tag muon |
| tag_ReqdREF | dR threshold between EventFilter and offline of tag muon |
| tag_dRL1 | dR between Level1 and offline of tag muon |
| tag_dREF | dR between Level1 and offline of tag muon |
| tag_pt | offline p<sub>T</sub> of tag muon |
| tag_eta | offline &eta; of tag muon |
| tag_exteta | offline &eta; of tag muon ( extrapolated to Muon Spectrometer ) |
| tag_phi | offline &phi; of tag muon |
| tag_extphi | offline &phi; of tag muon ( extrapolated to Muon Spectrometer ) |
| tag_d0 | offline d<sub>0</sub> of tag muon |
| tag_z0 | offline z<sub>0</sub> of tag muon |
| tag_charge | offline charge of tag muon |
| probe_pt | offline p<sub>T</sub> of probe muon |
| probe_eta | offline &eta; of probe muon |
| probe_exteta | offline &eta; of probe muon ( extrapolated to Muon Spectrometer ) |
| probe_phi | offline &phi; of probe muon |
| probe_extphi | offline &phi; of probe muon ( extrapolated to Muon Spectrometer ) |
| probe_d0 | offline d<sub>0</sub> of probe muon |
| probe_z0 | offline z<sub>0</sub> of probe muon |
| probe_charge | offline charge of probe muon |
| tp_dR | offline dR between tag and probe muons |
| tp_deta | offline &eta; between tag and probe muons |
| tp_dphi | offline &phi; between tag and probe muons |
| tp_extdR | offline dR between tag and probe muons( extrapolated to Muon Spectrometer ) |
| tp_extdeta | offline &eta; between tag and probe muons( extrapolated to Muon Spectrometer ) |
| tp_extdphi | offline &phi; between tag and probe muons( extrapolated to Muon Spectrometer ) |
| tp_mass | reconstructed mass of tag and probe muons |

Branch names beginning with probe_mesL1, probe_mesSA, probe_mesCB, probe_mesEF and probe_mesFTF are variables of probe muon measured in Level1, muonSA, muComb, EventFilter and FTF respectively.  
For example,

| branch name | description |
|:------------:|:------------:|
| probe_mesSA_pass | whether pass muonSA or not ( -1 if non-pass ) |
| probe_mesSA_dR | dR between muonSA and offline muons |
| probe_mesSA_pt | p<sub>T</sub> measured in muonSA |
| probe_mesSA_eta | &eta; measured in muonSA ( in case of muonSA, etaIP ) |
| probe_mesSA_phi | &phi; measured in muonSA ( in case of muonSA, etaIP ) |
| probe_mesSA_etams | &eta; measured in muonSA ( etaMS ) |
| probe_mesSA_phims | &phi; measured in muonSA ( phiMS ) |
| probe_mesSA_etabe | &eta; measured in muonSA ( &eta; back-extrapolated to IP with same method of muComb ) |
| probe_mesSA_phibe | &phi; measured in muonSA ( &phi; back-extrapolated to IP with same method of muComb ) |

## Calculation of efficiency
You can use CalcEffPlotMaker(https://gitlab.cern.ch/yyazawa/CalcEffPlotMakerOrigin , also included in https://gitlab.cern.ch/dkobayas/CalcEffTool) to make efficiency plots.
Additional cuts on dR and pt are done and total efficiency in J/&psi; tap is also calculated by combining tag_proc = 1 and tag_proc = 2 there.

## for close-by muon analysis
------------------------------------
If you choose method = "ClosebyMuon" in CalcEffAlg_options.py, then special algorithm for the events like dimuon go through single RoI are executed.
This method does not do Tag-and-probe but do matching between offline muons and trigger objects.
only one trigger chain can be selected in CalcEffAlg.cxx
```
//in CalcEffAlg.cxx
119   if( m_tapmethod == "ClosebyMuon" ){
120       m_mig.initialize( 0, m_useExt, m_tapmethod, m_ext, m_vft, m_trigDecTool, m_dataType, "mu4", MuInfoGetter::L1_MU4, "HLT_mu4", "none" );
121   } else {
```
Indexes of Ntuple line up in order of trigger object matched to offline muon.

## Introduction

This repository contains an analysis code for the CYGNO-MC output.

## Create CYGNOTree Class

The CYGNO-MC output file can have different formats, depending if some branches have been saved or not (hits, particle flux).
Therefore, prior to compile the code, you may have to run `MakeClass` to save the data format in the CYGNOTree class, from which the CYGNOAnalysis class inherits. 

```
root -l your-rootfile.root
nTuple->MakeClass("CYGNOTree")
mv CYGNOTree.C src/
mv CYGNOTree.h include/
```
Open `include/CYGNOTree.h`, add the line `using namespace std;` and comment the lines inside the constructor and the destructor of `CYGNOTree`.
```
CYGNOTree::CYGNOTree(TTree *tree) : fChain(0)
{
// comment all
}

CYGNOTree::~CYGNOTree()
{
// comment all
}
```


## Compile

Compile the code with
```
cd src;
make all;
cd -
```

## Usage

The code expects a config file with different structure, depending if you want to analyze external or internal background:
* example for external backgrounds `config/cygnoconf`
* example for internal backgrounds `config/cygnoconf_40K`


## Submit jobs in batch system

The script to run the analysis in the PBS batch system is `scripts/create_cygnoconf_lngs.py`
Options:

* `-i` [config_file]
* `--tag` [tag]
* `--list` [subdirectory where to find the input list inside `lists/`]
* `--split` [maximum_files_per_job] (ony for external backgrounds)
* `--external` (use this option if analyzing external backgrounds)
* `--retry` (use this option if you want to relaunch only failed jobs)
* `--lime` (use this option if you are analyzing lime simulations)

Create lists, config files and scripts for submission on batch queues of internal bkg analysis
-----------------------------

Create one list for each isotope that you have simulated. 
You can do it running a command line:
```
mkdir -p lists
find /FULL-PATH-TO-SIMULATIONS/ -name "*.root" > lists/list_ISOTOPE_RadioactiveDecayFromVOLUMENAME.list
```

Once you have all the lists you can create the cygnoconfig files with the script `scripts/create_cygnoconf_lngs.py`.
You need to write a txt file similar to `config/inputconfCrystalPMTBody` with this structure
```
## Volume_name    Isotope                        Activity[Bq/kg]    Smearing[0 or 1]     T1/2[days]
VOLUMENAME        ISOTOPE                            0.01078            1                -999       ##if you don't need to set half life time, just put -999   
```
where the VOLUMENAME and ISOTOPE are the same strings in the list name. 

> **Note:**
Isotopes (even if they are in the same decay chain and in equilibrium) have to be treated individually in order to sum up the contributes.

Then check if the volume mass is listed in `scripts/create_cygnoconf_lngs.py` around line 60. If not add it to the dictionary.

Now you can run from `CYGNO-MC-Analysis/` directory 
```
python scripts/create_cygnoconf_lngs.py -i config/inputconfVOLUMENAME --workdir YOUR-FULLPATH-TO-CYGNO-MC-Analysis --tag ANYUSEFULTAG
```
and you will get the submission scripts in `submit/` directory. 
Check if you also have the config files for CYGNOAnalysis you need in `config/` directory (similar to `cygnoconf`) 


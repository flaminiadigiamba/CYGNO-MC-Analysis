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

The script to run the analysis in the PBS batch system is `scripts/create_cygnoconf.py`
Options:

* `-i` <config_file>
* `--tag` <tag>
* `--list` <inputlist>
* `--split` <maximum files per job> (ony for external backgrounds)
* `--external` (use this option if analyzing external backgrounds)
* `--retry` (use this option if you want to relaunch only failed jobs)

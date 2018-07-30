# Tommaso  -  Machine Learning and Muons

## Python script from ROOT file to flat CSV
This code allows to read ROOT file content directly into a flat CSV file.

Usage:
```
./ROOTtoCSV.py --help
Usage: PROG [-h] [--fin INPUTFILE] [--branch BRANCH] [--branches BRANCHES]
            [--fout FOUT] [--branch-list] [--cut CUT]

optional arguments:
  -h, --help           show this help message and exit
  --fin INPUTFILE      Input ROOT file
  --branch BRANCH      Input ROOT file branch (default events)
  --branches BRANCHES  ROOT branches to read,
                       e.g.'dtPrimitives.id_r,genParticles.pt'
  --fout FOUT          Output CSV file
  --branch-list        List branches and exit (requires --branch argument)
  --cut CUT            Cuts for CSV

```
Example:

```bash
./ROOTtoCSV.py --fin /afs/cern.ch/work/b/bonacor/TOMMASO/MuonTree.root --branch MuonPogTree/MUONPOGTREE --branches "dtPrimitive.id_r,dtPrimitive.id_eta,dtPrimitive.id_phi,dtPrimitive.bxTrackFinder(),dtPrimitive.phiGlb(),genParticle.pt,dtPrimitive.bx" --fout output_bxcut.csv --cut "dtPrimitive.bx==0"
```
## List of variables used for input

This section shows the input variables used in the csv:

```
dtPrimitive.id_r      Station identifier integer.
dtPrimitive.id_phi    Sector identifier integer.
dtPrimitive.id_eta    Ring/wheel identifier integer.
dtPrimitive.phiGlb    Phi angle expressed in global coordinates (depending on the active sector)
dtPrimitive.phiB      Bending angle (rescaled using: phiGlb+phiB/512)
genParticle.pt        Transverse angle of the muon generated (used as target for predictions).

```

The cut used for the creation of the CSV is:

```
dtPrimitive.bx==0    Bunch-Crossing required to be =0 in order to avoid all issues related to pile-up

```

## Content of the repo

The folder ** Jupyter Notebooks ** contains a list of the notebooks used for the Muon Trigger ML project. It contains a pre-process data macro used after ROOTtoCSV.py software, the Keras model macro and the ROOT plots production macro.
The ** output ** folder, instead, contains the csv files produced during the process as well as the keras models. 


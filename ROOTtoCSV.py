#!/usr/bin/env python
import ROOT as root
import numpy as np
import csv
import argparse
import os.path
#root.gInterpreter.ProcessLine('#include "interface/MuonPogTree.h"')
#root.gSystem.Load('MuonPogTreeDict_rdict')
line = '-'*64


class OptionParser():
    def __init__(self):
        "User based option parser"
        self.parser = argparse.ArgumentParser(prog='PROG')
        self.parser.add_argument("--fin", action="store",
            dest="inputFile", default="", help="Input ROOT file")
        self.parser.add_argument("--branch", action="store",
            dest="branch", default="events", help="Input ROOT file branch (default events)")
        self.parser.add_argument("--branches", action="store",
            dest="branches", default="", help="ROOT branches to read, e.g.'dtPrimitives.id_r,genParticles.pt'")
        self.parser.add_argument("--fout", action="store",
            dest="fout", default="output.csv", help="Output CSV file")
        self.parser.add_argument("--branch-list", action="store_true",
            dest="listbranches", default=False, help="List branches and exit (requires --branch argument)" )
        self.parser.add_argument("--cut",action="store",
            dest="cut", default="True", help="Cuts for CSV")

def list_branches(tree,base_tree,n=0):
    n += 1
    for branch in tree.GetListOfBranches():
        br = base_tree.GetBranch(branch.GetName())
        lname,ltype = branch.GetName(),br.GetTypeName()
        print '\t'*(n-1),'-> Branch ',lname,' with type ',ltype
        list_branches(br,base_tree,n) 

 
def convert_to_csv(muonTree,fout,l_branches,cut):
    "Function that converts selected branches into a CSV file"
    save_path = './output/'
    if not os.path.exists(save_path):
        os.makedirs(save_path)
    completeName = os.path.join(save_path,fout)
    branches = [b.strip() for b in l_branches.split(',')]
    new_branch = []
    header = []
    print branches

    entries = muonTree.GetEntriesFast()

    with open(completeName,'wb') as csvfile:
        header.insert(0,"Event")
        for branch in branches:
            header.append(branch) 
        writer = csv.writer(csvfile)
        writer.writerow(header)
        for entry in muonTree: 
            for dtPrimitive, genParticle in [(dtPrimitive,genParticle) for dtPrimitive in entry.event.dtPrimitives for genParticle in entry.event.genParticles]: 
                new_branch.insert(0,entry.event.eventNumber)
                if eval(cut): #dtPrimitive.bx == 0:
                    for branch in branches:   
                        new_branch.append(eval(branch))  
                    writer.writerow(new_branch) 
                    del new_branch[:]
                del new_branch[:]

def main():
    "Main function"
    optmgr  = OptionParser()
    opts = optmgr.parser.parse_args()
    root.gROOT.LoadMacro('interface/MuonPogTree.h++')
    from ROOT.muon_pog import Event 
    fin = root.TFile(opts.inputFile)
    muonTree = fin.Get(opts.branch)
    if opts.listbranches == True:
        print line
        list_branches(muonTree,muonTree)
        print line
    else:
        convert_to_csv(muonTree,opts.fout,opts.branches,opts.cut)


if __name__ == '__main__':
    main()


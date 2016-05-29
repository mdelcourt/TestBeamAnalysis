#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TLeaf.h"
#include <vector>
#include <map>
#include "TH1I.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLegend.h"
#include <iomanip>
#include <string>
#include "TBrowser.h"
#include <algorithm>
#include <sstream>
#include "AnalysisObjects.cc"

#ifdef __MAKECINT__
#pragma link C++ class std::map<std::string,std::vector<int> >+;
#pragma link C++ class tbeam::cluster+;
#pragma link C++ class std::vector<tbeam::stub * >+;
#pragma link C++ class std::vector<tbeam::cluster *>+;
#pragma link C++ class std::vector<tbeam::cluster>+;
#pragma link C++ class std::map<std::string,std::vector<tbeam::cluster *> >+;
#pragma link C++ class tbeam::stub+;
#pragma link C++ class tbeam::cbc+;
#pragma link C++ class tbeam::dutEvent+;
#pragma link C++ class tbeam::condEvent+;
#endif

using namespace std;

void exampleAnalysis(string fName = "ntuple775.root"){
    
    TFile * f = new TFile(fName.c_str());
    if(!f->IsOpen()){return;}
    
    
    TTree * t = (TTree*)f->Get("treeMaker/tbeamTree");
    TBranch * dutBranch=0;
    TBranch * condBranch=0;
    tbeam::dutEvent * DUT = new tbeam::dutEvent();
    tbeam::condEvent * COND = new tbeam::condEvent();

    t->SetBranchAddress("DUT",&DUT,&dutBranch);
    t->SetBranchAddress("Condition",&COND,&condBranch);

    TH1 * badStubTDC       = new TH1I("badStubTDC","bad stub TDC", 20,0,20); 
    TH1 * TDC              = new TH1I("TDC","TDC", 20,0,20); 
    TH1 * clPos            = new TH1I("clPos","Beam profile on det0",255,0,255);
    TH1 * clSize           = new TH1I("clSize","Cluster Size",100,0,100);
    TH1 * nStubsPerCluster = new TH1I("nSpC", "Number of stubs from the same seeding cluster",10,0,10);

    int badStub(0),goodStub(0);

    for (int i =0; i<t->GetEntries(); i++){
        if (i/10000 == i*1./10000){cout<< i<<"/"<<t->GetEntries()<<endl;}
        Long64_t tentry = t->LoadTree(i);
        dutBranch->GetEntry(tentry);
        condBranch->GetEntry(tentry);
        
        if (COND->tdcPhase<4)continue;
        
        TDC->Fill(COND->tdcPhase);

        for ( vector<tbeam::cluster*>::iterator cl = DUT->clusters["det0"].begin(); cl!=DUT->clusters["det0"].end(); ++cl){
            clPos->Fill((*cl)->x);
            clSize->Fill((*cl)->size);
            nStubsPerCluster->Fill((*cl)->stubs.size());
        }
        
        if (DUT->stubWordReco != DUT->stubWord){
           badStub++;
           badStubTDC->Fill(COND->tdcPhase);
        }
        else{
            goodStub++;
        }
    }
    cout<<"Proportion of bad stubs = "<<badStub*1./(goodStub+badStub)<<endl;
    cout<<"More plots available in TBrowser."<<endl; 


    TH1 * badStubTdcRatio = new TH1F("badStubTdcRatio", "Prop of stub mismatch / tdc phase", 20, 0, 20);
    
    for (int i=0; i<TDC->GetNbinsX(); i++){
       float N = badStubTDC->GetBinContent(i);
       if (N>0){
          float p = badStubTDC->GetBinContent(i)*1./TDC->GetBinContent(i);
          badStubTdcRatio->SetBinContent(i,p);
          badStubTdcRatio->SetBinError(i,pow(p*(1-p)*1./N,0.5));
       }
    }
    badStubTdcRatio->GetXaxis()->SetTitle("TDC phase"); 
    badStubTdcRatio->GetXaxis()->SetTitle("TDC phase"); 
    
    badStubTdcRatio->Draw();

}


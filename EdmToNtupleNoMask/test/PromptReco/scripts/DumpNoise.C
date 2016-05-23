

#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TLeaf.h"
#include <vector>
#include <map>
#include "TH1I.h"
#include "TCanvas.h"
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TH2F.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLegend.h"
#include <iomanip>
#include <string>
#include "TBrowser.h"
#include <algorithm>
#include <sstream>


#ifdef __MAKECINT__
#pragma link C++ class map<string,vector<int> >+;
#endif

using namespace std;

// Default condition data
UInt_t CWD = 4;
UInt_t SSIZE = 6;
UInt_t OFFSET = 0;
UInt_t VCTH = 0;
UInt_t HV = 0;
UInt_t ANGLE = 0;
UInt_t TILT_ANGLE = 0;
UInt_t LATENCY = 0;
UInt_t L1A = 0;

//Eff param

int effOffset = 0;
int effWindow= 5 ; // will look for cluster in offset +- effWidth


int CBCSIZE=127;
int nStrip = CBCSIZE * 8;
int SENSOR_SIZE=nStrip;

int max_cl_for_stubCombi=10;

struct cl{
    double x;
    int size;
};

vector <cl> clusterizer(vector <int> hits){
    vector <cl> toReturn;
    if (hits.size()<1){
        return(toReturn);
    }
    double x0=hits.at(0);
    int size=1;

    for (unsigned int i=1; i<hits.size(); i++){
        if (hits.at(i)==x0+size){
            size++;
        }
        else{
            cl clust;
            clust.x=x0+(size-1)/2.;
            clust.size=size;
            toReturn.push_back(clust);
            x0=hits.at(i);
            size=1;
        }
    }
   cl clust;
   clust.x=x0+(size-1)/2;
   clust.size=size;
   toReturn.push_back(clust);
   return(toReturn);
}

void getCondData(TTree * t){

    t->GetEntry(0);
    TLeaf * lVCTH =t->GetLeaf("vcth");
    if (!lVCTH) cout<<"No VCTH leaf found"<<endl;
    else VCTH = lVCTH->GetValue();

    TLeaf * lHV =t->GetLeaf("hvSettings");
    if (!lHV) cout<<"No hvSettings leaf found"<<endl;
    else HV = lHV->GetValue();

    TLeaf * ldutAngle =t->GetLeaf("dutAngle");
    if (!ldutAngle) cout<<"No dutAngle leaf found"<<endl;
    else ANGLE = ldutAngle->GetValue();

    TLeaf * lTiltAngle =t->GetLeaf("tilt");
    if (!lTiltAngle) cout<<"No tiltAngle leaf found"<<endl;
    else TILT_ANGLE = lTiltAngle->GetValue();

    TLeaf * lLatency =t->GetLeaf("dataLatency");
    if (!lLatency) cout<<"No dataLatency leaf found"<<endl;
    else LATENCY = lLatency->GetValue();

    TLeaf * lL1A =t->GetLeaf("L1Latency");
    if (!lL1A) cout<<"No L1Latency leaf found"<<endl;
    else L1A = lL1A->GetValue();

    TLeaf * lCWD =t->GetLeaf("cwd");
    if (!lCWD) cout<<"No CWD leaf found"<<endl;
    //else CWD = lCWD->GetValue();

    TLeaf * lOffset =t->GetLeaf("offset");
    if (!lOffset) cout<<"No offset leaf found"<<endl;
    //else OFFSET = lOffset->GetValue();

    TLeaf * lSSize =t->GetLeaf("window");
    if (!lSSize) cout<<"No stubWindow leaf found"<<endl;
    //else SSIZE = lSSize->GetValue();

/*    TLeaf * lVCTH =t->GetLeaf("VCTH");
    if (!lVCTH) cout<<"No VCTH leaf found"<<endl;
    else VCTH = lVCTH->GetValue();*/



}

int stubSimulator(vector <cl> c0, vector <cl> c1){
    unsigned int stubWord=0;
    for (unsigned int i=0; i<c1.size(); i++){
        if (c1.at(i).size<CWD){
            for(unsigned int j=0; j<c0.size(); j++){
                if (c0.at(j).size<CWD && abs((int)c1.at(i).x-(int)c0.at(j).x+OFFSET)<SSIZE){
                    for (int k=7; k>=0; k--){
                        if (c0.at(j).x>=k*CBCSIZE){
                            //Set kth byte to 1
                            stubWord= stubWord | (int)1<<k;
                            break;
                        }
                    }
                }
            }
        }
    }
    return(stubWord);
}


void fillClusters(vector <cl> * c, TH1* h){
    for (int i=0; i<c->size(); i++){
        h->Fill(c->at(i).x);
    }
}

void fillStubInfo(int stub, int stubSim, TH2* h){
    // x= 0 : No stub, no sim
    //    1 : No stub, sim
    //    2 : Stub, no sim
    //    3 : Stub, sim
    for (int CBC=0; CBC<16; CBC++){
        bool d = (stub>>CBC)%2;
        bool s = (stubSim>>CBC)%2;
        int key = d*2+s;
        h->Fill(key,CBC);
    }
}




void DumpNoise(string fName = "nope.root",string outFile="save.root"){
    UInt_t stub=0;
    map<string,vector <int> > * data = 0;
    TFile * f = new TFile(fName.c_str());
    if(!f->IsOpen()){return;}
    TTree * t = (TTree*)f->Get("treeMaker/tbeamTree");
    getCondData(t);
    UInt_t tdc;
    TBranch *bvpx = 0;
    TBranch *sbranch = 0;
    TBranch *tbranch = 0;
    t->SetBranchAddress("dut_channel",&data,&bvpx);
    t->SetBranchAddress("stubWord",&stub,&sbranch);
    t->SetBranchAddress("tdcPhase",&tdc,&tbranch);

    TH1 * h0 = new TH1I("h0","hits 0", nStrip,0,nStrip);
    TH1 * h1 = new TH1I("h1","hits 1", nStrip,0,nStrip);
    TH1 * h2 = new TH1I("h2","hits 2", nStrip,0,nStrip);
    TH1 * h3 = new TH1I("h3","hits 3", nStrip,0,nStrip);
    TH1 * raw0h = new TH1I("rawh","rawh",2*nStrip,0,2*nStrip);
    TH1 * raw1h = new TH1I("rawh1","rawh1",2*nStrip,0,2*nStrip);
    TH1 * hTDC = new TH1I("tdc","TDC phase",20,0,20);

    TH1 * effCandi0 = new TH1I("effCandi0","rawh",2*nStrip,0,2*nStrip);
    TH1 * effPos0 = new TH1I("effPos0","rawh",2*nStrip,0,2*nStrip);

    TH2 * stubInfo = new TH2I("stubInfo","Stub information",4,0,4,16,0,16);
    
    TH1 * hOcc = new TH1I("hitOcc","Hit occupancy",1000,0,1000);
    TH1 * hClOcc = new TH1I("clOcc","Cluster occupancy",1000,0,1000);

    TH1 * hstub  = new TH1I("stub","stub",65536,0,65536);
    TH1 * hstubSim  = new TH1I("stubSim","stubSim",65536,0,65536);
    TH1 * stubSize = new TH1I("stubSize","stub size",2000,-100,100);
    int nBadStub=0;
    int nGoodStub=0;
    int nStub = 0;
    int nStubSim =0;
    
    int fakePos=0;
    int fakeNeg=0;
   


    int N0(0),N1(0),P0(0),P1(0);
    int N2(0),N3(0),P2(0),P3(0);


    
    TH1 * noise0 = new TH1I("noise0","noise0",nStrip,0,nStrip);
    TH1 * noise1 = new TH1I("noise1","noise1",nStrip,0,nStrip);
    TH1 * noise2 = new TH1I("noise2","noise2",nStrip,0,nStrip);
    TH1 * noise3 = new TH1I("noise3","noise3",nStrip,0,nStrip);
    int nHits = 0;
    int nEvent= 0;
    int nClust =0;
    int clSize=0;
    int nEffCandi0=0;
    int nEffCandi1=0;
    for (int i =0; i<t->GetEntries(); i++){
        nEvent++;
        if (i/10000 == i*1./10000){cout<< i<<"/"<<t->GetEntries()<<endl;}
        Long64_t tentry = t->LoadTree(i);
        bvpx->GetEntry(tentry);
        sbranch->GetEntry(tentry);
        tbranch->GetEntry(tentry);
        hTDC->Fill(tdc);
        vector <int> raw0 = (*data)["det0"]; vector <int> raw1 = (*data)["det1"];
        
        nHits+=raw0.size();
        nHits+=raw1.size();
        
        // Split hits to 2 sensors
        vector <int> hits0, hits1, hits2, hits3;
        for (unsigned int j=0; j<raw0.size(); j++){
            raw0h->Fill(raw0.at(j));
            if (raw0.at(j)<SENSOR_SIZE){
                    hits0.push_back(raw0.at(j));
                //hits0.push_back(126-raw0.at(j)+254*(raw0.at(j)>126));
                }
            else{
                    hits2.push_back(raw0.at(j)-SENSOR_SIZE);
                }
        }
        for (unsigned int j=0; j<raw1.size(); j++){
            raw1h->Fill(raw1.at(j));
            if (raw1.at(j)<SENSOR_SIZE)
                {
                   // hits1.push_back(126-raw1.at(j)+254*(raw1.at(j)>126));
                    hits1.push_back(raw1.at(j));
                }
            else{
                    hits3.push_back(raw1.at(j)-SENSOR_SIZE);
            }
        }

        hOcc->Fill(hits0.size()+hits1.size()+hits2.size()+hits3.size());
        sort(hits0.begin(),hits0.end());
        sort(hits1.begin(),hits1.end());
        sort(hits2.begin(),hits2.end());
        sort(hits3.begin(),hits3.end());

        vector<cl> cl0 = clusterizer(hits0);
        vector<cl> cl1 = clusterizer(hits1);
        vector<cl> cl2 = clusterizer(hits2);
        vector<cl> cl3 = clusterizer(hits3);
        fillClusters(&cl0, h0);
        fillClusters(&cl1, h1);
        fillClusters(&cl2, h2);
        fillClusters(&cl3, h3);
        
        if (cl0.size()==1){
            N1++;
            for (int j=0; j<cl1.size(); j++) {
                if (abs(cl0.at(0).x-cl1.at(j).x+effOffset)>effWindow){
                    P1++;
                    noise1->Fill(cl1.at(j).x);
                }
            }
        }

        if (cl1.size()==1){
            N0++;
            for (int j=0; j<cl0.size(); j++){
                if (abs(cl1.at(0).x-cl0.at(j).x+effOffset)>effWindow){
                    P0++;
                    noise0->Fill(cl0.at(j).x);
                }
            }
        }
        
        if (cl2.size()==1){
            N3++;
            for (int j=0; j<cl3.size(); j++) {
                if (abs(cl2.at(0).x-cl3.at(j).x+effOffset)>effWindow){
                    P3++;
                    noise3->Fill(cl3.at(j).x);
                }
            }
        }

        if (cl3.size()==1){
            N2++;
            for (int j=0; j<cl2.size(); j++) {
                if (abs(cl3.at(0).x-cl2.at(j).x+effOffset)>effWindow){
                    P2++;
                    noise2->Fill(cl2.at(j).x);
                }
            }
        }
//        if (cl1.size()==1){
//            nEffCandi1++;
//            effCandi0->Fill(cl0.at(0).x);
//            for (int j=0; j<cl1.size(); j++) if (abs(cl0.at(j).x-cl1.at(0).x+effOffset)<effWindow+1){/*effPos0->Fill(cl0.at(1).x);*/nEffCandi1++;break;}
//        }
        
        hClOcc->Fill(cl0.size()+cl1.size()+cl2.size()+cl3.size());

        nClust+=cl0.size()+cl1.size()+cl2.size()+cl3.size();
        for(int j=0; j<cl0.size(); j++){
            clSize+=cl0.at(j).size;
        }
        for(int j=0; j<cl1.size(); j++){
            clSize+=cl1.at(j).size;
        }
        for(int j=0; j<cl2.size(); j++){
            clSize+=cl2.at(j).size;
        }
        for(int j=0; j<cl3.size(); j++){
            clSize+=cl3.at(j).size;
        }
        if (cl0.size()<=max_cl_for_stubCombi && cl1.size()<=max_cl_for_stubCombi){
            for (int j=0; j<cl0.size(); j++){
                for(int k=0; k<cl1.size(); k++){
                    stubSize->Fill(cl0.at(j).x-cl1.at(k).x);
                }
            }
        }

        if (cl2.size()<=max_cl_for_stubCombi && cl3.size()<=max_cl_for_stubCombi){
            for (int j=0; j<cl2.size(); j++){
                for(int k=0; k<cl3.size(); k++){
                    stubSize->Fill(cl2.at(j).x-cl3.at(k).x);
                }
            }
        }

        unsigned int stubSim1 = stubSimulator(cl0,cl1);
        unsigned int stubSim2 = stubSimulator(cl2,cl3);
        unsigned int stubSim = stubSim1+256*stubSim2;

        if ((stub>>11)%2){stub-=(int)pow(2,11);}
        if ((stub>>13)%2){stub-=(int)pow(2,13);}
        if ((stubSim>>11)%2){stubSim-=(int)pow(2,11);}
        if ((stubSim>>13)%2){stubSim-=(int)pow(2,13);}
        fillStubInfo(stub,stubSim,stubInfo);
        if(stub)nStub++;
        if(stub==stubSim && stub)nGoodStub++;
        if(stubSim)nStubSim++;
        hstub->Fill(stub);
        hstubSim->Fill(stubSim);
    
    }
    //f->Close();
    TH1 * summary = new TH1D("Summary","Summary",17,0,17);
    summary->GetXaxis()->SetBinLabel(1,"VCTH");
    summary->SetBinContent(1,VCTH);
    summary->GetXaxis()->SetBinLabel(2,"HV");
    summary->SetBinContent(2,HV);
    summary->GetXaxis()->SetBinLabel(3,"Angle");
    summary->SetBinContent(3,ANGLE); 
    summary->GetXaxis()->SetBinLabel(4,"Data Latency");
    summary->SetBinContent(4,LATENCY);
    summary->GetXaxis()->SetBinLabel(5,"L1 Latency");
    summary->SetBinContent(5,L1A);
    summary->GetXaxis()->SetBinLabel(6,"CWD");
    summary->SetBinContent(6,CWD);
    summary->GetXaxis()->SetBinLabel(7,"Offset");
    summary->SetBinContent(7,OFFSET);
    summary->GetXaxis()->SetBinLabel(8,"Window Size");
    summary->SetBinContent(8,SSIZE);
    summary->GetXaxis()->SetBinLabel(9,"tilt angle");
    summary->SetBinContent(9,TILT_ANGLE);
    summary->GetXaxis()->SetBinLabel(10,"Number of events");
    summary->SetBinContent(10,nEvent);
    int nCond = 10;
    summary->GetXaxis()->SetBinLabel(nCond+1,"Hit occ");
    summary->SetBinContent(nCond+1,nHits*1./nEvent);
    summary->GetXaxis()->SetBinLabel(nCond+2,"Cluster occ");
    summary->SetBinContent(nCond+2,nClust*1./nEvent);
    summary->GetXaxis()->SetBinLabel(nCond+3,"Cluster size");
    summary->SetBinContent(nCond+3,clSize*1./nClust);
    summary->GetXaxis()->SetBinLabel(nCond+4,"Stub occ");
    summary->SetBinContent(nCond+4,nStub *1./nEvent);
    summary->GetXaxis()->SetBinLabel(nCond+5,"Stub reco occ");
    summary->SetBinContent(nCond+5,nStubSim*1./nEvent);
    summary->GetXaxis()->SetBinLabel(nCond+6,"Stub eff");
    summary->SetBinContent(nCond+6,nGoodStub*1./nStubSim);
    summary->GetXaxis()->SetBinLabel(nCond+7,"Stub size");
    summary->SetBinContent(nCond+7,stubSize->GetMean());

    TFile * saveFile = new TFile(outFile.c_str(),"RECREATE");

    TH1 * eff0 = new TH1D("eff0","eff0",nStrip,0,nStrip);
    for (int i=0; i<nStrip; i++){
        double e = effPos0->GetBinContent(i+1);
        if (effCandi0->GetBinContent(i+1)==0){e=0;}
        else{e/=effCandi0->GetBinContent(i+1);}
        eff0->SetBinContent(i+1,e);
        if(e){eff0->SetBinError(i+1,sqrt(e*(1-e)/effCandi0->GetBinContent(i+1)));}
    }
    eff0->Write();
    hstub->Write();
    hstubSim->Write();
    h0->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    raw0h->Write();
    raw1h->Write();
    hOcc->Write();
    hClOcc->Write();
    stubInfo->GetXaxis()->SetBinLabel(1,"No stub + no Sim");
    stubInfo->GetXaxis()->SetBinLabel(2,"No Stub + Sim");
    stubInfo->GetXaxis()->SetBinLabel(3,"Stub + no Sim");
    stubInfo->GetXaxis()->SetBinLabel(4,"Stub + Sim");
    stubInfo->GetYaxis()->SetTitle("CBC #");
    stubInfo->Write();
    stubSize->Write();
    summary->Write();
    //saveFile->Close();
    stringstream ss;
    
    ss<<"echo '";
    //ss<<fName<<","<<VCTH<<",";
    //cout<<endl;
    ss<<fName<<","<<VCTH<<","<<N0<<","<<P0<<","<<N1<<","<<P1;
    ss<<                  ","<<N2<<","<<P2<<","<<N3<<","<<P3;
    ss<<"'>> out.txt";
    system(ss.str().c_str());

}


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
#include "TStyle.h"
#include "stdio.h"

double pitch_Mod_01 = 90.;
double pitch_Mod_02 = 80.;

void BeamDiv(){

	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
 	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;

	TH1F *h_div = new TH1F("","; D[#mum]; Entries", 100, -3000. , 3000.);


	TFile *recofile =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_478_120vcth.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);
	recotree->SetBranchAddress("clusters_S1", &clusters_position_S1);
    	recotree->SetBranchAddress("clusters_S2", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3", &clusters_position_S3);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);

		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();

		if (  cluster_size_S0 == 1 &&  cluster_size_S1 == 1 && cluster_size_S2 == 1 &&  cluster_size_S3 == 1){
			for(size_t iStrip = 0; iStrip < cluster_size_S0; ++iStrip){
				h_div->Fill((((clusters_position_S0->at(0)+clusters_position_S1->at(0))/2.)*pitch_Mod_01) - (((clusters_position_S2->at(0)+clusters_position_S3->at(0))/2.))*pitch_Mod_02);
			}
		}
	}
	h_div->Fit("gaus");

	gStyle->SetOptFit(1011);
	h_div->Draw();
}

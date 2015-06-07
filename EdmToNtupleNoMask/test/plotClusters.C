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


void plotClusters(){

	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
 	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;

	TH1F *h_clusters_S0 = new TH1F("",";X[strip];Entries", 256, 0. , 256.);
	TH1F *h_clusters_size_S0 = new TH1F("",";Clusters multiplicity;Entries", 20, 0 , 20);
	TH1F *h_clusters_S1 = new TH1F("clusters_S1","clusters_S1", 256, 0. , 256.);
	TH1F *h_clusters_size_S1 = new TH1F("","", 20, 0 , 20);

	TH1F *h_clusters_S2 = new TH1F("clusters_S2","clusters_S2", 256, 0. , 256.);
	TH1F *h_clusters_S3 = new TH1F("clusters_S3","clusters_S3", 256, 0. , 256.);

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

		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
		h_clusters_S0->Fill(clusters_position_S0->at(k));
		h_clusters_size_S0->Fill(clusters_position_S0->size());}

		for(unsigned int k = 0 ; k < cluster_size_S1 ; ++k){
		h_clusters_S1->Fill(clusters_position_S1->at(k));		h_clusters_size_S1->Fill(clusters_position_S1->size());}

		for(unsigned int k = 0 ; k < cluster_size_S2 ; ++k){
			h_clusters_S2->Fill(clusters_position_S2->at(k));}
		for(unsigned int k = 0 ; k < cluster_size_S3 ; ++k){
			h_clusters_S3->Fill(clusters_position_S3->at(k));}
		//	h_clusters_S3_masked->Fill(clusters_position_S3_masked->at(k));}
	}

	gStyle->SetOptStat(0);

		TCanvas *c1 = new TCanvas("c1","c1",700,500);
		h_clusters_S0->SetLineColor(kRed);
		h_clusters_S0->Draw();
		h_clusters_S1->SetLineColor(kBlue);
		h_clusters_S1->Draw("sames");
		//h_clusters_S2->SetLineColor(3);
		//h_clusters_S2->Draw("sames");
		//h_clusters_S3->SetLineColor(4);
		//h_clusters_S3->Draw("sames");

		TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
			leg->SetFillColor(0);
			//leg->SetLineColor(0);
			leg->AddEntry(h_clusters_S0,"S0","l");
			leg->AddEntry(h_clusters_S1,"S1","l");
			leg->Draw();

		TCanvas *c2 = new TCanvas("c2","c2",700,500);
		c2->SetLogy();
		Double_t scale = 1/h_clusters_size_S0->Integral();
  		h_clusters_size_S0->Scale(scale);
		h_clusters_size_S0->SetLineColor(kRed);
		h_clusters_size_S0->Draw();
		Double_t scale1 = 1/h_clusters_size_S1->Integral();
  		h_clusters_size_S1->Scale(scale1);
		h_clusters_size_S1->SetLineColor(kBlue);
		h_clusters_size_S1->Draw("same");

		TLegend *leg1 = new TLegend(0.1,0.7,0.48,0.9);
			leg1->SetFillColor(0);
			//leg->SetLineColor(0);
			leg1->AddEntry(h_clusters_S0,"S0","l");
			leg1->AddEntry(h_clusters_S1,"S1","l");
			leg1->Draw();
}

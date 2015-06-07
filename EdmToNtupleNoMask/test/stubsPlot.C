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

void stubsPlot(){



	std::vector<double> *stubs_module_1(0);

	TH1F *h_stubs0 = new TH1F("0","", 80, -10. , 30.);
	TH1F *h_stubs1 = new TH1F("8","", 80, -10. , 30.);
	TH1F *h_stubs2 = new TH1F("11","", 80, -10. , 30.);
	TH1F *h_stubs3 = new TH1F("12","", 80, -10. , 30.);
	TH1F *h_stubs4 = new TH1F("14","", 80, -10. , 30.);
	TH1F *h_stubs5 = new TH1F("16","", 80, -10. , 30.);
	TH1F *h_stubs6 = new TH1F("10","", 80, -10. , 30.);
	TH1F *h_stubs7 = new TH1F("13","", 80, -10. , 30.);
	TH1F *h_stubs8 = new TH1F("15","", 80, -10. , 30.);
	TH1F *h_stubs9 = new TH1F("20","", 80, -10. , 30.);
	TH1F *h_stubs10 = new TH1F("30","", 80, -10. , 30.);

	
	TFile *recofile =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_478_120vcth.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs0->Fill(stubs_module_1->at(k));
		}
	}


	TFile *recofile1 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_499_10deg_120vcth.root");
	TTree *recotree1 = (TTree *) recofile1->Get("recotree");
	recotree1->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries1 = recotree1->GetEntries();

	for (int i =0; i < dutEntries1; i++){
		recotree1->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs1->Fill(stubs_module_1->at(k));
		}
	}



	TFile *recofile2 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_500_13deg_120vcth.root");
	TTree *recotree2 = (TTree *) recofile2->Get("recotree");
	recotree2->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries2 = recotree2->GetEntries();

	for (int i =0; i < dutEntries2; i++){
		recotree2->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs2->Fill(stubs_module_1->at(k));
		}
	}


	TFile *recofile3 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_501_14deg_120vcth.root");
	TTree *recotree3 = (TTree *) recofile3->Get("recotree");
	recotree3->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries3 = recotree3->GetEntries();

	for (int i =0; i < dutEntries3; i++){
		recotree3->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs3->Fill(stubs_module_1->at(k));
		}
	}



	TFile *recofile4 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_502_16deg_120vcth.root");
	TTree *recotree4 = (TTree *) recofile4->Get("recotree");
	recotree4->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries4 = recotree4->GetEntries();

	for (int i =0; i < dutEntries4; i++){
		recotree4->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs4->Fill(stubs_module_1->at(k));
		}
	}


TFile *recofile5 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_503_18deg_120vcth.root");
	TTree *recotree5 = (TTree *) recofile5->Get("recotree");
	recotree5->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries5 = recotree5->GetEntries();

	for (int i =0; i < dutEntries5; i++){
		recotree5->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs5->Fill(stubs_module_1->at(k));
		}
	}




TFile *recofile6 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_504_12deg_120vcth.root");
	TTree *recotree6 = (TTree *) recofile6->Get("recotree");
	recotree6->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries6 = recotree6->GetEntries();

	for (int i =0; i < dutEntries6; i++){
		recotree6->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs6->Fill(stubs_module_1->at(k));
		}
	}


TFile *recofile7 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_511_15deg_120vcth.root");
	TTree *recotree7 = (TTree *) recofile7->Get("recotree");
	recotree7->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries7 = recotree7->GetEntries();

	for (int i =0; i < dutEntries7; i++){
		recotree7->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs7->Fill(stubs_module_1->at(k));
		}
	}


TFile *recofile8 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_518_17deg_120vcth.root");
	TTree *recotree8 = (TTree *) recofile8->Get("recotree");
	recotree8->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries8 = recotree8->GetEntries();

	for (int i =0; i < dutEntries8; i++){
		recotree8->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs8->Fill(stubs_module_1->at(k));
		}
	}


TFile *recofile9 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_526_22deg_120vcth.root");
	TTree *recotree9 = (TTree *) recofile9->Get("recotree");
	recotree9->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries9 = recotree9->GetEntries();

	for (int i =0; i < dutEntries9; i++){
		recotree9->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs9->Fill(stubs_module_1->at(k));
		}
	}

TFile *recofile10 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_533_32deg_120vcth.root");
	TTree *recotree10 = (TTree *) recofile10->Get("recotree");
	recotree10->SetBranchAddress("stubs_module_1", &stubs_module_1);
	

	int dutEntries10 = recotree10->GetEntries();

	for (int i =0; i < dutEntries10; i++){
		recotree10->GetEntry(i);
		
		unsigned int stub_size = stubs_module_1->size();

		for(unsigned int k = 0 ; k < stub_size ; ++k){
			h_stubs10->Fill(stubs_module_1->at(k));
		}
	}


/*
	TCanvas *c1 = new TCanvas("c1","c1",1200,1200);
	c1->Divide(4,4);
	c1->SetLogy();
c1->cd(1);
	h_stubs0->Draw();
c1->cd(2);
	h_stubs1->SetLineColor(2);
	h_stubs1->Draw();
c1->cd(3);
	h_stubs2->SetLineColor(3);
	h_stubs2->Draw();
c1->cd(4);
	h_stubs3->SetLineColor(4);
	h_stubs3->Draw();
c1->cd(5);
	h_stubs4->Draw();
c1->cd(6);
	h_stubs5->Draw();
c1->cd(7);
	h_stubs6->Draw();
c1->cd(8);
	h_stubs7->Draw();
c1->cd(9);
	h_stubs8->Draw();
c1->cd(10);
	h_stubs9->Draw();
c1->cd(11);
	h_stubs10->Draw();*/

	TCanvas *c0 = new TCanvas("c0","c0",400,400);
	c0->SetLogy();
	h_stubs0->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs0->Draw();
	c0->Print("stubs_0.pdf","pdf");

	TCanvas *c1 = new TCanvas("c1","c1",400,400);
	c1->SetLogy();
	h_stubs1->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs1->Draw();
	c1->Print("stubs_1.pdf","pdf");


	TCanvas *c2 = new TCanvas("c2","c2",400,400);
	c2->SetLogy();
	h_stubs2->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs2->Draw();
	c2->Print("stubs_2.pdf","pdf");

	TCanvas *c3 = new TCanvas("c3","c3",400,400);
	c3->SetLogy();
	h_stubs3->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs3->Draw();
	c3->Print("stubs_3.pdf","pdf");


	TCanvas *c4 = new TCanvas("c4","c4",400,400);
	c4->SetLogy();
	h_stubs4->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs4->Draw();
	c4->Print("stubs_4.pdf","pdf");


	TCanvas *c5 = new TCanvas("c5","c5",400,400);
	c5->SetLogy();
	h_stubs5->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs5->Draw();
	c5->Print("stubs_5.pdf","pdf");


	TCanvas *c6 = new TCanvas("c6","c6",400,400);
	c6->SetLogy();
	h_stubs6->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs6->Draw();
	c6->Print("stubs_6.pdf","pdf");


	TCanvas *c7 = new TCanvas("c7","c7",400,400);
	c7->SetLogy();
	h_stubs7->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs7->Draw();
	c7->Print("stubs_7.pdf","pdf");


	TCanvas *c8 = new TCanvas("c8","c8",400,400);
	c8->SetLogy();
	h_stubs8->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs8->Draw();
	c8->Print("stubs_8.pdf","pdf");

	TCanvas *c9 = new TCanvas("c9","c9",400,400);
	c9->SetLogy();
	h_stubs9->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs9->Draw();
	c9->Print("stubs_9.pdf","pdf");



	TCanvas *c10 = new TCanvas("c10","c10",400,400);
	c10->SetLogy();
	h_stubs10->SetLineColor(1);
	//h_stubs0->SetFillColor(1);
	h_stubs10->Draw();
	c10->Print("stubs_10.pdf","pdf");

// 	h_stubs8->SetLineColor(2);
// 	h_stubs8->SetFillColor(2);
// 	h_stubs8->Draw("sames");

// 	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
// 		leg->SetFillColor(0);
// 		//leg->SetLineColor(0);
// 		leg->AddEntry(h_stubs0,"0[deg]","F");
// 		leg->AddEntry(h_stubs8,"15[deg]","F");
// 		leg->Draw();

}
// ================================================== //
//                                                    //
//       pull normalization weights from QCD          //
//                                                    //   
// ================================================== //

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TROOT.h"
#include "TObject.h"

using namespace std;

// define name Tree in calcEntries()

void calcEntries(string  flavour, string category, vector<float> & entries, string dir, string fix);

void NormalizationWeights(){
  
  string dir = "/scratch/vlambert/TMVA/QCD_flat_skimmed_combined";
  string fix = "skimmed_20k_eachptetabin_CombinedSVV2";

  //if(argc == 2 || argc == 3) dir = argv[1];
  //if(argc == 3) fix = argv[2];
		
  cout << "calculate bias from rootfiles in dir " << dir << endl;
  
  string flavour[3] = {"C", "B", "DUSG"};
  string cat[3] = {"NoVertex", "PseudoVertex", "RecoVertex"};
  
  vector<float> entries[9];
  
  int nIter =0;
  
  for(int j=0; j<3; j++){//loop on categories
    for(int i =0; i<3; i++){//loop on flavours
      calcEntries(flavour[i], cat[j], entries[nIter], dir, fix);
      //for(int k =0 ; k<entries[nIter].size(); k++) cout<<flavour[i]<<"   "<<cat[j]<<"  "<<entries[nIter][k]<<endl; 
      nIter++;
    }
  }
  
  ofstream myfile;
  string filename = "";
  for(int j=0; j<3; j++){//loop on categories	
    for(int k=0; k<3; k++){//loop on B and light
      cout<<"***************   "<<cat[j]<<"_"<<flavour[k]<<"   ***************"<<endl;
      filename = cat[j]+"_"+flavour[k]+"_qcd.txt";
      myfile.open (filename.c_str());
      for(int l = 0; l<19; l++ ){// loop on pt/eta bins
	int indexb = k+j*3;
	float bias = (float)(1./entries[indexb][l]);
	myfile << "<bias>"<<bias<<"</bias>\n";
	cout<<"<bias>"<<bias<<"</bias>"<<endl; 
      }
      myfile.close();
    }
  }
	
	//return 0;
}


void calcEntries(string flavour, string  category,  vector<float> & entries, string dir, string fix){	
  TFile * f = TFile::Open((dir+"/"+fix+category+"_"+flavour+".root").c_str());
  
  cout << "opening file: " << (dir+"/"+fix+category+"_"+flavour+".root").c_str() << endl;
  
  f->cd();
  TTree * t =(TTree*)f->Get("tree");
  
  //definition of pt and eta bins should be the same as in the Train*xml files!!!
  entries.push_back(t->GetEntries("jetPt>15&&jetPt<40&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>15&&jetPt<40&&TMath::Abs(jetEta)<2.1&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>15&&jetPt<40&&(!(TMath::Abs(jetEta)<2.1))"));
  entries.push_back(t->GetEntries("jetPt>40&&jetPt<60&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>40&&jetPt<60&&TMath::Abs(jetEta)<2.1&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>40&&jetPt<60&&(!(TMath::Abs(jetEta)<2.1))"));
  entries.push_back(t->GetEntries("jetPt>60&&jetPt<90&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>60&&jetPt<90&&TMath::Abs(jetEta)<2.1&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>60&&jetPt<90&&(!(TMath::Abs(jetEta)<2.1))"));
  entries.push_back(t->GetEntries("jetPt>90&&jetPt<150&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>90&&jetPt<150&&TMath::Abs(jetEta)<2.1&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>90&&jetPt<150&&(!(TMath::Abs(jetEta)<2.1))"));
  entries.push_back(t->GetEntries("jetPt>150&&jetPt<400&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>150&&jetPt<400&&TMath::Abs(jetEta)<2.1&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>150&&jetPt<400&&(!(TMath::Abs(jetEta)<2.1))"));
  entries.push_back(t->GetEntries("jetPt>400&&jetPt<600&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>400&&jetPt<600&&(!(TMath::Abs(jetEta)<1.2))"));
  entries.push_back(t->GetEntries("jetPt>600&&TMath::Abs(jetEta)<1.2"));
  entries.push_back(t->GetEntries("jetPt>600&&(!(TMath::Abs(jetEta)<1.2))"));
  
  cout << "jets have been put in pt and eta bins now" << endl;
	    
}




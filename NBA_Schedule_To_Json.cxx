#include<iostream>
#include<fstream>
#include<sstream>
#include<TMath.h>
#include<TGraph.h>
#include<TGaxis.h>
#include<TMultiGraph.h>
#include<TCanvas.h>
#include<TArrow.h>
#include<TAttLine.h>
#include "TMath.h"
#include "TPaveText.h"
#include <vector>
#include<TAxis.h>
#include<TH1.h>
#include<TH1F.h>
#include<TH2.h>
#include<TH3.h>
#include<TF1.h>
#include<TChain.h>
#include<TROOT.h>
#include<TFile.h>
#include<TMinuit.h>
#include<TVirtualFitter.h>
#include<TLatex.h>
#include<TStyle.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraphAsymmErrors.h>
#include "TLegend.h"
#include<TRandom3.h>
#include <TVector3.h>
#include <string>
#include <TSystem.h>

using namespace std;

string GetShort(string Name){

  string Name_Short;

  
  if(Name=="Hawks"){ Name_Short="ATL";}
  if(Name=="Nets"){ Name_Short="BKN";}
  if(Name=="Celtics"){ Name_Short="BOS";}
  if(Name=="Hornets"){ Name_Short="CHA";}
  if(Name=="Bulls"){ Name_Short="CHI";}
  if(Name=="Cavaliers"){ Name_Short="CLE";}
  if(Name=="Mavericks"){ Name_Short="DAL";}
  if(Name=="Nuggets"){ Name_Short="DEN";}
  if(Name=="Pistons"){ Name_Short="DET";}
  if(Name=="Warriors"){ Name_Short="GS";}
  if(Name=="Rockets"){ Name_Short="HOU";}
  if(Name=="Pacers"){ Name_Short="IND";}
  if(Name=="Clippers"){ Name_Short="LAC";}
  if(Name=="Lakers"){ Name_Short="LAL";}
  if(Name=="Grizzlies"){ Name_Short="MEM";}
  if(Name=="Heat"){ Name_Short="MIA";}
  if(Name=="Bucks"){ Name_Short="MIL";}
  if(Name=="Timberwolves"){ Name_Short="MIN";}
  if(Name=="Pelicans"){ Name_Short="NO";}
  if(Name=="Knicks"){ Name_Short="NY";}
  if(Name=="Thunder"){ Name_Short="OKC";}
  if(Name=="Magic"){ Name_Short="ORL";}
  if(Name=="76ers"){ Name_Short="PHI";}
  if(Name=="Suns"){ Name_Short="PHX";}
  if(Name=="Trail Blazers"){ Name_Short="POR";}
  if(Name=="Spurs"){ Name_Short="SA";}
  if(Name=="Kings"){ Name_Short="SAC";}
  if(Name=="Raptors"){ Name_Short="TOR";}  
  if(Name=="Jazz"){ Name_Short="UTAH";}
  if(Name=="Wizards"){ Name_Short="WSH";}

  return Name_Short;

}

void NBA_Schedule_To_Json(Int_t Year = 2022, Int_t Month = 02, Int_t Day = 10){

  TString date = Form("%d",Year);
  if(Month<10){
    date = date + (TString)"0" + Form("%d",Month);
  }else{
    date = date + Form("%d",Month);
  }
  if(Day<10){
    date = date + (TString)"0" + Form("%d",Day);
  }else{
    date = date + Form("%d",Day);
  }
  
  const TString OutputFileName =(TString)"NBA_schedule.html";
  std::ofstream outputfile(OutputFileName,std::ios::out);
  outputfile << "{" << endl;
  outputfile << "\"info\": [" << endl;

  vector<string> *VarName = new vector<string>();
  vector<string> *TeamH = new vector<string>();
  vector<string> *TeamA = new vector<string>();
  vector<string> *TeamH_Short = new vector<string>();
  vector<string> *TeamA_Short = new vector<string>();
  vector<string> *GameId = new vector<string>();
  vector<string> *Time = new vector<string>();

  VarName->clear();
  TeamH->clear();
  TeamA->clear();
  TeamH_Short->clear();
  TeamA_Short->clear();
  GameId->clear();
  Time->clear();
  
  TString File = (TString)"/local/home/ar245054/AndroidAssests/HotPicks/macros/NBA_Data/2021_2022/schedule/Schedule_" + date + (TString)".csv";
  std::ifstream DataFile(File,std::ios::in);
  
  if(DataFile.is_open()){

    std::string line, colname;
    
    if(DataFile.good()){

      // Extract the first line in the file
      std::getline(DataFile, line);

      // Create a stringstream from line
      std::stringstream ss(line);

      // Extract each column name
      while(std::getline(ss, colname, ',')){
	
	// Initialize and add <colname, int vector> pairs to result
	VarName->push_back(colname);
      }
	  
      // Read data, line by line
      while(std::getline(DataFile, line)){

	      
	// Create a stringstream of the current line
	std::stringstream ss3(line);
	
	// Keep track of the current column index
	unsigned int colIdx = 0;

	while(std::getline(ss3, colname, ',')){

	  if(colIdx < VarName->size()){
	    if(VarName->at(colIdx)=="TeamH"){
	      TeamH->push_back(colname);
	      string temp = GetShort(colname);
	      TeamH_Short->push_back(temp);
	      //cout << colname << endl;
	    }
	    if(VarName->at(colIdx)=="TeamA"){
	      TeamA->push_back(colname);
	      string temp = GetShort(colname);
	      TeamA_Short->push_back(temp);
	      //cout << colname << endl;
	    }
	    if(VarName->at(colIdx)=="Id"){
	      GameId->push_back(colname);
	      //cout << colname << endl;
	    }
	    if(VarName->at(colIdx)=="Time"){
	      Time->push_back(colname);
	      //cout << colname << endl;
	    }
	  }else{
	    cout << "Problem in the variables names" << endl;
	  }
	  colIdx++;
	}
      }
    }

    //Write Json file
    for(UInt_t i = 0 ; i < GameId->size() ; i++){
      if(i==0){
	outputfile << "{" << endl;
      }else{
	outputfile << "}," << endl;
	outputfile << "{" << endl;
      }
      outputfile  << "\"time\": \"" << Time->at(i) << "\"," << endl;
      outputfile  << "\"teamh\": \"" << TeamH->at(i) << "\"," << endl;
      outputfile  << "\"teama\": \"" << TeamA->at(i) << "\"," << endl;
      outputfile  << "\"teamhshort\": \"" << TeamH_Short->at(i) << "\"," << endl;
      outputfile  << "\"teamashort\": \"" << TeamA_Short->at(i) << "\"," << endl;
      outputfile  << "\"gameid\": \"" << GameId->at(i) << "\"" << endl;
    
    }
    outputfile << "}" << endl;
  }else{ //if no games
    outputfile << "{" << endl;
    outputfile  << "\"time\": \"" << "Today" << "\"," << endl;
    outputfile  << "\"teamh\": \"" << "No Game" << "\"," << endl;
    outputfile  << "\"teama\": \"" << "No Game" << "\"," << endl;
    outputfile  << "\"teamhshort\": \"" << "" << "\"," << endl;
    outputfile  << "\"teamashort\": \"" << "" << "\"," << endl;
    outputfile  << "\"gameid\": \"" << "" << "\"" << endl;
    outputfile << "}" << endl;
  }
  
  delete VarName;
  delete TeamH;
  delete TeamA;
  delete TeamA_Short;
  delete TeamH_Short;
  delete GameId;
  delete Time;
  
  outputfile << "]" << endl;
  outputfile << "}" << endl;
  outputfile.close();
}


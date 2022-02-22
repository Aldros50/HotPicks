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

void NBA_Data_To_Json(){

  vector<string> *TEAMS = new vector<string>();

  TEAMS->push_back("ATL");
  TEAMS->push_back("BKN");
  TEAMS->push_back("BOS");
  TEAMS->push_back("CHA");
  TEAMS->push_back("CHI");
  TEAMS->push_back("CLE");
  TEAMS->push_back("DAL");
  TEAMS->push_back("DEN");
  TEAMS->push_back("DET");
  TEAMS->push_back("GS");
  TEAMS->push_back("HOU");
  TEAMS->push_back("IND");
  TEAMS->push_back("LAC");
  TEAMS->push_back("LAL");
  TEAMS->push_back("MEM");
  TEAMS->push_back("MIA");
  TEAMS->push_back("MIL");
  TEAMS->push_back("MIN");
  TEAMS->push_back("NO");
  TEAMS->push_back("NY");
  TEAMS->push_back("OKC");
  TEAMS->push_back("ORL");
  TEAMS->push_back("PHI");
  TEAMS->push_back("PHX");
  TEAMS->push_back("POR");
  TEAMS->push_back("SA");
  TEAMS->push_back("SAC");
  TEAMS->push_back("TOR");  
  TEAMS->push_back("UTAH");
  TEAMS->push_back("WSH");
  //Getting GameId Collection
  vector<string> *GameId = new vector<string>();
  TString FileId = (TString)"/local/home/ar245054/AndroidAssests/HotPicks/macros/NBA_GameId_Collection_2021_2022.dat";
  std::ifstream GameIdFile(FileId,std::ios::in);
  if(GameIdFile.is_open()){

    std::string line, colname;
    
    if(GameIdFile.good()){
      // Read data, line by line
      while(std::getline(GameIdFile, line)){
	
	// Create a stringstream of the current line
	std::stringstream ss3(line);
	
	while(std::getline(ss3, colname, ',')){
	  
	  GameId->push_back(colname);
	  //cout << colname << endl;
	}
      }
    }
  }

  cout << "Number of GameID Collected : " << GameId->size() << endl;
  
  for(UInt_t kk=0 ; kk<TEAMS->size() ; kk++){

    TString TEAM = TEAMS->at(kk);
    
    const TString OutputFileName = TEAM + (TString)".html";
    std::ofstream outputfile(OutputFileName,std::ios::out);
    outputfile << "{" << endl;
    outputfile << "\"info\": [" << endl;
    
    cout << "::::::::::" << TEAM << " ::::::::::" << endl;
  
    vector<string> *VarName = new vector<string>();
    vector<string> *Id = new vector<string>();
    vector<string> *IdPlayed = new vector<string>();
    vector<string> *Team = new vector<string>();
    vector<string> *Player = new vector<string>();
    vector<string> *OppTeam = new vector<string>();
    vector<double> *REB = new vector<double>();
    vector<double> *PTS = new vector<double>();
    vector<double> *AST = new vector<double>();
    vector<double> *MIN = new vector<double>();
    vector<double> *TPT = new vector<double>();
    vector<double> *PRA = new vector<double>();
  
    Int_t Counter=0;
    Int_t Found_Team=0;
  
    //loop over previous games
    for(Int_t i=GameId->size() ; i>0 ; i--){

      //Init
      Team->clear();
      VarName->clear();

      TString File = (TString)"/local/home/ar245054/AndroidAssests/HotPicks/macros/NBA_Data/2021_2022/NBA_ID_" + GameId->at(i-1) + (TString)".csv";
      //cout << Counter << "  " << File << endl;
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
	    Team->push_back(colname);
	  }

	  if(Team->at(0)==TEAM || Team->at(1)==TEAM){
	    Found_Team=1;
	    Id->push_back(GameId->at(i-1));
	    	  
	    if(Team->at(0)==TEAM){ //if first team in file

	      // Extract the second line in the file
	      std::getline(DataFile, line);

	      // Create a stringstream from line
	      std::stringstream ss1(line);

	      // Extract each column name
	      while(std::getline(ss1, colname, ',')){
	
		// Initialize and add <colname, int vector> pairs to result
		// if(TEAM==colname){
		// 	cout << colname << endl;
		// 	cout << "Problem" << endl;
		// }
	      }

	      // Extract the third line in the file
	      std::getline(DataFile, line);

	      // Create a stringstream from line
	      std::stringstream ss2(line);

	      // Extract each column name
	      while(std::getline(ss2, colname, ',')){
	
		// Initialize and add <colname, int vector> pairs to result
		VarName->push_back(colname);
		//cout << colname << endl;
	      }
	  
	      Int_t End = 0;
	    
	      // Read data, line by line
	      while(std::getline(DataFile, line)){

		if(line.size()<10){
		  End = 1;
		}
	      
		if(End==0){
		
		  // Create a stringstream of the current line
		  std::stringstream ss3(line);
        
		  // Keep track of the current column index
		  unsigned int colIdx = 0;

		  while(std::getline(ss3, colname, ',')){
		    if(colIdx < VarName->size()){
		      if(VarName->at(colIdx)=="Name"){
			//To clean the names
			int sizestr = colname.length();
			string Pos = colname.substr(sizestr-1,sizestr);
			string PosMinus1 = colname.substr(sizestr-2,sizestr-1);
			if(Pos=="F" || Pos=="G"){
			  if(PosMinus1 == "PG" || PosMinus1 == "SG" || PosMinus1 == "PF" || PosMinus1 == "SF"){
			    colname = colname.substr(0,sizestr-2);
			  }else{
			    colname = colname.substr(0,sizestr-1);
			  }
			}else if(Pos=="C"){
			  colname = colname.substr(0,sizestr-1);
			}
			sizestr = colname.length();
			colname = colname.substr(0,(int)sizestr*0.5);
			sizestr = colname.length();
			string test = colname.substr(sizestr-3,sizestr);
			if(test=="Jr." || test=="III" || test=="Sr."){
			  //cout << test << endl;
			  colname = colname.substr(0,sizestr-4);
			  //cout << colname << endl;
			}
			if(test==" IV"){
			  //cout << test << endl;
			  colname = colname.substr(0,sizestr-3);
			  //cout << colname << endl;
			}
			Player->push_back(colname);
			OppTeam->push_back(Team->at(1));
			IdPlayed->push_back(GameId->at(i-1));
		      }
		      if(VarName->at(colIdx)=="REB"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			REB->push_back(v);
		      }
		      if(VarName->at(colIdx)=="PTS"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			PTS->push_back(v);
		      }
		      if(VarName->at(colIdx)=="AST"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			AST->push_back(v);
		      }
		      if(VarName->at(colIdx)=="MIN"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			MIN->push_back(v);
		      }
		      if(VarName->at(colIdx)=="3PT"){
			int sizestr = colname.length();
			string TPTstr;
			for(Int_t k=0 ; k<sizestr ; k++){
			  if(colname[k]=='-'){
			    TPTstr = colname.substr(0,k);
			  }
			}
			int n = TPTstr.length();
			char colname_char[n+1];
		     	strcpy(colname_char,TPTstr.c_str());
			double v = atof(colname_char);
			TPT->push_back(v);
		      }
		    }else{
		      cout << "Problem in the variables names" << endl;
		    }
		    colIdx++;
		  }
		}
	      }
	    
	    }else{ //if we are the second team in the file

	      // Extract the second line in the file
	      std::getline(DataFile, line);

	      // Create a stringstream from line
	      std::stringstream ss1(line);

	      // Extract each column name
	      while(std::getline(ss1, colname, ',')){
	
		// Initialize and add <colname, int vector> pairs to result
	      }

	      // Extract the third line in the file
	      std::getline(DataFile, line);

	      // Create a stringstream from line
	      std::stringstream ss2(line);

	      // Extract each column name
	      while(std::getline(ss2, colname, ',')){
	
		// Initialize and add <colname, int vector> pairs to result
		VarName->push_back(colname);
		//cout << colname << endl;
	      }
	  
	      Int_t End = 0;
	    
	      // Read data, line by line
	      while(std::getline(DataFile, line)){

		if(End==2 && line.size()>10){
		  End = 3;
		}
		if(End==1 && line.size()>10){
		  End = 2;
		}
		if(line.size()<10){
		  End = 1;
		}
	    	      
		if(End==3){
		
		  // Create a stringstream of the current line
		  std::stringstream ss3(line);
        
		  // Keep track of the current column index
		  unsigned int colIdx = 0;

		  while(std::getline(ss3, colname, ',')){
		    if(colIdx < VarName->size()){
		      if(VarName->at(colIdx)=="Name"){
			//To clean the names
			int sizestr = colname.length();
			string Pos = colname.substr(sizestr-1,sizestr);
			string PosMinus1 = colname.substr(sizestr-2,sizestr-1);
			if(Pos=="F" || Pos=="G"){
			  if(PosMinus1 == "PG" || PosMinus1 == "SG" || PosMinus1 == "PF" || PosMinus1 == "SF"){
			    colname = colname.substr(0,sizestr-2);
			  }else{
			    colname = colname.substr(0,sizestr-1);
			  }
			}else if(Pos=="C"){
			  colname = colname.substr(0,sizestr-1);
			}
			// if(Pos=="F" || Pos=="G"){
			//   colname = colname.substr(0,sizestr-2);
			// }else if(Pos=="C"){
			//   colname = colname.substr(0,sizestr-1);
			// }
			sizestr = colname.length();
			colname = colname.substr(0,(int)sizestr*0.5);
			Player->push_back(colname);
			OppTeam->push_back(Team->at(0));
			IdPlayed->push_back(GameId->at(i-1));
		      }
		      if(VarName->at(colIdx)=="REB"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			REB->push_back(v);
		      }
		      if(VarName->at(colIdx)=="PTS"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			PTS->push_back(v);
		      }
		      if(VarName->at(colIdx)=="AST"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			AST->push_back(v);
		      }
		      if(VarName->at(colIdx)=="MIN"){
			int n = colname.length();
			char colname_char[n+1];
			strcpy(colname_char,colname.c_str());
			double v = atof(colname_char);
			MIN->push_back(v);
		      }
		      if(VarName->at(colIdx)=="3PT"){
			int sizestr = colname.length();
			string TPTstr;
			for(Int_t k=0 ; k<sizestr ; k++){
			  if(colname[k]=='-'){
			    TPTstr = colname.substr(0,k);
			  }
			}
			int n = TPTstr.length();
			char colname_char[n+1];
		     	strcpy(colname_char,TPTstr.c_str());
			double v = atof(colname_char);
			TPT->push_back(v);
		      }
		    }else{
		      cout << "Problem in the variables names" << endl;
		    }
		    colIdx++;
		  }
		}
	      }
	    
	    }
	  
	    Counter++;
	  }
	}

	DataFile.close();
      
      }else{
	std::cerr << "Error:: The File : '" << File << "' was not found" << std::endl;
      }
    }
  
    
    //Computing variables
    for(UInt_t i=0 ; i<Player->size() ; i++){
      PRA->push_back(PTS->at(i)+AST->at(i)+REB->at(i));
    }
    
    //Analysis
    vector<string> *Player_ = new vector<string>();
    vector<int> *GameN = new vector<int>();
    vector<double> *MinAve = new vector<double>();
    vector<double> *TptAve = new vector<double>();
    vector<double> *PtsAve = new vector<double>();
    vector<double> *RebAve = new vector<double>();
    vector<double> *AstAve = new vector<double>();
    vector<double> *RebBet = new vector<double>();
    vector<double> *AstBet = new vector<double>();
    vector<double> *Pm3Bet = new vector<double>();
    vector<double> *RebBet_DK = new vector<double>();
    vector<double> *AstBet_DK = new vector<double>();
    vector<double> *Pm3Bet_DK = new vector<double>();
    vector<double> *PtsBet_DK = new vector<double>();
    Double_t Pts[30][100]; //[PlayerId][GameNbr]
    Double_t Min[30][100];
    Double_t Tpt[30][100];
    Double_t Ast[30][100];
    Double_t Reb[30][100];
    string Opp[30][100];
    int PlayerNumber[30];

    string OppList[100];

    //Init OppList
    for(Int_t j=0 ; j<Id->size() ; j++){
      OppList[j] = "";
    }
    
    //Getting oponents
    for(Int_t j=0 ; j<Id->size() ; j++){
      for(UInt_t i=0 ; i<Player->size() ; i++){
	if(Id->at(j)==IdPlayed->at(i)){
	  OppList[j] = OppTeam->at(i);
	}
      }
    }

    for(Int_t j=0 ; j<Id->size() ; j++){
      cout << OppList[j] << endl;
      cout << Id->at(j) << endl;
    }

      
    for(Int_t i=0 ; i<30 ; i++){
      PlayerNumber[i] = 0;
      for(Int_t j=0 ; j<100 ; j++){
	Pts[i][j] = 0;
	Min[i][j] = 0;
	Tpt[i][j] = 0;
	Ast[i][j] = 0;
	Reb[i][j] = 0;
	Opp[i][j] = OppList[j];
      }
    }
    
    Int_t FoundPlayer = 0;
    Int_t PlayerCounter = 0;
  
    for(UInt_t i=0 ; i<Player->size() ; i++){

      //cout << Player->at(i) << "  " << IdPlayed->at(i) << endl;

      FoundPlayer = 0;
    
      for(UInt_t j=0 ; j<Player_->size() ; j++){

	if(Player->at(i)==Player_->at(j)){
	  
	  // if(GameN->at(j)<5){ //Last 5 games

	  //   Pts[j][GameN->at(j)] = PTS->at(i);
	  //   Ast[j][GameN->at(j)] = AST->at(i);
	  //   Reb[j][GameN->at(j)] = REB->at(i);
	  //   Min[j][GameN->at(j)] = MIN->at(i);
	  //   Opp[j][GameN->at(j)] = OppTeam->at(i);
	  
	  // }
	  
	  for(Int_t k=0 ; k<Id->size() ; k++){
	    if(Id->at(k)==IdPlayed->at(i)){
	      Pts[j][k] = PTS->at(i);
	      Ast[j][k] = AST->at(i);
	      Reb[j][k] = REB->at(i);
	      Min[j][k] = MIN->at(i);
	      Tpt[j][k] = TPT->at(i);
	      //Opp[PlayerCounter][k] = OppTeam->at(i);
	    }
	  }
	
	  GameN->at(j) = GameN->at(j)+1;
       
	
	  FoundPlayer = 1;
	}

      }

      if(FoundPlayer==0){ //Player not listed yet
	//cout << Player->at(i) << endl;
	Player_->push_back(Player->at(i));
	for(Int_t k=0 ; k<Id->size() ; k++){
	  if(Id->at(k)==IdPlayed->at(i)){
	    Pts[PlayerCounter][k] = PTS->at(i);
	    Ast[PlayerCounter][k] = AST->at(i);
	    Reb[PlayerCounter][k] = REB->at(i);
	    Min[PlayerCounter][k] = MIN->at(i);
	    Tpt[PlayerCounter][k] = TPT->at(i);
	    //PlayerNumber[PlayerCounter] = 0;
	    //Opp[PlayerCounter][k] = OppTeam->at(i);
	  }
	}
	GameN->push_back(1.);
	PlayerCounter++;
      }
    
    }

    //Compute Averages
    for(Int_t i = 0 ; i < Player_->size() ; i++){
      cout << Player_->at(i) << "   " << GameN->at(i) << endl;
      Int_t jmax = 5;
      // if(jmax>GameN->at(i)){
      // 	jmax = GameN->at(i);
      // }
      int SumMin = 0;
      int SumPts = 0;
      int SumAst = 0;
      int SumReb = 0;
      int SumTpt = 0;
      for(Int_t j=0 ; j<Id->size() ; j++){
	//cout << j << "   " << Min[i][j] << endl;
	SumMin+=Min[i][j];
	SumPts+=Pts[i][j];
	SumAst+=Ast[i][j];
	SumReb+=Reb[i][j];
	SumTpt+=Tpt[i][j];
      }
      MinAve->push_back((double)SumMin/GameN->at(i));
      PtsAve->push_back((double)SumPts/GameN->at(i));
      TptAve->push_back((double)SumTpt/GameN->at(i));
      AstAve->push_back((double)SumAst/GameN->at(i));
      RebAve->push_back((double)SumReb/GameN->at(i));
    }
    
    //Reorder List of Players
    for(Int_t i = 0 ; i < Player_->size()-1 ; i++){
      for(Int_t j = i+1 ; j < Player_->size() ; j++){
    	//if(MinAve->at(i)<MinAve->at(j)){
    	if(Min[i][0]<Min[j][0]){// order with min of last game
    	  string stemp;
    	  int itemp;
    	  double dtemp;
    	  //Name
    	  stemp = Player_->at(i);
    	  Player_->at(i) = Player_->at(j);
    	  Player_->at(j) = stemp;
    	  //Nbr games
    	  itemp = GameN->at(i);
    	  GameN->at(i) = GameN->at(j);
    	  GameN->at(j) = itemp;
    	  //AveMin
    	  dtemp = MinAve->at(i);
    	  MinAve->at(i) = MinAve->at(j);
    	  MinAve->at(j) = dtemp;
    	  //AveTpt
    	  dtemp = TptAve->at(i);
    	  TptAve->at(i) = TptAve->at(j);
    	  TptAve->at(j) = dtemp;
    	  //AvePts
    	  dtemp = PtsAve->at(i);
    	  PtsAve->at(i) = PtsAve->at(j);
    	  PtsAve->at(j) = dtemp;
    	  //AveAst
    	  dtemp = AstAve->at(i);
    	  AstAve->at(i) = AstAve->at(j);
    	  AstAve->at(j) = dtemp;
    	  //AveReb
    	  dtemp = RebAve->at(i);
    	  RebAve->at(i) = RebAve->at(j);
    	  RebAve->at(j) = dtemp;
    	  for(Int_t k=0 ; k<10 ; k++){
    	    stemp = Opp[i][k];
    	    Opp[i][k] = Opp[j][k];
    	    Opp[j][k] = stemp;
    	    itemp = Pts[i][k];
    	    Pts[i][k] = Pts[j][k];
    	    Pts[j][k] = itemp;
    	    itemp = Min[i][k];
    	    Min[i][k] = Min[j][k];
    	    Min[j][k] = itemp;
    	    itemp = Tpt[i][k];
    	    Tpt[i][k] = Tpt[j][k];
    	    Tpt[j][k] = itemp;
    	    itemp = Reb[i][k];
    	    Reb[i][k] = Reb[j][k];
    	    Reb[j][k] = itemp;
    	    itemp = Ast[i][k];
    	    Ast[i][k] = Ast[j][k];
    	    Ast[j][k] = itemp;
    	  }
    	}
      }
    }
    //Get Bets info from Winamax
    vector<string> *BET = new vector<string>();
    vector<string> *PLAYER = new vector<string>();
    vector<double> *VAL = new vector<double>();
  
    TString FileBet = (TString)"../macros/bets/winamax_"+TEAM+(TString)".csv";
  
    std::ifstream DataFileBet(FileBet,std::ios::in);
  
    if(DataFileBet.is_open()){

      std::string line, colname;
    
      if(DataFileBet.good()){

	// Read data, line by line
	while(std::getline(DataFileBet, line)){

	  // Create a stringstream of the current line
	  std::stringstream ss(line);
        
	  // Keep track of the current column index
	  unsigned int colIdx = 0;

	  while(std::getline(ss, colname, ',')){

	    if(colIdx==0){
	      PLAYER->push_back(colname);
	    }

	    if(colIdx==1){
	      BET->push_back(colname);
	    }
	    
	    if(colIdx==2){
	      int n = colname.length();
	      char colname_char[n+1];
	      strcpy(colname_char,colname.c_str());
	      double v = atof(colname_char);
	      VAL->push_back(v);
	    }
	  
	    colIdx++;
	  }
	}
      }
    
      DataFileBet.close();

    }else{
      std::cerr << "Error:: The File : 'winamax.csv' was not found" << std::endl;
    }
    
    for(Int_t j = 0 ; j < Player_->size() ; j++){
      RebBet->push_back(0.0);
      AstBet->push_back(0.0);
      Pm3Bet->push_back(0.0);
      
      for(Int_t i = 0 ; i < PLAYER->size() ; i++){
	//cout << PLAYER->at(i) << "   " << BET->at(i) << "   " << VAL->at(i) << endl;
	if(PLAYER->at(i)==Player_->at(j)){

	  if(BET->at(i)=="REB"){
	    RebBet->at(j) = VAL->at(i);
	  }else if(BET->at(i)=="AST"){
	    AstBet->at(j) = VAL->at(i);
	  }else if(BET->at(i)=="3PM"){
	    Pm3Bet->at(j) = VAL->at(i);
	  }
	}
      }
    }


    //Get Bets info from Draftking
    vector<string> *BET_DK = new vector<string>();
    vector<string> *PLAYER_DK = new vector<string>();
    vector<double> *VAL_DK = new vector<double>();
  
    TString FileBet_DK = (TString)"../macros/bets/draftking_"+TEAM+(TString)".csv";
  
    std::ifstream DataFileBet_DK(FileBet_DK,std::ios::in);
  
    if(DataFileBet_DK.is_open()){

      std::string line, colname;
    
      if(DataFileBet_DK.good()){

	// Read data, line by line
	while(std::getline(DataFileBet_DK, line)){

	  // Create a stringstream of the current line
	  std::stringstream ss(line);
        
	  // Keep track of the current column index
	  unsigned int colIdx = 0;

	  while(std::getline(ss, colname, ',')){

	    if(colIdx==0){
	      PLAYER_DK->push_back(colname);
	    }

	    if(colIdx==1){
	      BET_DK->push_back(colname);
	    }
	    
	    if(colIdx==2){
	      int n = colname.length();
	      char colname_char[n+1];
	      strcpy(colname_char,colname.c_str());
	      double v = atof(colname_char);
	      VAL_DK->push_back(v);
	    }
	  
	    colIdx++;
	  }
	}
      }
    
      DataFileBet_DK.close();

    }else{
      std::cerr << "Error:: The File : 'draftking.csv' was not found" << std::endl;
    }

    
    for(Int_t j = 0 ; j < Player_->size() ; j++){
      RebBet_DK->push_back(0.0);
      AstBet_DK->push_back(0.0);
      Pm3Bet_DK->push_back(0.0);
      PtsBet_DK->push_back(0.0);
      
      for(Int_t i = 0 ; i < PLAYER_DK->size() ; i++){
	//cout << PLAYER_DK->at(i) << "   " << BET_DK->at(i) << "   " << VAL_DK->at(i) << endl;
	if(PLAYER_DK->at(i)==Player_->at(j)){

	  if(BET_DK->at(i)=="REB"){
	    RebBet_DK->at(j) = VAL_DK->at(i);
	  }else if(BET_DK->at(i)=="AST"){
	    AstBet_DK->at(j) = VAL_DK->at(i);
	  }else if(BET_DK->at(i)=="3PM"){
	    Pm3Bet_DK->at(j) = VAL_DK->at(i);
	  }else if(BET_DK->at(i)=="PTS"){
	    PtsBet_DK->at(j) = VAL_DK->at(i);
	  }
	}
      }
    }
    
    //Read through player list
    for(Int_t i = 0 ; i < Player_->size() ; i++){
      if(i==0){
	outputfile << "{" << endl;
      }else{
	if(Min[i][0]+Min[i][1]+Min[i][2]+Min[i][3]+Min[i][4]!=0){
	  outputfile << "}," << endl;
	  outputfile << "{" << endl;
	}
      }
      if(Min[i][0]+Min[i][1]+Min[i][2]+Min[i][3]+Min[i][4]!=0){
	outputfile  << "\"name\": \"" << Player_->at(i) << "\"," << endl;
	outputfile  << "\"avepts\": \"" << Form("%0.1f",PtsAve->at(i)) << "\"," << endl;
	outputfile  << "\"aveast\": \""<< Form("%0.1f",AstAve->at(i)) << "\"," << endl;
	outputfile  << "\"avereb\": \""<< Form("%0.1f",RebAve->at(i)) << "\"," << endl;
	outputfile  << "\"avemin\": \""<< Form("%0.1f",MinAve->at(i)) << "\"," << endl;
	outputfile  << "\"avepm\": \""<< Form("%0.1f",TptAve->at(i)) << "\"," << endl;
	outputfile  << "\"betreb\": \""<< Form("%0.1f",RebBet->at(i)) << "\"," << endl;
	outputfile  << "\"betast\": \""<< Form("%0.1f",AstBet->at(i)) << "\"," << endl;
	outputfile  << "\"bet3pm\": \""<< Form("%0.1f",Pm3Bet->at(i)) << "\"," << endl;
	outputfile  << "\"betrebdk\": \""<< Form("%0.1f",RebBet_DK->at(i)) << "\"," << endl;
	outputfile  << "\"betastdk\": \""<< Form("%0.1f",AstBet_DK->at(i)) << "\"," << endl;
	outputfile  << "\"bet3pmdk\": \""<< Form("%0.1f",Pm3Bet_DK->at(i)) << "\"," << endl;
	outputfile  << "\"betptsdk\": \""<< Form("%0.1f",PtsBet_DK->at(i)) << "\"," << endl;

	for(Int_t j = 0 ; j < Id->size() ; j++){ //all games

	  //if(j<GameN->at(i)){
	  //cout << GameN->at(i) << endl;
	  outputfile  << "\"opp" << j << "\": \""<< Opp[i][j] << "\"," << endl;
	  outputfile  << "\"pts" << j << "\": \""<< Pts[i][j] << "\"," << endl;
	  outputfile  << "\"ast" << j << "\": \""<< Ast[i][j] << "\"," << endl;
	  outputfile  << "\"reb" << j << "\": \""<< Reb[i][j] << "\"," << endl;
	  outputfile  << "\"pm" << j << "\": \""<< Tpt[i][j] << "\"," << endl;
	  //if(j<4 && j!=(GameN->at(i)-1)){
	  if(j<(Id->size()-1)){
	    outputfile  << "\"min" << j << "\": \""<< Min[i][j] << "\"," << endl;
	  }else{
	    outputfile  << "\"min" << j << "\": \""<< Min[i][j] << "\"" << endl;
	  }
	  // outputfile << "Pts :  " << Pts[i][j] << endl;
	  // outputfile << "Ast :  " << Ast[i][j] << endl;
	  // outputfile << "Reb :  " << Reb[i][j] << endl;
	  // outputfile << "Min :  " << Min[i][j] << endl;
	  
	  
	  //}
	
	}
      }
    }

    outputfile << "}" << endl;
    
    if(Found_Team==0){
      cout << "Didn't find the team stats" << endl;
    }

    cout << endl;

    delete Team;
    delete OppTeam;
    delete VarName;
    delete Player;
    delete REB;
    delete PTS;
    delete AST;
    delete PRA;
    delete Player_;
    delete GameN;

 outputfile << "]" << endl;
  outputfile << "}" << endl;
 outputfile.close();
 }

 
  
  // outputfile << "\\end{document}" << endl;
 
  
  // gSystem->Exec((TString)"pdflatex "+OutputFileName);
  

}


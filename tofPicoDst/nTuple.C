#include "iostream.h"


// Forward the class declarations for StChain and St_db_Maker
class     StChain;
class     St_db_Maker;

void loadLibs();

void nTuple(const Char_t *fileList = "test.lis",
                   const Char_t *ntuplename = "testing.ntuple.root")
{
  
  StChain  *chain = 0;
  St_db_Maker *dbMk = 0;

  Int_t iEvt = 0, istat = 0;


  Int_t nEvents = 1000000;
  Int_t nfiles = 1000;

  //
  // First load some shared libraries we need
  //
  loadLibs();

  // create the chain
  chain  = new StChain("StChain");

  // create the StMuDstMaker
  StMuDstMaker *muDstMaker = new StMuDstMaker(  0,
                                                0,
                                                "",
                                                fileList,
                                                "MuDst.root",
                                                nfiles
                                              );


  // Initialize the database
  cout << endl << "============  Data Base =========" << endl;
  dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb","StarDb");

  // Setup the nTuple Maker
  StBTofNtupleMaker *btofNtuple = new StBTofNtupleMaker(  "btofNtuple", 
                                                          ntuplename
                                                        );
  // set nTupler options
  btofNtuple->SetDebug(0); 
  btofNtuple->setMuDstIn(kTRUE);


  // Initialize chain
  Int_t iInit = chain->Init();
  
  // ensure that the chain initializes
  if ( iInit ) 
    chain->Fatal(iInit,"on init");

  // print the chain status
  chain->PrintInfo();


  //
  // Event loop
  //
  int istat = 0, i = 1;


  while ( i <= nEvents && istat != 2 ){
    cout << endl << "============================ Event " << i << " start ============================" << endl;
   
    // clear the chain state
    chain->Clear();

    // make the chain and get that status
    istat = chain->Make(i);

    if (istat == 2) {
      cout << "Last event processed. Status = " << istat << endl;
    } else if (istat == 3) {
      cout << "Error event processed. Status = " << istat << endl;
    }
     
     i++;
  }
  
  cout << endl << "============================ Event " << ( i - 1 ) << " finished ============================" << endl;

  //
  // Chain Finish
  //
  if (nEvents > 1) {
    chain->Finish();
  }

  delete chain;

  

}






void loadLibs(){


  if (gClassTable->GetID("TTable") < 0) {
    gSystem->Load("libStar");
    gSystem->Load("libPhysics");
  }  
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StarMagField");
  gSystem->Load("StMagF");
  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StTpcDb");
  gSystem->Load("StDaqLib");
  gSystem->Load("StDbBroker");
  gSystem->Load("StDbUtilities");
  gSystem->Load("St_db_Maker");

  gSystem->Load("StEvent");
  gSystem->Load("StEventMaker");
  gSystem->Load("StarMagField");
 
  gSystem->Load("libGeom");
  gSystem->Load("St_g2t");
  gSystem->Load("xgeometry");
 
  gSystem->Load("St_geant_Maker");
  gSystem->Load("StBTofUtil");
  gSystem->Load("StBTofMatchMaker");
  gSystem->Load("StBTofNtupleMaker");


}
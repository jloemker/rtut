#include <stdio.h>
/*
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
*/

void TreeMacro(){
//reading file
TFile *dataFile = new TFile("data.root");
//pointer to the histogram 
TH1D * dataHist =(TH1D*)dataFile -> Get("combined");
//Draw histogram...Actually E2 should carry the error bars
dataHist -> Draw("E2");
//But running the program only creates the pdf
}

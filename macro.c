#include <stdio.h>
#include <functional>
/*
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
*/
void macro(){
//reading file
TFile *dataFile = new TFile("data.root");
//pointer to the histogram 
TH1D * dataHist =(TH1D*)dataFile -> Get("combined");
//Draw histogram...Actually E2 should carry the error bars
dataHist -> Draw("E2");

}
//Plot the function on top of each the dataset. What do you observe
/*
double function(double x, double * parameter){
    double result = parameter[0] + x*parameter[1] + parameter[2]*std::exp(-x*parameter[3]);
    return result;
}

double parameter[4] = {30, -0.06, 800, 0.01};

TF1 * func = new TF1(func,double function(double x, double * parameter), 3,300);
func -> Draw();
*/
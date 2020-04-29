#include <stdio.h>
#include <functional>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"



void macro(){

TH1::AddDirectory(ROOT::kFALSE);//sets global switch: disabling references
TFile dataFile = TFile("data.root");//reading file
/*Canvas: area mapped to a window under the control of the display manager
-Root sessions can have many of them open at any given time*/
TCanvas * c = new TCanvas("combined", "combined", 400, 500);//1st horiz. 2cond vert.

TH1F * dataHist =(TH1F*) dataFile -> Get("combined"); //pointer to the histogram 

TF1 * func_bg = new TF1("func_bg", "[0] + [1] * x + [2] * exp(- x + [3])" );//parametrisation + linesettings
func_bg -> SetParameters(30, -0.06, 800, 0.01);
func_bg -> SetLineColor(kBlue);
func_bg -> SetLineStyle(kDashDotted);

dataHist -> Draw("E2");//Draw histogram - !Actually E2 should carry the error bars
dataHist -> Fit("func_bg");//Draw our func_bg into same Histogram
}
//Plot the function on top of each the dataset. What do you observe

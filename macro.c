//Obviously I don't need to include anything
//using namespace


void macro(){
gStyle->SetOptFit(1111);
//Adds automaticall all information to the histogram
/*  p = 1; Probability
    c = 1; Chisquare/ndof
    e = 1; errors
    v = 1; default/new names/valus of parameter
*/
TH1::AddDirectory(ROOT::kFALSE);//sets global switch: disabling references

TFile dataFile = TFile("data.root");//reading file
/*Canvas: area mapped to a window under the control of the display manager
-Root sessions can have many of them open at any given time*/
TCanvas * c = new TCanvas("combined", "combined", 600, 500);//1st horiz. 2cond vert.

TH1F * dataHist =(TH1F*) dataFile.Get("combined"); //pointer to the histogram 

TF1 * func_bg = new TF1("func_bg", "[0] + [1] * x + [2] * exp(- x + [3])" );//parametrisation + linesettings
func_bg -> SetParNames("alpha","beta","gamma","delta");//To change default names (SetOptFit)
func_bg -> SetParameters(30, -0.06, 800, 0.01);
func_bg -> SetLineColor(kBlue);
func_bg -> SetLineStyle(kDashDotted);


//only for extra print in Terminal
cout << "Chisquare/ndof -> Background :  " << func_bg -> GetChisquare()/52 << "  The propability for this function to be compatible is 0 !" << endl;

TF1 * sign_func = new TF1("sign_func", "gaus");
//sign_func -> SetParNames("N","") lets check default
sign_func -> SetLineColor(kRed);
sign_func -> SetLineStyle(kDotted);
/* Gauss 3 Fitparameter: const, mu, sigma ----default Print in Histogram*/


dataHist -> Draw("E2");//Draw histogram - !Actually E2 should carry the error bars: Draw error bars with rectangles
dataHist -> Fit("func_bg");//Draw our func_bg into same Histogram
dataHist -> Fit("sign_func");

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
the last fit is shown in the histogram as well as the combined data
func_bg is not shown, but the values are printed in the terminal 
!!!Chisquare bg is = 0; ?! 
check out next step of the exercise and then carry the structure 
tp prevent vales to be overwritten. 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

}


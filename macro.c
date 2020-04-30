//Obviously I don't need to include anything
void macro(){
gStyle->SetOptFit(1111); //#########################################################################Opt_Fit_Functions
//Adds automaticall all information to the histogram
/*  p = 1; Probability
    c = 1; Chisquare/ndof
    e = 1; errors
    v = 1; default/new names/valus of parameter
*/
TH1::AddDirectory(ROOT::kFALSE);//sets global switch: disabling references

TFile dataFile = TFile("data.root");//#############################################################reading file
/*Canvas: area mapped to a window under the control of the display manager
-Root sessions can have many of them open at any given time*/
TCanvas * c = new TCanvas("combined", "combined", 600, 500);//1st horiz. 2cond vert.###############Visual_Setup
TH1F * dataHist =(TH1F*) dataFile.Get("combined"); 
dataHist -> Draw("E2");
//Draw histogram 
//- !Actually E2 should carry the error bars: Draw error bars with rectangles


//##################################################################################################Background
TF1 * func_bg = new TF1("func_bg", "[0] + [1] * x + [2] * exp(- x + [3])" );//parametrisation + linesettings
func_bg -> SetParNames("alpha","beta","gamma","delta");//To change default names in (SetOptFit)
func_bg -> SetParameters(30, -0.06, 800, 0.01);//init CHi2 value ?!
func_bg -> SetLineColor(kBlue);
func_bg -> SetLineStyle(kDashDotted);
//Fit's histogram (+Value in SetOptFit) and prints values in terminal
dataHist -> Fit("func_bg");
double * bg_para=func_bg->GetParameters(); //necessary for bg + sign parameter
//##################################################################################################Signal
TF1 * sign_func = new TF1("sign_func", "gaus", 150, 200) ;//should fit the resonance
sign_func -> SetParNames("N","mu","sigma") ;
sign_func -> SetParameters(0.004,170,1.0);
sign_func -> SetLineColor(kRed);
sign_func -> SetLineStyle(kDotted);
/* Gauss 3 Fitparameter: const, mu, sigma ----default Print in Histogram without fun_bla -> SetXy due to SetOptFit*/
dataHist -> Fit("sign_func");//Overrides past fit in the histogram - but terminal keeps ("func_bg")
double * sign_para=sign_func->GetParameters(); 

TH1F * dataHisto = dataHist->Clone();

//###################################################################################################Background +Signal
TF1 * fit_func = new TF1("fit_func","[0]+[1]*x+[2]*exp(-[3]*x)+[4]*exp(-0.5*((x-[5])/[6])**2)", 0, 300);
fit_func -> SetParNames("alpha","beta","gamma","delta", "N","mu","sigma");
fit_func ->SetParameters(bg_para[0], bg_para[1], bg_para[2], bg_para[3], sign_para[0], sign_para[1], sign_para[2]); //0.004 , 170, 10);
fit_func -> SetLineColor(kGreen);
fit_func -> SetLineStyle(kDashed);
//combining the fits -> SetOptFit -> Optimises parameter in terminal and histogram
dataHisto -> Fit("fit_func");
//Overrides Fit("XY") 
//+ hands over "refitted"/more precise parameter to gStyle->SetOptFit
/*for(int i=0;i<4;i++){
		func_bg->SetParameter(i,fit_func->GetParameter(i));
        }
for(int i = 4; i < 6, i++){
    sign_func -> SetParameter(i-4, fit_func ->GetParameter(i));
}
*/
func_bg->Draw("lSAME");

//###################################################################################################
cout << "-> fit_bg (Background) : Chi2 = " << func_bg -> GetChisquare() << "  ndof = 52  =>  Chi2/ndof = " << func_bg -> GetChisquare()/52 << endl;
cout << "Chi2 -> sign_func (Signal) : Chi2 = " << sign_func -> GetChisquare() <<  "  ndof = 53  =>  Chi2/ndof = " << sign_func -> GetChisquare()/53 << endl;
cout << "Chi2 -> fit_func (Bg + Sign) : Chi2 = " << fit_func -> GetChisquare() << "  ndof = 49  =>  Chi2/ndof = " << fit_func -> GetChisquare()/49 << endl;

/*
Problem list
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
fit is shown in the histogram as well as the combined parameter
!!! E2 I don't see error bars...
func_bg is not shown, but the values are printed in the terminal 
!!!Chisquare bg is = 0; ?! 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

}


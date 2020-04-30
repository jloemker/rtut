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
TCanvas * c = new TCanvas("combined", "combined", 500, 400);//1st horiz. 2cond vert.###############Visual_Setup


TH1F * Hist =(TH1F*) dataFile.Get("combined"); 


//##################################################################################################Background
TF1 * func_bg = new TF1("func_bg", "[0] + [1] * x + [2] * exp(- x * [3])" );//parametrisation + linesettings
func_bg -> SetParNames("alpha","beta","gamma","delta");//To change default names in (SetOptFit)
func_bg -> SetParameters(30, -0.06, 800, 0.01);
func_bg -> SetLineColor(kBlue);
func_bg -> SetLineStyle(kDashDotted);


Hist -> Draw("E2");
//Draw histogram 
//- !Actually E2 should carry the error bars: Draw error bars with rectangles
Hist -> Fit("func_bg");


double * bg_par = func_bg->GetParameters(); //acesses values from fir above: necessary for bg + sign parameter
//##################################################################################################Signal
TF1 * sign_func = new TF1("sign_func", "gaus") ;//should fit the resonance
sign_func -> SetParNames("N","mu","sigma") ;
/*sign_func -> SetParameters(0.004,170,1.0);
sign_func -> SetLineColor(kRed);
sign_func -> SetLineStyle(kDotted);
Gauss 3 fitparameter: const, mu, sigma & [range] can be set.
*/

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Clone_Histogram
TH1F * Histo = Hist->Clone();

//###################################################################################################Background +Signal
TF1 * fit_func = new TF1("fit_func","[0]+[1]*x+[2]*exp(-[3]*x)+[4]*exp(-0.5*((x-[5])/[6])**2)", 0, 300);//
fit_func -> SetParNames("alpha","beta","gamma","delta", "N","mu","sigma");
fit_func ->SetParameters(bg_par[0], bg_par[1], bg_par[2], bg_par[3], 0.004, 170, 10); //sign_para[0], sign_para[1], sign_para[2]
fit_func -> SetLineColor(kGreen);
fit_func -> SetLineStyle(kDashed);

Histo -> Fit("fit_func");
func_bg->Draw("lSAME");
double * fit_par=fit_func->GetParameters();//to access/{add}/update shown parameter

//###################################################################################################
cout << "-> fit_bg (Background) : Chi2 = " << func_bg -> GetChisquare() << "  ndof = 52  =>  Chi2/ndof = " << (func_bg -> GetChisquare())/52 << endl;
cout << "-> fit_func (Bg + Sign) : Chi2 = " << fit_func -> GetChisquare() << "  ndof = 49  =>  Chi2/ndof = " << (fit_func -> GetChisquare())/49 << endl;
//###################################################################################################

/*
Problem list
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Alles Tutti Frutti 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

}

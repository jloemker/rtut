void TreeMacro(){
    TH1::AddDirectory(kFALSE);//-> histogram is not gone when the file is closed 
//################################################################################---Open Tfile + TTree for both
 	TFile * bg_File = new TFile("background.root");
    TFile * sig_File = new TFile("signal.root");

	TTree * bg_Tree = (TTree*)bg_File->Get("btree");//pointer to the tree
    TTree * sig_Tree = (TTree*)sig_File->Get("stree");
//################################################################################---Histograms
    TH1F * bg_PT = new TH1F("bg_PT","p_T [GeV]",50,0,110);//create histograms -> Canvas still missing
    TH1F * sig_PT = new TH1F("sig_PT","p_T [GeV]",50,0,110);

    TH1F * bg_eta = new TH1F("bg_eta", "pseudo-rapidity", 20, -7, 7);
    TH1F * sig_eta = new TH1F("sig_eta", "pseudo-rapidity", 20, -7, 7);   

    TH1F * sig_phi = new TH1F("sig_phi", "azimuthal angle", 20, -4, 4);
    TH1F * bg_phi = new TH1F("bg_phi", "azimuthal angle", 20, -4, 4);

    TH1F * sig_E = new TH1F("sig_E", "Energy [GeV]", 50, 0, 1000);
    TH1F * bg_E = new TH1F("bg_E", "Energy [GeV]", 50, 0, 1000);
//################################################################################---Branches and Dataaccess---BG
    TBranch * branchPx = bg_Tree -> GetBranch("px");
    TBranch * branchPy = bg_Tree -> GetBranch("py");
    TBranch * branchPz = bg_Tree -> GetBranch("pz");
    TBranch * branchE = bg_Tree -> GetBranch("E");

    Double_t px,py,pz,E; //Parameter initialisation 
//dynamic structures changing with each entry -> redefine the branch address before filling the branch again. 
//This is done via the TBranch::SetAddress member function
	branchPx->SetAddress(&px);
	branchPy->SetAddress(&py);
	branchPz->SetAddress(&pz);
	branchE->SetAddress(&E);
	Int_t NEntries= bg_Tree ->GetEntries();//Extract number of entries 
    for(int l = 0; l < NEntries; l++){
        branchPx -> GetEntry(l);
        branchPy -> GetEntry(l);
        branchPz -> GetEntry(l);
        branchE -> GetEntry(l);
        TLorentzVector v_bg(px, py, pz, E);
        //##############################################################################---Filling Histogram---BG
        bg_PT -> Fill(v_bg.Pt());
	    bg_eta->Fill(v_bg.Eta());
	    bg_phi->Fill(v_bg.Phi());
        bg_E->Fill(v_bg.E());}
//#################################################################################---Branches and Dataaccess---Sig
    TBranch *branchPx = sig_Tree -> GetBranch("px");
    TBranch * branchPy = sig_Tree -> GetBranch("py");
    TBranch * branchPz = sig_Tree -> GetBranch("pz");
    TBranch * branchE = sig_Tree -> GetBranch("E");
    Double_t px,py,pz,E;
	branchPx->SetAddress(&px);
	branchPy->SetAddress(&py);
	branchPz->SetAddress(&pz);
	branchE->SetAddress(&E);
	Int_t NEntries= sig_Tree ->GetEntries();
    for(int l = 0; l < NEntries; l++){
        branchPx -> GetEntry(l);
        branchPy -> GetEntry(l);
        branchPz -> GetEntry(l);
        branchE -> GetEntry(l);
        TLorentzVector v_sig(px, py, pz, E);
        //##############################################################################---Filling Histogram---Sig
        sig_PT -> Fill(v_sig.Pt());
	    sig_eta->Fill(v_sig.Eta());
	    sig_phi->Fill(v_sig.Phi());
        sig_E->Fill(v_sig.E());
        } 
//################################################################################---Canvas [c_PT, c_]
    TCanvas * c_PT = new TCanvas("PT","PT",600,600); //may use smaller steps for bins -> change 1st parameter in Histograms
    //c_PT->SetLogy(); logarithmic view for current pad
    bg_PT->SetLineColor(kRed);
    bg_PT->SetFillColor(kRed);
    sig_PT->SetLineColor(kBlue);
    sig_PT->SetFillColor(kBlue);
    bg_PT->Draw("H");
    sig_PT->Draw("HSAME");
    //c_pT->Print("pT.eps");

    TCanvas * c_eta = new TCanvas("eta","Pseudo-Rapidity", 600, 600);
    //c_eta->SetLogy();
    bg_eta->SetLineColor(kRed);
    bg_eta->SetFillColor(kRed);
    sig_eta->SetLineColor(kBlue);
    sig_eta->SetFillColor(kBlue);
    bg_eta->Draw("H");
    sig_eta->Draw("HSAME");

    TCanvas * c_phi = new TCanvas("phi","azimuthal angle", 600, 600);
    //c_eta->SetLogy();
    bg_phi->SetLineColor(kRed);
    bg_phi->SetFillColor(kRed);
    sig_phi->SetLineColor(kBlue);
    sig_phi->SetFillColor(kBlue);
    bg_phi->Draw("H");
    sig_phi->Draw("HSAME");

    TCanvas * c_E = new TCanvas("E","Energy in [GeV]", 600, 600);
    //c_eta->SetLogy();
    bg_E->SetLineColor(kRed);
    bg_E->SetFillColor(kRed);
    sig_E->SetLineColor(kBlue);
    sig_E->SetFillColor(kBlue);
    bg_E->Draw("H");
    sig_E->Draw("HSAME");
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
1)Open both ﬁles in an interactive ROOT session and start a TBrowser. 
Check the content of these ﬁles and plot the stored variables. 
Plot the background and signal events on top of each other, 
can you ﬁnd a variable that achieves good separation between these processes?
------------------------Bad Browser connection-------------------------
2)Write a ROOT macro which opens both ﬁles and loops over all background and signal events.
For each event, create a TLorentzVector from the stored three- momentum components and the energy. 
Now ﬁll histograms containing the transverse momentum PT, the pseudo-rapidity η, the azimuthal
angle φ phi and the energy of the four-vectors and plot the background and signal processes on top of each other.
--------------------------------DONE------------------------------------
To DO:
3)By studying the histograms ____________no Glasfaser____________,
try to ﬁnd a selection which enriches the signal content. 
Calculate the relative signal content by dividing the number of signal events by the total number
of events in your selected sample. What’s the best separation you can achieve? 
+ Some parameters as well as logarithmic scale should become asjusted.

4)Now start to look at correlations between the diﬀerent observables. 
Create two-dimensional histograms where you plot meaningful combinations of PT, η, φ and E. 
Can you improve your cuts and the separation power?

*/

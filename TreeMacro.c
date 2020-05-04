void TreeMacro(){
    TH1::AddDirectory(kFALSE);//-> histogram is not gone when the file is closed 
    gROOT->SetBatch(kTRUE);
//################################################################################---Open Tfile + TTree for both
 	TFile * bg_File = new TFile("background.root");
    TFile * sig_File = new TFile("signal.root");

	TTree * bg_Tree = (TTree*)bg_File->Get("btree");//pointer to the tree
    TTree * sig_Tree = (TTree*)sig_File->Get("stree");
//################################################################################---Histograms
    TH1F * bg_PT = new TH1F("bg_PT","p_T [GeV]",50,0,100);//(name, title, #bins, from, to)
    TH1F * sig_PT = new TH1F("sig_PT","p_T [GeV]",50,0,100);

    TH1F * bg_eta = new TH1F("bg_eta", "pseudo-rapidity", 20, -4.3, 4.3);
    TH1F * sig_eta = new TH1F("sig_eta", "pseudo-rapidity", 20, -7, 7);   

    TH1F * sig_phi = new TH1F("sig_phi", "azimuthal angle", 20, -3, 3);
    TH1F * bg_phi = new TH1F("bg_phi", "azimuthal angle", 20, -3, 3);

    TH1F * sig_E = new TH1F("sig_E", "Energy [GeV]", 100, 0, 700);
    TH1F * bg_E = new TH1F("bg_E", "Energy [GeV]", 100, 0, 700);
//###############################################################################---Selection Histograms
    TH1F * bg_PT_select= new TH1F("bg_PT_sel","p_T [GeV]",50,0,110);
	TH1F * sig_PT_select = new TH1F("sig_PT_sel","p_T [GeV]",50,0,110);

	TH1F * bg_eta_select = new TH1F("bg_eta_sel","#pseudo-rapidity",20,-7,7);
	TH1F * sig_eta_select = new TH1F("sig_eta_sel","#pseudo-rapidity",20,-7,7);

	TH1F * bg_phi_select = new TH1F("bg_phi_sel","#phi",20,-3.5,3.5);
	TH1F * sig_phi_select = new TH1F("sig_phi_sel","#phi",20,-3.5,3.5);

	TH1F * bg_E_select = new TH1F("bg_E_sel","Energy [GeV]",100,0,700);
	TH1F * sig_E_select = new TH1F("sig_E_sel","Energy [GeV]",100,0,700);
//################################################################################---2D Histograms
    TH2F * bg_PTvEta = new TH2F("bg_pTvEta","bg_pTvEta",100,0, 110, 20,-7,7);
	TH2F * sig_PTvEta = new TH2F("sig_pTvEta","sig_pTvEta",100,0,110,20,-7,7);

    TH2F * bg_phivE = new TH2F("bg_phivE","bg_phivE",20,-3.5,3.5,100,0,700);
	TH2F * sig_phivE = new TH2F("sig_phivE","sig_phivE",20,-3.5,3.5,100,0,700);

    TH2F * bg_pTvE = new TH2F("bg_pTvE","bg_pTvE",100,0,110,100,0,700);
	TH2F * sig_pTvE = new TH2F("sig_pTvE","sig_pTvE",100,0,110,100,0,700);
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
        bool selection = (v_bg.Pt()>62.0 && v_bg.Pt()<85.0 && v_bg.E()>200 && v_bg.Eta()<0);
        //##############################################################################---Filling Histogram---BG
        bg_PT->Fill(v_bg.Pt());
	    bg_eta->Fill(v_bg.Eta());
	    bg_phi->Fill(v_bg.Phi());
        bg_E->Fill(v_bg.E());
        bg_PTvEta->Fill(v_bg.Pt(),v_bg.Eta());
        bg_phivE->Fill(v_bg.Phi(),v_bg.E());
        bg_pTvE->Fill(v_bg.Pt(),v_bg.E());
        //##############################################################################---selection---BG
            if(selection){
            bg_PT_select->Fill(v_bg.Pt());
	        bg_eta_select->Fill(v_bg.Eta());
	        bg_phi_select->Fill(v_bg.Phi());
            bg_E_select->Fill(v_bg.E()); 
            }
        }
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
        bool selection = (v_sig.Pt()>62.0 && v_sig.Pt()<85.0 && v_sig.E()>200 && v_sig.Eta()<0);
        //##############################################################################---Filling Histogram---Sig
        sig_PT -> Fill(v_sig.Pt());
	    sig_eta->Fill(v_sig.Eta());
	    sig_phi->Fill(v_sig.Phi());
        sig_E->Fill(v_sig.E());
        sig_PTvEta->Fill(v_sig.Pt(),v_sig.Eta());
        sig_phivE->Fill(v_sig.Phi(),v_sig.E());
        sig_pTvE->Fill(v_sig.Pt(),v_sig.E());
        //##############################################################################---selection---Sig
            if(selection){
            sig_PT_select->Fill(v_sig.Pt());
	        sig_eta_select->Fill(v_sig.Eta());
	        sig_phi_select->Fill(v_sig.Phi());
            sig_E_select->Fill(v_sig.E());
        }
        } 
//################################################################################---Canvas 

    TCanvas * c_PT = new TCanvas("PT","PT",400,400);
    c_PT->SetLogy();// logarithmic view for current pad
    bg_PT->SetLineColor(kRed);
    bg_PT->SetFillColor(kRed);
    sig_PT->SetLineColor(kBlue);
    sig_PT->SetFillColor(kBlue);
    bg_PT->Draw("H");
    sig_PT->Draw("HSAME");
    //c_pT->Print("pT.eps");

    TCanvas * c_eta = new TCanvas("eta","Pseudo-Rapidity", 400, 400);
    c_eta->SetLogy();
    bg_eta->SetLineColor(kRed);
    bg_eta->SetFillColor(kRed);
    sig_eta->SetLineColor(kBlue);
    sig_eta->SetFillColor(kBlue);
    bg_eta->Draw("H");
    sig_eta->Draw("HSAME");

    TCanvas * c_phi = new TCanvas("phi","azimuthal angle", 400, 400);
    c_phi->SetLogy();
    bg_phi->SetLineColor(kRed);
    bg_phi->SetFillColor(kRed);
    sig_phi->SetLineColor(kBlue);
    sig_phi->SetFillColor(kBlue);
    bg_phi->Draw("H");
    sig_phi->Draw("HSAME");

    TCanvas * c_E = new TCanvas("E","Energy in [GeV]", 400, 400);
    c_E->SetLogy();
    bg_E->SetLineColor(kRed);
    bg_E->SetFillColor(kRed);
    sig_E->SetLineColor(kBlue);
    sig_E->SetFillColor(kBlue);
    bg_E->Draw("H");
    sig_E->Draw("HSAME");
//################################################################################---Canvas_selection
    TCanvas * c_PT_select = new TCanvas("PT_select","PT_select", 400, 400);
    c_PT_select->SetLogy();// logarithmic view for current pad
    bg_PT_select->SetLineColor(kRed);
    bg_PT_select->SetFillColor(kRed);
    sig_PT_select->SetLineColor(kBlue);
    sig_PT_select->SetFillColor(kBlue);
    bg_PT_select->Draw("H");
    sig_PT_select->Draw("HSAME");
    //c_pT->Print("pT.eps");

    TCanvas * c_eta_select = new TCanvas("eta_select","Pseudo-Rapidity", 400, 400);
    c_eta_select->SetLogy();
    bg_eta_select->SetLineColor(kRed);
    bg_eta_select->SetFillColor(kRed);
    sig_eta_select->SetLineColor(kBlue);
    sig_eta_select->SetFillColor(kBlue);
    bg_eta_select->Draw("H");
    sig_eta_select->Draw("HSAME");

    TCanvas * c_phi_select = new TCanvas("phi_select","azimuthal angle", 400, 400);
    c_phi_select->SetLogy();
    bg_phi_select->SetLineColor(kRed);
    bg_phi_select->SetFillColor(kRed);
    sig_phi_select->SetLineColor(kBlue);
    sig_phi_select->SetFillColor(kBlue);
    bg_phi_select->Draw("H");
    sig_phi_select->Draw("HSAME");

    TCanvas * c_E_select = new TCanvas("E_select","Energy in [GeV]", 400, 400);
    c_E_select->SetLogy();
    bg_E_select->SetLineColor(kRed);
    bg_E_select->SetFillColor(kRed);
    sig_E_select->SetLineColor(kBlue);
    sig_E_select->SetFillColor(kBlue);
    bg_E_select->Draw("H");
    sig_E_select->Draw("HSAME");
    //##############################################################################---2D
    TCanvas * c_PTvEta = new TCanvas("PTvEta","PTvEta",400,400);
	c_PTvEta->SetLogy();
	bg_PTvEta->Draw("Col");
	sig_PTvEta->Draw("ColSAME");
    c_PTvEta->SaveAs("PTvEta.pdf");

    TCanvas * c_phivE = new TCanvas("phivE","phivE",400,400);
	c_phivE->SetLogy();
	bg_phivE->Draw("Col");
	sig_phivE->Draw("ColSAME");
    c_phivE->SaveAs("phivE.pdf");

    TCanvas * c_pTvE = new TCanvas("pTvE","pTvE",400,400);
	c_pTvE->SetLogy();
	bg_pTvE->Draw("Col");
	sig_pTvE->Draw("ColSAME");
    c_pTvE->SaveAs("PTvE.pdf");
    //################################################################################---Prints
    cout << "Signal before Selection : " <<sig_PT->GetEntries() << " Total(with Bg) : " << sig_PT->GetEntries()+bg_PT->GetEntries() << endl;
	cout  << "SignalEvents/Total: "<<sig_PT->GetEntries()/(sig_PT->GetEntries()+bg_PT->GetEntries()) << endl;
	cout << "Signal After Selection : " <<sig_PT_select->GetEntries() << " Total: " << sig_PT_select->GetEntries()+bg_PT_select->GetEntries() << endl;
	cout  << "S/Total: "<<sig_PT_select->GetEntries()/(sig_PT_select->GetEntries()+bg_PT_select->GetEntries()) << endl;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Alles Tutti Frutti- :) 
*/

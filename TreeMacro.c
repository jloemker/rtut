#include <stdio.h>
 // TH1-Dim histogram base class
void TreeMacro{
   TH1::AddDirectory(kFalse); //Sets a global switch disabling the reference

   TFile * combined = new TFile("combined.root");//reading file
   //pointer to the histogram 
    TH1F * histoComb;
   histoComb -> Draw("E2");//Draw it

};
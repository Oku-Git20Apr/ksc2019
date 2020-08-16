void hist_monte(){
//gROOT->Reset();

#include<fstream>

double x;

TCanvas *c1 = new TCanvas("c1", "Distri_of_Zenith_Angle_MC", 10, 20, 400, 400);
TH1S *h1 = new TH1S("h1", "Distri_of_Zenith_Angle_MC", 90, 0, 90);
//TF1 *f1 = new TF1("f1", "[0]*pow(cos(x),[1])",0,90);

//f1->SetParameter(0,500);
//f1->SetParameter(1,2);

ifstream data;
data.open("./montecarlo_data.txt");

while(data>>x) h1->Fill(x);
h1->SetXTitle("zenith_angle [deg]");
//h1->SetYTitle("counts");
h1->Draw();
h1->Fit("f1","","",0,90);
//f1->SetLineColor(2);
//f1->Draw("same");

//c1->Print("montecarlo_data0826_1kai.png");

}

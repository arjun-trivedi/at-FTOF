{
TFile* f17=TFile::Open("/data/trivedia/FTOF/ftof_official/17/17cm_123456.root");
TFile* f407=TFile::Open("/data/trivedia/FTOF/ftof_official/407/June06_407cm_123456_auto_new.root");

TH1F* h17_p3=(TH1F*)f17->Get("point_3/res_1_2_3_point3_cont");
h17_p3->SetStats();
TH1F* h407_p1=(TH1F*)f407->Get("point_1/res_1_2_3_point1_cont");
TH1F* h407_p135=(TH1F*)f407->Get("point_135/res_1_2_3_point135_cont");
h407_p1->SetStats();
h407_p135->SetStats();

TCanvas *c17=new TCanvas("17cm","17cm");
h17_p3->Draw();

TCanvas *c407=new TCanvas("407cm","407cm");
c407->Divide(1,2);
c407->cd(1);
h407_p1->Draw();
c407->cd(2);
h407_p135->Draw();
}

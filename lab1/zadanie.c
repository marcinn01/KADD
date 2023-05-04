void zadanie(){
	
	TF1 *fun1 = new TF1("f1","[0]*TMath::Cos([1]*x)", 0, 2*M_PI); 
	fun1 ->SetParameters(-1,2);
	fun1 ->SetLineColor(kBlue); 
	
	TF1 *fun2 = new TF1("f2","[0]*TMath::Sin([1]*x)/x", 0, 2*M_PI); 
	fun2 ->SetParameters(-1,2);
	fun2 ->SetLineColor(kGreen);
	
	int width = 600 ;
	int height = 800 ;
	TCanvas* canva1 = new TCanvas("canva1", "Canvas1", width, height);	
	
	canva1 -> Divide(2,2);
	canva1 -> cd(1);
	fun1->Draw();
	fun1->SetTitle("cos(x)");
	
	canva1 -> cd(2);
	fun2->SetTitle("sin(x)/x");
	fun2->Draw();
	
	canva1 -> cd(3);
	
	fun1->SetTitle("both");
	fun1->DrawCopy();
	fun2->Draw("same");
	
	TH1D* hist1 = new TH1D("hist1", "histogram", 6, 0, 6);
	hist1->SetBinContent(1, 15);
	hist1->SetBinContent(2, 3);
	hist1->SetBinContent(3, 12);
	hist1->SetBinContent(4, 25);
	hist1->SetBinContent(5, 6);
	hist1->SetBinContent(6, 19);
	
	canva1 -> cd(4);
	hist1->Draw();
}

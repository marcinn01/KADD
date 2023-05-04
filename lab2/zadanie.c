Double_t density(double_t x)
{
	Double_t a = 4.0;
	return ((1/a) * TMath::Exp(-x/a));
}

Double_t distribuant(double_t x)
{
	Double_t a = 4.0;
	return (1 - TMath::Exp(-x/a));
}

Double_t xf(double_t x)
{
	Double_t a = 4.0;
	return (x*(1/a) * TMath::Exp(-x/a));
}

void zadanie(){
	Double_t width = 800 ;
	Double_t height = 800 ;
	TCanvas* canva1 = new TCanvas("canva1", "lab2", width, height);
	
	TF1 *fun1 = new TF1("f1", "TMath::Exp(-x/4)/4", 0, 50); 
	fun1 -> SetLineColor(kBlue); 
	fun1 -> SetTitle("funkcja gestosci");
	fun1 -> GetXaxis() -> SetTitle("x");
	fun1 -> GetYaxis() -> SetTitle("f(x)");
	
	TF1 *fun2 = new TF1("numerycznie", "TMath::Exp(-x/4)/4", 0, 50); 
	fun2 -> SetLineColor(kRed);
	fun2 -> SetTitle("Dystrybuanta");
	fun2 -> GetXaxis() -> SetTitle("x");
	fun2 -> GetYaxis() -> SetTitle("f(x)");
	
	TF1 *fun3 = new TF1("analitycznie ", "1 - TMath::Exp(-x/4)", 0, 50); 
	//fun3 -> SetParameters(-1,2);
	fun3 -> SetLineColor(kGreen);
	fun3 -> SetLineStyle(5);
	
	canva1 -> Divide(2,1);
	canva1 -> cd(1);
	fun1 -> Draw();
	canva1 -> cd(2);
	fun2 -> DrawIntegral();
	fun3 -> Draw("same");
	
	auto legend = new TLegend(0.5555, 0.1, 0.9, 0.3);
	legend->AddEntry(fun2,"numerycznie","lpf");
	legend->AddEntry(fun3,"analitycznie","l");
	legend->Draw();
	  
   
	cout << "P(2<=x<=8) z gestosci: " << fun1 -> Integral(2, 8) << endl;
	cout << "P(2<=x<=8) z dystrybuanty: " << distribuant(8) - distribuant(2) << endl;
	cout << "Wartosc srednia funkcji TF1 wynosi: " << fun1 -> Mean(0, 50) << endl;
	cout << "Wartosc srednia analitycznie: 4" << endl;
	cout << "Wariancja funkcji TF1 wynosi: " << fun1 -> Variance(0, 50) << endl;
	cout << "Wariancja analitycznie: 16" << endl;
	cout << "Moda: " << fun1 ->  GetMaximumX(0, 50) << endl;
	Double_t qx[3] = {0.25, 0.5, 0.75};
	Double_t qy[3];
	fun1 -> GetQuantiles (3, qy, qx);
	
	cout << "x0.25 = " << qy[0] << endl;
	cout << "x0.50 = " << qy[1] << endl;
	cout << "x0.75 = " << qy[2] << endl;
	
}

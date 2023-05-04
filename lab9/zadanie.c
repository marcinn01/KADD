double chi2(double *xx, double *nn) 
{
	double n = nn[0];
	double x = xx[0];
	double lambda = n/2;
	double gamma = ROOT::Math::tgamma(lambda);
	double k = 1./(gamma*TMath::Power(2,lambda));
	
	if(x >= 0)
		return (double)(k*TMath::Power(x, (lambda-1)) * TMath::Exp(-x/2));
	
	return 0;
	
}

void splot(TF1 **f , int k , TH1D *h , int n) 
{
	double suma = 0;
	for(int j = 0; j < n; j++)
	{
		for(int i = 0; i < k; i++)
		{
			suma += f[i] -> GetRandom();
			
		}
		h -> Fill(suma);
		suma = 0;
	}
}

void zadanie()
{
	Double_t width = 800;
	Double_t height = 700;
	TCanvas* canva1 = new TCanvas("canva1", "lab8", width, height);
	canva1 -> Divide(2, 1);
	
	TF1 *fun1 = new TF1("fun1", chi2, 0, 30, 1);
	fun1 -> SetParameter(0,1);
	fun1 -> SetTitle("rozklad #chi^{2}");
	fun1 -> GetXaxis() -> SetTitle("#chi^{2}");
	fun1 -> GetYaxis() -> SetTitle("f(#chi^{2})");
	fun1 -> SetLineColor(1);
	
	canva1 -> cd(1);
	fun1 -> Draw();
	
	auto *legend = new TLegend(0.7, 0.3, 0.9, 0.9);
	legend -> AddEntry(fun1, "n = 1", "LP");
	
	for(int i = 2; i < 21; i++)
	{
		TF1 *fun2 = new TF1("fun2", chi2, 0, 30, 1);
		fun2 -> SetParameter(0,i);
		canva1 -> cd(1);
		fun2 -> Draw("same");
		fun2 -> SetLineColor(i);
		legend -> AddEntry(fun2, "n = " , "L");
	}
	
	legend -> Draw();
	
	//////////////////DYSTRYBUANTA//////////////////
	
	TF1 *fun3 = new TF1("fun3", chi2, 0, 30, 1);
	fun3 -> SetParameter(0,1);
	
	canva1 -> cd(2);
	
	TGraph * ggraph = (TGraph*)(fun3 -> DrawIntegral());
	ggraph -> SetTitle("dystrybuanta #chi^{2}");
	ggraph -> GetXaxis() -> SetTitle("#chi^{2}");
	ggraph -> GetYaxis() -> SetTitle("f(#chi^{2})");
	ggraph -> SetLineColor(1);
	
	ggraph -> Draw();
	
	auto *legend2 = new TLegend(0.7, 0.15, 0.9, 0.7);
	legend2 -> AddEntry(fun1, "n = 1", "LP");
	
	for(int i = 2; i < 21; i++)
	{
		TF1 *fun4 = new TF1("fun4", chi2, 0, 30, 1);
		fun4 -> SetParameter(0,i);
		canva1 -> cd(2);
		fun4 -> SetLineColor(i);
		fun4 -> DrawIntegral("same");
		legend2 -> AddEntry(fun4, "n = " , "L");
	}
	
	legend2 -> Draw();	
	
}

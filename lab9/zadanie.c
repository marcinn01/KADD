void splot(int k, TH1D *h, int n)
{
	double suma = 0.0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			suma += gRandom -> Uniform();
		}
		h -> Fill(suma);
		suma = 0.0;
	}
}

double chi2(double *xx, double *params)
{
	double x = xx[0];
	double n = params[0];
	
	double lambda = n/2;
	double k = 1./(TMath::Gamma(lambda) * TMath::Power(2, lambda));
	
	if(x>=0)
		return (k * TMath::Power(x, (lambda-1)) * TMath::Exp(-x/2));
	else 
		return 0;
}

void zadanie()
{
	/*CZESC I */
	
	TCanvas *canva1 = new TCanvas("canva1", "lab9", 800, 600);
	canva1 -> Divide(2, 1);
	
	canva1 -> cd(1);
	
	TLegend *leg = new TLegend(0.7, 0.2, 0.9, 0.9); //legend
	
	TF1 *fun1 = new TF1("fun1", chi2, 0, 30, 1);
	fun1 -> SetParameter(0, 1);
	fun1 -> SetLineColor(1);
	fun1 -> SetTitle("rozklad #chi^{2}");
	fun1 -> GetXaxis() -> SetTitle("#chi^{2}");
	fun1 -> GetYaxis() -> SetTitle("f(#chi^{2})");
	fun1 -> Draw();
	
	leg -> AddEntry(fun1,"n = 1","l");
	
	for(int i = 2; i <=20; i++)
	{
		TF1 *fun2 = new TF1("fun2", chi2, 0, 30, 1);
		fun2 -> SetParameter(0, i);
		fun2 -> SetLineColor(i);
		fun2 -> Draw("same");
		
		string x = "n = "+to_string(i); //
        const char *tab = x.c_str();
        leg -> AddEntry(fun2,tab,"l");	
	}
	
	leg -> Draw();
	
	
	canva1 -> cd(2);
	
	TLegend *leg2 = new TLegend(0.7, 0.2, 0.9, 0.9); //legend
	
	TGraph *graph = (TGraph*)(fun1 -> DrawIntegral());
	graph -> SetTitle("dystrybuanta #chi^{2}");
	graph -> GetXaxis() -> SetTitle("#chi^{2}");
	graph -> GetYaxis() -> SetTitle("F(#chi^{2})");
	graph -> Draw();
	
	leg2 -> AddEntry(graph,"n = 1","l");
	
	for(int i = 2; i <=20; i++)
	{
		TF1 *fun2 = new TF1("fun2", chi2, 0, 30, 1);
		fun2 -> SetParameter(0, i);
		fun2 -> SetLineColor(i);
		fun2 -> DrawIntegral("same");
		
		string x = "n = "+to_string(i); //
        const char *tab = x.c_str();
        leg2 -> AddEntry(fun2,tab,"l");	
	}
	leg2 -> Draw();
	
	
	/*CZESC II */
	
	TCanvas *canva2 = new TCanvas("canva2", "lab9", 800, 600);
	
	TF1 *gauss = new TF1();
	TH1D *hist;
	
	double chisq = 0.0;
	int n = 0; 
	int ndf = 0;
	
	do{
		hist = new TH1D("hist", "Splot", 100, 0, 9);
		splot(n, hist, 10000);
		hist -> Fit("gaus");
		gauss = hist -> GetFunction("gaus");
		chisq = gauss -> GetChisquare();
		ndf = gauss -> GetNDF();
		n++;
	}
	while(chisq/ndf >= 1.0);
	
	cout << "\nWykonano splot " << n << " rozkladow" << endl;
	cout << "chi2/NDF = " << chisq/ndf << endl;
	
	//hist->SetStats(false);
	
}
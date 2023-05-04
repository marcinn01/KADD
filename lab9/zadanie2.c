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

void splot(int k , TH1D *h , int n) 
{
	double suma = 0, u;
	for(int j = 0; j < n; j++)
	{
		for(int i = 0; i < k; i++)
		{
			u = gRandom -> Uniform(0,1);
			suma += u;
		}
		h -> Fill(suma);
		suma = 0.0;
	}
}

void zadanie2()
{
	Double_t width = 800;
	Double_t height = 700;
	TCanvas* canva1 = new TCanvas("canva1", "lab8", width, height);
	canva1 -> Divide(1, 1);
	
	
	TF1 *gauss = new TF1();
	TH1D *hist;
	int n = 0;
	double chisq;
	int ndf;
	
	
	do 
	{
		hist = new TH1D("hist", "histogram", 100, 0, 9);
		splot(n, hist, 10000);
		hist -> Fit("gaus");
		gauss = hist -> GetFunction("gaus");
		chisq = gauss -> GetChisquare();
		ndf = gauss -> GetNDF();
		n++;
	}
	while(chisq/ndf >= 1);
	
	cout << n << endl;
	cout << chisq/ndf << endl;
	
	
}

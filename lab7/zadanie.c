TRandom *r = new TRandom();

double PI()
{
	Double_t N = 500000;
	Double_t NA = 0;
	Double_t NR = 0;
	TGraph *graph1 = new TGraph();
	TGraph *graph2 = new TGraph();
	
	TH1D *th1 = new TH1D("th1", "Accpeted x", 100, 0, 1);
	
	for(int i = 0; i <= N; i++)
	{
		Double_t x = r -> Uniform(1);
		Double_t y = r -> Uniform(1);
		if(x*x + y*y <= 1)
		{
			graph1 -> SetPoint(NA, x, y);
			th1 -> Fill(x);
			NA++;
		}
		else 
		{
			graph2 -> SetPoint(NR, x, y);
			NR++;
		}
	}
	Double_t width = 800;
	Double_t height = 600;
	TCanvas* canva1 = new TCanvas("canva1", "lab7", width, height);
	canva1 -> Divide(2,1);
	
	canva1 -> cd(1);
	graph1 -> Draw("AP");
	graph1 -> SetMarkerColor(kRed);
	graph1 -> SetTitle("PI");
	graph1 -> GetXaxis() -> SetTitle("x");
	graph1 -> GetYaxis() -> SetTitle("y");
	graph2 -> Draw("sameP");
	graph2 -> SetMarkerColor(kGreen);
	
	canva1 -> cd(2);
	th1 -> Draw("L");
	th1 -> GetXaxis() -> SetTitle("x");
	th1 -> GetYaxis() -> SetTitle("# of x");
	
	return 4.*NA/N;
}

double losujVonNeumann (TF1* g , double min , double max)
{
	double u, y;
	do 
	{
		double y = r -> Uniform(0, g -> GetMaximum(min, max));
		double u = r -> Uniform(min, max);
	}while(g -> Eval(u) <= y);
	return u;
}

double wydajnoscVonNeumanna (TF1 *g, double min, double max, int n) {
	int w = 0;
	double u, y;
	for (int i = 0; i < n; i++) {
		u = r -> Uniform(0, g -> GetMaximum(min, max));
		y = r -> Uniform(min, max);
		if ((g -> Eval(y)) > u ) 
			w++;
	}
	return (double) w / n;
}

double calkaVonNeumann (TF1 *g, double min, double max, int n) {
	double d = g -> GetMaximum(min, max);
	return wydajnoscVonNeumanna(g, min, max, n) * (max - min) * d ;
}

double calkaFL(double x, double a, double b)
{
	return a * x*x/2 +b*x;
}

double odwrDys(double x, double a, double b)
{
	return (-(b/a) + TMath::Sqrt(2*x/a+ (b*b)/(a*a) ) );
}

double calkaVonNeumannZPomoc(TF1 *g, TF1 *s, double min, double max, int n, double &wydajnosc) {
	int wyd = 0;
	double a = s -> GetParameter(0);
	double b = s -> GetParameter(1);
	double u, y, x;
	
	//TH1D *th = new TH1D("th", "distribution", );
	
	for (int i = 0; i < n; i++) {
		u = r -> Uniform(0, 1);
		x = r -> Uniform(calkaFL(min, a, b), calkaFL(max, a, b));
		y = odwrDys(x, a, b);
		if ((g -> Eval(y) / s -> Eval(y)) > u ) 
			wyd++;
	}
	wydajnosc = (double) wyd / n;
	return wydajnosc * (max - min) * (s -> Eval(min) + s -> Eval(max)) / 2;
	
	//TCanvas* canva3 = new TCanvas("canva3", "lab7", 800, 600);
	//th -> Draw("L");
}

void zadanie()
{
	Double_t min = 0., max =1.;
	TF1 *g = new TF1("g", "0.4 + (TMath::Sin(TMath::Pi()*(x+1.2)))/(TMath::Pi()*(x+1.2)+1)", 0, 1);
	TF1 *s = new TF1 ("s", "[0] * x + [1]", min, max);
	double c = g -> Eval(min);
	double d = g -> Eval(max);
	s -> SetParameters(0, d - c);
	s -> SetParameters(1, c);
	
	int n = 10000;
	double wydajnosc;
	
	cout << "PI = " << PI() << endl;
	cout << "Calka metoda Integral: " << g -> Integral(0, 1) << endl;
	cout << "# von Neumann #" << endl;
	cout << "Calka: " << calkaVonNeumann(g, 0, 1, n) << endl;
	cout << "Wydajnosc: " << wydajnoscVonNeumanna(g, 0, 1, n) << endl;
	cout << "Calka pomocnicza: " << calkaVonNeumannZPomoc(g, s, 0, 1, n, wydajnosc) << endl;
	cout << "Wydajnosc: " << wydajnoscVonNeumanna(g, 0, 1, n) << endl;
	
	TCanvas* canva2 = new TCanvas("canva2", "lab7", 800, 600);
	g -> Draw("L");
	g -> SetTitle("Rozklad g(y) von Neumann");
	
}
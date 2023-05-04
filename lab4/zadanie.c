Double_t density(Double_t *x, Double_t *params)
{
	Double_t X = x[0];
	Double_t Y = x[1];
	Double_t c = params[0];
	if(X >= 0 && X <= TMath::Pi()/2 && Y >= 0 && Y <= TMath::Pi()/2)
		return (c * TMath::Sin(X*Y));
	else 
		return 0;
}

void zadanie()
{
	Double_t width = 800;
	Double_t height = 800;
	TCanvas* canva1 = new TCanvas("canva1", "lab4", width, height);
	canva1 -> Divide(2, 2);
	
	Double_t xmin = 0, xmax = TMath::Pi()/2, ymin = 0, ymax = TMath::Pi()/2;
	
	TF2* fun1 = new TF2("fun1", density, xmin, xmax, ymin, ymax, 1);
	fun1 -> SetParameter(0, 1.0);
	
	Double_t cc = fun1 -> Integral(xmin, xmax, ymin, ymax);
	cout << "Stala normujaca: c = " << 1./cc << endl;
	fun1 -> SetParameter(0, 1./cc);

	TH2D* graph = new TH2D("graph", "gestosc prawdopodobienstwa", 30, xmin, xmax, 30, ymin, ymax);
	Double_t count = 0;
	Double_t px, py;
	for(Int_t i = 0; i <= 50000; i++)
	{
		fun1 -> GetRandom2(px, py);
		graph -> Fill(px, py);
	}
	
	canva1 -> cd(1);
	graph -> GetXaxis() -> SetTitle("x");
	graph -> GetYaxis() -> SetTitle("y");
	graph -> GetZaxis() -> SetTitle("f(x,y)");
	graph -> Draw("LEGO2");
	
	graph -> Scale(1./graph->Integral(0, 30, 0, 30, "width"));
	TH2D* fun3 = new TH2D("graph", "dystrybuanta", 30, xmin, xmax, 30, ymin, ymax);
	for(Int_t i=0; i<=30; i++)
	{
		for(Int_t j=0; j<=30; j++)
		{
			fun3 -> SetBinContent(i, j, graph -> Integral(0, i, 0, j, "width"));
		}
	}
	
	canva1 -> cd(2);
	fun3 -> GetXaxis() -> SetTitle("x");
	fun3 -> GetYaxis() -> SetTitle("y");
	fun3 -> GetZaxis() -> SetTitle("F(x,y)");
	fun3 -> Draw("LEGO2");
	
	TH1D* g = graph -> ProjectionX();
	canva1 -> cd(3);
	g -> GetXaxis() -> SetTitle("x");
	g -> GetYaxis() -> SetTitle("g(x)");
	g -> Draw();
	g -> SetTitle("gest brzeg x");
	
	TH1D* h = graph -> ProjectionY();
	canva1 -> cd(4);
	h -> GetXaxis() -> SetTitle("y");
	h -> GetYaxis() -> SetTitle("h(y)");
	h -> Draw("L");
	h -> SetTitle("gest brzeg y");
	h -> SetLineStyle(5);
	//h -> SetLineColor("kGreen");
	
	Double_t ex = graph -> GetMean(1);
	Double_t ey = graph -> GetMean(2);
	//cout << "Wartosc oczekiwana: " << endl;
	cout << "E(X) = " << ex << endl;
	cout << "E(Y) = " << ey << endl;  
	
	Double_t sx = graph -> GetStdDev(1);
	Double_t sy = graph -> GetStdDev(2);
	//cout << "Odchylenie standardowe: " << endl;
	cout << "sigma(X) = " << sx << endl;
	cout << "sigma(Y) = " << sy << endl;  
	
	Double_t cov = graph -> GetCovariance(1, 2);
	//cout << "Odchylenie standardowe: " << endl;
	cout << "cov(X,Y) = " << cov << endl;  
	
	Double_t rho = graph -> GetCorrelationFactor(1, 2);
	//cout << "Odchylenie standardowe: " << endl;
	cout << "rho(X,Y) = " << rho << endl;  
}
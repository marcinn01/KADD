Double_t fcn(double *x, double *params)
{
	if(x[0] >= 0 && x[0] <= 1 && x[1] >= 0 && x[1] <= 1)
	{
		return (params[0] * TMath::Power(x[0], params[1]) * TMath::Power(x[1], params[2]));
	}
	else
	{
		return 0;
	}
}

void zadanie()
{
	Double_t width = 1000;
	Double_t height = 1000;
	TCanvas* canva1 = new TCanvas("canva1", "lab3", width, height);
	
	
	TF2* fun1 = new TF2("fun1", fcn, 0, 1, 0, 1, 3);
	fun1 -> SetParameters(1, 1, 3);
	
	Double_t c = fun1 -> Integral(0, 1, 0, 1);
	cout << "Stala normujaca: c = " << 1/c << endl;
	fun1 -> SetParameter(0, 1/c);
	
	canva1 -> Divide(2, 2);
	canva1 -> cd(1);
	fun1 -> Draw("surf1");
	fun1 -> SetTitle("f(x,y)");
	fun1 -> GetXaxis() -> SetTitle("x");
	fun1 -> GetYaxis() -> SetTitle("y");
	fun1 -> GetZaxis() -> SetTitle("f(x,y)");
	
	
	TGraph2D* graph = new TGraph2D();
	Int_t count = 0;
	for(Double_t x = 0; x <=1; x+= 1./10)
	{
		for(Double_t y = 0; y <=1; y+= 1./10)
		{
			graph -> SetPoint(count, x, y, fun1 -> Integral(0,x, 0,y));
			count++;
		}
	}
	
	canva1 -> cd(2);
	graph -> SetTitle("Dystrybuanta");
	graph -> GetXaxis() -> SetTitle("x");
	graph -> GetYaxis() -> SetTitle("y");
	graph -> GetZaxis() -> SetTitle("F(x,y)");
	graph -> Draw("surf1");
	
	
	TGraph* g = new TGraph();
	Int_t count1 = 0;
	for(Double_t x = 0; x <=1; x+= 1./100)
	{
		g -> SetPoint(count1, x, fun1->Integral(x -1./10, x, 0, 1));
		count1++;
	}
	
	canva1 -> cd(3);
	g -> SetTitle("Gestosc brzegowa x");
	g -> GetXaxis() -> SetTitle("x");
	g -> GetYaxis() -> SetTitle("g(x)");
	g -> Draw("APL");
	
	TGraph* h = new TGraph();
	Int_t count2 = 0;
	for(Double_t y = 0; y <=1; y+= 1./100)
	{
		h -> SetPoint(count2, y, fun1->Integral(0, 1, y -1./10, y));
		count2++;
	}
	
	canva1 -> cd(4);
	h -> SetTitle("Gestosc brzegowa y");
	h -> GetXaxis() -> SetTitle("y");
	h -> GetYaxis() -> SetTitle("h(y)");
	h -> Draw("APL");
} 

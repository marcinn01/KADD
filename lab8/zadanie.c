void splot(TF1 **f, int k, TH1D *h, int n)
{
	double suma = 0.0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			suma += f[j] -> GetRandom();
		}
		h -> Fill(suma);
		suma = 0.0;
	}
}

void deskaGaltona(TH1D *h, int n, int l, double p)
{
	TRandom *r = new TRandom();
	int z = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < l; j++)
		{
			if(r->Uniform(0,1) < p)
				z--;
			else z++;
		}
		h -> Fill(z);
		z = 0;
	}
}

void zadanie()
{
	TCanvas *canva1 = new TCanvas("canva1", "lab8", 800, 600);
	canva1 -> Divide(2, 2);
	
	TF1 *fun1 = new TF1("fun1", "1", 2, 5);
	TF1 *fun2 = new TF1("fun2", "gaus(0)", 0, 50);
	TF1 *fun3 = new TF1("fun3", "gaus(0)", 0, 50);
	
	fun2 -> SetParameters(1, 10, 3);
	fun3 -> SetParameters(1, 15, 4);
	
	TF1 *splot1[2];
	TF1 *splot2[3];
	TF1 *splot3[2];
	
	splot1[0] = fun1;
	splot1[1] = fun1;
	
	splot2[0] = fun1;
	splot2[1] = fun1;
	splot2[2] = fun1;
	
	splot3[0] = fun2;
	splot3[1] = fun3;
	
	TH1D *h1 = new TH1D("h1", "Splot 2U", 100, 4, 10);
	h1 -> GetXaxis() -> SetTitle("x");
	h1 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot1, 2, h1, 100000);
	canva1 -> cd(1);
	h1 -> Draw();
	
	TH1D *h2 = new TH1D("h2", "Splot 3U", 100, 6, 15);
	h2 -> GetXaxis() -> SetTitle("x");
	h2 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot2, 3, h2, 100000);
	canva1 -> cd(2);
	h2 -> Draw();
	
	TH1D *h3 = new TH1D("h3", "Splot 2N", 100, 0, 50);
	h3 -> GetXaxis() -> SetTitle("x");
	h3 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot3, 2, h3, 100000);
	canva1 -> cd(3);
	h3 -> Draw();
	
	/*
	EX1, EX2, VX1 i VX2
	to parametry rozkładu normalnego 
	*/
	
	cout << "EX 1: 10" << endl;
	cout << "EX 2: 15" << endl;
	cout << "EX: " << h3 -> GetMean() << endl;
	
	cout << "VX 1: 3" << endl;
	cout << "VX 2: 4" << endl;
	cout << "VX: " << h3 -> GetStdDev() << endl;
	
	
	///////////////////////////////////////////////////////
	TH1D *hist = new TH1D("hist", "Tablica", 21, -11, 11);
	hist -> GetXaxis() -> SetTitle("pozycja");
	hist -> GetYaxis() -> SetTitle("l. zliczen");
	deskaGaltona(hist, 1500, 20, 0.5);
	canva1 -> cd(4);
	hist -> Draw();
	
}
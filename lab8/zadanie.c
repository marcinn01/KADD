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

void deskaGaltona(TH1D *h , int n , int l , double p)
{
	//srand(time(NULL));
	TRandom *r = new TRandom();
	// n-liczba prób (kuli);
	// l-liczba rzędów;
	// p-prawdopodobieństwo ruchu kuli w prawo (sukcesu).
	for(int i = 0; i < n; i++)
	{
		double z = 0;
		for(int j = 0; j < l; j++)
		{
			if(r -> Uniform(0,1) < p)
			{
				z--;
			}
			else
			{
				z++;
			}
		}
		h -> Fill(z);
	}
}

void zadanie()
{
	Double_t width = 800;
	Double_t height = 600;
	TCanvas* canva1 = new TCanvas("canva1", "lab8", width, height);
	canva1 -> Divide(2, 2);
	
	TF1 *f1 = new TF1("f1", "1", 2, 5);
	TF1 *f2 = new TF1("f2", "gaus(0)", 0, 50);
	TF1 *f3 = new TF1("f3", "gaus(0)", 0, 50);
	
	f2 -> SetParameters(1,10,3);
	f3 -> SetParameters(1,15,4);
	
	TF1 *splot1[2];
	splot1[0] = f1;
	splot1[1] = f1;
	
	TF1 *splot2[3];
	splot2[0] = f1;
	splot2[1] = f1;
	splot2[2] = f1;
	
	TF1 *splot3[2];
	splot3[0] = f2;
	splot3[1] = f3;
	
	TH1D *th1 = new TH1D("th1", "Splot 2U", 100, 4, 10);
	th1 -> GetXaxis() -> SetTitle("x");
	th1 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot1, 2, th1, 1000000);
	canva1 -> cd(1);
	th1 -> Draw();
	
	TH1D *th2 = new TH1D("th2", "Splot 3U", 100, 6, 15);
	th2 -> GetXaxis() -> SetTitle("x");
	th2 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot2, 3, th2, 1000000);
	canva1 -> cd(2);
	th2 -> Draw();
	
	TH1D *th3 = new TH1D("th3", "Splot 2N", 100, 0, 50);
	th3 -> GetXaxis() -> SetTitle("x");
	th3 -> GetYaxis() -> SetTitle("l. zliczen");
	splot(splot3, 2, th3, 1000000);
	canva1 -> cd(3);
	th3 -> Draw();
	
	/*cout << "Splot 2U" << endl;
	cout << "Srednia 1: " << th1 -> GetMean() << endl;
	cout << "Odchylenie standardowe 1: " << th1 -> GetStdDev() << endl;
	
	cout << "Splot 3U" << endl;
	cout << "Srednia 2: " << th2 -> GetMean() << endl;
	cout << "Odchylenie standardowe 2: " << th2 -> GetStdDev() << endl;
	*/
	cout << "Splot 2N" << endl;
	
	cout << "Srednia 3: " << f2 -> Mean(0, 50) << endl;
	cout << "Odchylenie standardowe: 4" << endl;
	
	cout << "Srednia 3: " << f3 -> Mean(0, 50) << endl;
	cout << "Odchylenie standardowe: 6" << endl;
	
	cout << "Srednia 3: " << th3 -> GetMean() << endl;
	cout << "Odchylenie standardowe 3: " << th3 -> GetStdDev() << endl;
	
	
	TH1D *th4 = new TH1D("th4", "tablica", 22, -11, 11);
	th4 -> GetXaxis() -> SetTitle("pozycja");
	th4 -> GetYaxis() -> SetTitle("l. zliczen");
	deskaGaltona(th4, 10000, 20, 0.5);
	canva1 -> cd(4);
	th4 -> Draw();
	
}

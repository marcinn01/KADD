/*long seed = time(NULL);
double uniform(double min, double max)
{
	//int m = 97;
	//int g = 23;
	
	//int m = 12799;
	//int g = 223;
	
	int m = 147483647;
	int g = 16807;
	
	int c = 0;
	
	double value = (g*seed+c)%m;
	seed = value;
	return value*(max-min)/(m-1);
}*/

double myfun(double *X, double *params)
{
	double x = X[0];
	double tau = params[0];
	if(x >= 0)
		return (1/tau*TMath::Exp(-x/tau));
	else
			return 0;
}

void zadanie()
{
	TCanvas* canva1 = new TCanvas("canva1", "lab5", 800, 600);
	canva1 -> Divide(2,3);
	
	int N = 10000;
	
	/*ofstream file;
	file.open("dane3.txt");
	double val;
	double x[N];
	for(int i = 0; i <= N; i++)
	{
		x[i] = uniform(0, 1);
		file << x[i] << endl;
	}
	file.close();*/
	
	TH1D* th11 = new TH1D("th11", "Rozklad jednorodny", 100, 0, 1);
	TH2D* th12 = new TH2D("th12", "korelacja", 100, 0, 1, 100, 0, 1);
	
	TH1D* th21 = new TH1D("th21", "Rozklad jednorodny", 100, 0, 1);
	TH2D* th22 = new TH2D("th22", "korelacja", 100, 0, 1, 100, 0, 1);
	
	TH1D* th31 = new TH1D("th31", "Rozklad jednorodny", 100, 0, 1);
	TH2D* th32 = new TH2D("th32", "korelacja", 100, 0, 1, 100, 0, 1);
	
	ifstream file1;
	file1.open("dane1.txt");
	double x1[N];
	double value1;
	for(int i = 0; i <= N; i++)
	{
		file1 >> value1;
		x1[i] = value1;
		//cout << x1[i] << endl;
		th11 -> Fill(x1[i]);
		th12 -> Fill(x1[i], x1[i+1]);
		
	}
	file1.close();
	
	ifstream file2;
	file2.open("dane2.txt");
	double x2[N];
	for(int i = 0; i <= N; i++)
	{
		file2 >> x2[i];
		th21 -> Fill(x2[i]);
		th22 -> Fill(x2[i], x2[i+1]);
	}
	file2.close();
	
	ifstream file3;
	file3.open("dane3.txt");
	double x3[N];
	for(int i = 0; i <= N; i++)
	{
		file3 >> x3[i];
		th31 -> Fill(x3[i]);
		th32 -> Fill(x3[i], x3[i+1]);
	}
	file3.close();
	
	
	canva1 -> cd(1);
	th11 -> Draw("COLZ");
	
	canva1 -> cd(2);
	th12 -> Draw("COLZ");
	
	canva1 -> cd(3);
	th21 -> Draw("COLZ");
	
	canva1 -> cd(4);
	th22 -> Draw("COLZ");
	
	canva1 -> cd(5);
	th31 -> Draw("COLZ");
	
	canva1 -> cd(6);
	th32 -> Draw("COLZ");
	
	TF1* fun1 = new TF1("fun1", myfun, 0, 8, 1);
	fun1 -> SetParameter(0, 3);
	double c = fun1 -> Integral(0, 8);
	
	TH1D* th4 = new TH1D("th4", "dist", 100, 0, 10);
	ifstream file4;
	file4.open("dane3.txt");
	double x4[N];
	for(int i = 0; i <= N; i++)
	{
		file4 >> x4[i];
		th4 -> Fill(-3*TMath::Log(1-x4[i]));
	}
	file4.close();
	double d = th4 -> Integral(0, 100, "width");
	th4 -> Scale(c/d);
	
	cout << c << endl << d << endl;
	TCanvas* canva2 = new TCanvas("canva2", "lab6", 800, 600);
	fun1 -> Draw();
	th4 -> Draw("same");
	fun1 -> GetXaxis() -> SetTitle("y");
	fun1 -> GetYaxis() -> SetTitle("g(y)");
	fun1 -> SetTitle("Rozklad metoda odwrotnej dystrybuanty");
}

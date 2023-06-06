double chi2(TH1D *h, TF1 *f)
{
	double T = 0, nk = 0, npk = 0;
	for(int i = 0; i < 9; i++)
	{
		nk = h -> GetBinContent(i+1);
		npk = f -> Eval(i);
		T += (TMath::Power((nk - npk), 2))/npk;
	}
	return T;
}

bool testChi2(double T, double alpha, int ndf)
{
	TF1 *fun = new TF1("fun1", "[0] * TMath::Power(x, [1]-1) * TMath::Exp(-x/2)", 0, 20);
	double lambda = ndf/2;
	double k = 1./(TMath::Gamma(lambda) * TMath::Power(2, lambda));
	fun -> SetParameter(0, k);
	fun -> SetParameter(1, lambda);
	
	double check = fun -> Integral(0, T);
	
	if(1-alpha < check)
		return true;
	else return false;
}

void zadanie()
{
	/*CZESC I */
	
	TCanvas *canva1 = new TCanvas("canva1", "lab9", 800, 600);
	
	TLegend *leg = new TLegend(0.75, 0.65, 0.9, 0.9); //legend
	
	TH1D *hist = new TH1D("hist", "Wyniki", 9, 0, 9);
	hist -> GetXaxis() -> SetTitle("k");
	hist -> GetYaxis() -> SetTitle("n_{k}, np_{k}");
	
	double bin, val;
	double licznik = 0.0, mianownik = 0.0;
	
	ifstream file;
	file.open("dane10.txt");
	while(file >> bin >> val)
	{
		hist -> SetBinContent(bin+1, val);
		licznik += bin*val;
		mianownik += val;
	}
	file.close();
	
	leg -> AddEntry(hist, "wyniki", "f");
	hist -> SetFillColor(kRed-8);
	hist -> Draw();
	hist -> SetStats(false);
	
	double lambda = licznik/mianownik;
	cout << "Wspolczynnik najwiekszej wiarygodnosci: " << lambda << endl;
	
	TF1 *fun1 = new TF1("fun1", "[0] * TMath::PoissonI(x, [1])", 0, 10);
	fun1 -> SetParameter(0, hist->Integral());
	fun1 -> SetParameter(1, lambda);
	fun1 -> SetLineColor(kRed);
	fun1 -> Draw("same");
	leg -> AddEntry(fun1, "fit ENW", "l");
	
	TF1 *fun2 = new TF1("fun2", "[0] * TMath::PoissonI(x, [1])", 0, 10);
	fun2 -> SetParameter(0, hist->Integral());
	fun2 -> SetParameter(1, 1);
	fun2 -> SetLineColor(kBlue);
	hist -> Fit(fun2, "LR", 0, 9);
	fun2 = hist -> GetFunction("fun2");
	leg -> AddEntry(fun2, "fit ROOT", "l");
	
	leg -> Draw();
	
	/////////////////////////////////////////////////////////////////
	double T1 = chi2(hist, fun1);
	double T2 = chi2(hist, fun2);
	int ndf = 9-2-1;		//liczba binów - l. parametrów - 1
	
	double lambdaROOT = fun2 -> GetParameter(1);
	
	cout << "Lambda najwiekszej wiarygodnosci: " << lambda << endl;
	cout << "Lambda (ROOT Fit): " << lambdaROOT << endl;
	cout << "chi2 (wartosc statystyki testowej T): " << T2 << endl;
	cout << "chi2/NDF): " << T1/ndf << endl;
	
	cout << "---------------------------------------" << endl;
	double chi2ROOT = fun2 -> GetChisquare();
	cout << "chi2 (ROOT Fit): " << chi2ROOT << endl;
	cout << "chi2 (ROOT Fit)/NDF): " << chi2ROOT/ndf << endl;
	
	double alpha = 0.01;
	cout << "\nPoziom istotnosci alpha: " << alpha << endl;
	
	
	bool tescik = testChi2(T2, alpha, ndf);
	
	if(tescik == 1)
		cout << "Odrzucono" << endl;
	else 
		cout << "Nie ma podstaw do odrzucenia" << endl;
	
	
}
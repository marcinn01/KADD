/*double chi2(TH1D *h, TF1 *f)
{
	double T = 0, nk = 0, npk = 0;
	for(int i = 0; i < 9; i++)
	{
		nk = h -> GetBinContent(i+1);
		npk = f -> Eval(i);
		T += (TMath::Power((nk - npk), 2))/npk;
	}
	return T;
}*/

bool testChi2(double T, double alpha, int ndf)
{
	TF1 *fun = new TF1("fun1", "[0] * TMath::Power(x, [1]-1) * TMath::Exp(-x/2)", 0, 20);
	double lambda = ndf/2;
	double k = 1./(TMath::Gamma(lambda) * TMath::Power(2, lambda));
	fun -> SetParameter(0, k);
	fun -> SetParameter(1, lambda);
	
	double check = TMath::ChisquareQuantile(1-alpha, ndf);
	
	if(T < check)
		return false;
	else return true;
}

double dopasuj(int st, int n, double *tj, double *yj, double *sigmaj, double *wsp, double *bwsp)
{
	double val1, val2;
	int index = 0;
	ifstream file;
	file.open("dane.dat");
	while(file >> val1 >> val2)
	{
		tj[index] = val1;
		yj[index] = val2;
		sigmaj[index] = TMath::Sqrt(val2);
		index++;
	}
	
	
	TMatrixD *c = new TMatrixD(n, 1);
	TMatrixD *H = new TMatrixD(n, n);
	TMatrixD *A = new TMatrixD(n, st+1);
	
	for(int i = 0; i < n; i++)
	{
		(*c)(i, 0) = yj[i];
		(*H)(i, i) = 1./(sigmaj[i]);
		(*A)(i, 0) = 1.0;
		
		for(int j = 1; j < st+1; j++)
		{
			(*A)(i, j) = TMath::Power(tj[i], j);			
		}	
	}
	
	
	
	
	// c'
	TMatrixD *cPrim = new TMatrixD(*H, TMatrixD::kMult, *c);
	
	//A'
	TMatrixD *APrim = new TMatrixD(*H, TMatrixD::kMult, *A);
	//A'^T
	TMatrixD *APrimT = new TMatrixD(TMatrixD::kTransposed, *APrim);
	// ( A'^T * A' )
	TMatrixD *APrimT_APrim = new TMatrixD(*APrimT, TMatrixD::kMult, *APrim);
	// ( A'^T * A' )^-1
	TMatrixD *Inverted = new TMatrixD(*APrimT, TMatrixD::kMult, *APrim);
	Inverted -> Invert();
	// ( A'^T * A' )^-1  *  A'^T
	TMatrixD *Inv_APrimT = new TMatrixD(*Inverted, TMatrixD::kMult, *APrimT);
	// ( ( A'^T * A' )^-1  *  A'^T ) * c'
	TMatrixD *xSim = new TMatrixD(*Inv_APrimT, TMatrixD::kMult, *cPrim);
	
	//eta 
	TMatrixD *eta = new TMatrixD(*A, TMatrixD::kMult, *xSim);
	
	
	
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	
	
	
	for(int i = 0; i < st+1; i++)
	{
		wsp[i] = (*xSim)(i, 0);
		bwsp[i] = TMath::Sqrt((*Inverted)(i, i));
		
		
		//cout << "X" << i << " = " << wsp[i] << " +/- " << bwsp[i] << endl;
	}
	
	
	double M = 0.0;
	for(int i = 0; i < n; i++)
	{
		M += TMath::Power(((yj[i] - (*eta)(i,0))/sigmaj[i]), 2);
	}
	
	
	
	
	return M;
}

void zadanie()
{
	
	//TCanvas *canva1 = new TCanvas("canva1", "lab9", 800, 600);
	double alpha = 0.01;
	double x[10], y[10], sigma[10], wsp[6], bwsp[6];
	double val1, val2;
	int index = 0;
	ifstream file;
	file.open("dane.dat");
	while(file >> val1 >> val2)
	{
		x[index] = val1;
		y[index] = val2;
		sigma[index] = TMath::Sqrt(val2);
		index++;
	}
	
	TCanvas *c1 = new TCanvas("c1", "Zadanie 11", 800, 600);
    TGraphErrors *errgraph = new TGraphErrors(index, x, y, NULL, sigma);
	c1 -> cd(1);
	errgraph -> SetTitle("Dane");
	errgraph -> GetXaxis() -> SetTitle("t, cos#theta");
	errgraph -> GetYaxis() -> SetTitle("y, liczba obserwacji");
    errgraph -> SetMarkerStyle(kFullCircle);
    errgraph -> SetMarkerSize(1.5);
    auto *legend = new TLegend(0.12, 0.6, 0.35, 0.9);
	legend -> AddEntry("errgraph", "dane pomiarowe");
	errgraph -> Draw();
	
	
	double M = 0.0;
	//dopasuj(5, 10, x, y, sigma, wsp, bwsp);
	for(int i = 0; i < 6; i++)
	{
		cout << "\n****** Wielomian stopnia " << i << "**********" << endl;
		M = dopasuj(i, 10, x, y, sigma, wsp, bwsp);
		cout << "Funkcja M = " << M << endl;
		
		
		TF1 *fun = new TF1 ("Data", Form("pol%d", i), -11, 11);
		
		for(int j = 0; j <= i; j++)
		{
			cout << "X" << j << " = " << wsp[j] << " +/- " << bwsp[j] << endl;
			fun -> SetParameter(j, wsp[j]);
		}

		fun -> SetLineColor(i+2);
	    legend -> AddEntry(fun, Form("st %d", i), "l");
		fun -> Draw("sameC");
		
		
		int ndf = 10 - 1 - i;
		cout << "Liczba stopni swobody = " << ndf << endl;
		cout << "Poziom istotnosci = " << alpha << endl;
		cout << "Kwantyl = " << TMath::ChisquareQuantile(1-alpha, ndf) << endl;
		
		bool tescik = testChi2(M, alpha, ndf);
		
		if(tescik == 1)
			cout << "Odrzucamy" << endl;
		else 
			cout << "Akceptujemy" << endl;
		
	}
	
	legend -> Draw();
	
	
}
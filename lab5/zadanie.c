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
	TCanvas* canva1 = new TCanvas("canva1", "lab5", width, height);
	canva1 -> Divide(2, 2);
	
	double x1min = 1.5;
	double x2min = 0;
	double x3min = 4;
	double x1max = 5;
	double x2max = 3;
	double x3max = 16;
	
	TH2D* th12 = new TH2D("th12", "hist 12", 100, x1min, x1max, 100, x2min, x2max);
	
	TH2D* th13 = new TH2D("th13", "hist 13", 100, x1min, x1max, 100, x3min, x3max);
	
	TH2D* th23 = new TH2D("th23", "hist 23", 100, x2min, x2max, 100, x3min, x3max);
	
	ifstream ifile;
	ifile.open("Dane1.dat");
	double val1;
	
	ifstream ifile2;
	ifile2.open("Dane2.dat");
	double val2;
	
	ifstream ifile3;
	ifile3.open("Dane3.dat");
	double val3;
	
	while(ifile >> val1 && ifile2 >> val2 && ifile3 >> val3)
	{
		th12 -> Fill(val1, val2);
		th13 -> Fill(val1, val3);
		th23 -> Fill(val2, val3);		
	}
	
	
	canva1 -> cd(1);
	th12 -> Draw("COLZ");
	
	canva1 -> cd(2);
	th13 -> Draw("COLZ");
	
	canva1 -> cd(3);
	th23 -> Draw("COLZ");

	ifile.close();
	ifile2.close();
	ifile3.close();
	
	double x1 = th12 -> GetMean(1);
	double x2 = th12 -> GetMean(2);
	double x3 = th23 -> GetMean(2);
	
	double ux1 = th12 -> GetStdDev(1);
	double ux2 = th12 -> GetStdDev(2);
	double ux3 = th23 -> GetStdDev(2);
	
	cout << "X1 = " << x1 << ", u(X1) = " << ux1 << endl;
	cout << "X2 = " << x2 << ", u(X2) = " << ux2 << endl;
	cout << "X3 = " << x3 << ", u(X3) = " << ux3 << endl;
	
	cout << "Po zaokragleniu: " << endl;
	cout << "X1 = " << setprecision(2) << x1 << ", u(X1) = " << ux1 << endl;
	cout << "X2 = " << setprecision(2) << x2 << ", u(X2) = " << ux2 << endl;
	cout << "X3 = " << setprecision(2) << x3 << ", u(X3) = " << ux3 << endl;
	
	cout << "Wspolczynnik korelacji th12: " << th12 -> GetCorrelationFactor() << endl;
	cout << "Wspolczynnik korelacji th13: " << th13 -> GetCorrelationFactor() << endl;
	cout << "Wspolczynnik korelacji th23: " << th23 -> GetCorrelationFactor() << endl;
	
	double cov1 = th12 -> GetCovariance(1, 2);
	double cov2 = th13 -> GetCovariance(1, 2);
	double cov3 = th23 -> GetCovariance(1, 2);
	
	double sigma1 = (th12 -> GetRMS(1))*(th12 -> GetRMS(1));
	double sigma2 = (th12 -> GetRMS(2))*(th12 -> GetRMS(2));
	double sigma3 = (th23 -> GetRMS(2))*(th23 -> GetRMS(2));
	
	TMatrixD matcov(3, 3);
	
	matcov(0,0) = sigma1;
	matcov(1,1) = sigma2;
	matcov(2,2) = sigma3;
	
	matcov(0,1) = cov1;
	matcov(1,0) = cov1;
	
	matcov(0,2) = cov2;
	matcov(2,0) = cov2;
	
	matcov(1,2) = cov3;
	matcov(2,1) = cov3;

	matcov.Print();
	
	double y1 = 3*x1 + 2*x2 + x3;
	double y2 = 2 + 5*x1 + 2*x2;
	
	TMatrixD mat(2, 3);
	mat(0,0) = 3;
	mat(0,1) = 2;
	mat(0,2) = 1;
	
	mat(1,0) = 5;
	mat(1,1) = 2;
	mat(1,2) = 0;
	
	TMatrix przed = mat * matcov;
	TMatrix help(3,2);
	help.Transpose(mat);
	
	TMatrix end = przed * help;
	end.Print();
	
	double uy1 = sqrt(end(0,0));
	double uy2 = sqrt(end(1,1));
	
	cout << "Y1 = " << y1 << ", u(Y1) = " << uy1 << endl;
	cout << "Y2 = " << y2 << ", u(Y2) = " << uy2 << endl;
	cout << "Po zaokragleniu: " << endl;
	cout << "Y1 = " << y1 << ", u(Y1) = " << uy1 << endl;
	cout << "Y2 = " << y2 << ", u(Y2) = " << uy2 << endl;
	
	double cor12 = end(0,1)/sqrt(end(0,0) * end(1,1));
	double cor21 = end(1,0)/sqrt(end(0,0) * end(1,1));
	
	cout << "rho(Y1, Y2) = " << cor12 << endl;
	cout << "rho(Y2, Y1) = " << cor21 << endl;
}
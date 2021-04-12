//
//
// rpp2020-rev-cosmic-rays, 30.3.1 Muons
// Eq.(30.4), valid for E_{mu} > 100 GeV, zenith angle (theta) > 70
//
//
double getFlux(double muonEnergy, double theta)
{
	double Emu = muonEnergy;       // GeV
	double costh = cos(theta); 

	double part1 = 1./(1 + 1.1 * Emu * costh / 115);
	double part2 = 0.054/(1 + 1.1 * Emu * costh/850);

	//double flux = 0.14 * pow(Emu, -2.7) * (part1 +  part2);
	double flux = 0.14 * (part1 +  part2);

	return flux * 10000;
}

double funFlux(double *x, double *par)
{
	double muonEnergy = x[0];

	// theta = 0
	return getFlux(muonEnergy, 0);
}

void muonFlux0()
{
   TCanvas* c1 = new TCanvas("c1", "  ");
   c1->SetLogx();
   c1->SetLogy();
   c1->SetGrid();


   TF1 *f1 = new TF1("func", funFlux, 1, 1000, 1);
   f1->GetYaxis()->SetRangeUser(10, 10000);

   f1->Draw();
}

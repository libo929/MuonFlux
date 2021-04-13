//
// arXiv:1509.06176v1, A parametrization of the cosmic-ray muon flux at sea-level
// Eq.(3) is for random muon energy generation, from 0.1 to 2000 GeV for zenith angle 0 degree.
//
double getFlux(double muonEnergy, double theta)
{
	const double P1 = 0.102573;
	const double P2 = -0.068287;
	const double P3 = 0.958633;
	const double P4 = 0.0407253;
	const double P5 = 0.817285;

	double cosTheta = cos(theta); 
	double cosThetaStar2 = ( cosTheta * cosTheta + P1 * P1 + P2 * pow(cosTheta, P3) + P4 * pow(cosTheta, P5) ) /
		(1. + P1*P1 + P2 + P4);
	double cosThetaStar = sqrt(cosThetaStar2);

	double Emu = muonEnergy;       // GeV

	double term1 = 1./(1 + 1.1 * Emu * cosThetaStar/115);
	double term2 = 0.054/(1 + 1.1 * Emu * cosThetaStar/850);

	double flux = 0.14 * pow(Emu * (1. + 3.64/(Emu * pow(cosThetaStar, 1.29))), -2.7) * (term1 +  term2);

	return flux * 10000; // 1/cm^2 -> 1/m^2
}

double funFlux(double *x, double *par)
{
	double muonEnergy = x[0];
	double theta = par[0]/180. * TMath::Pi();

	return getFlux(muonEnergy, theta);
}

void genMuon()
{
   TCanvas* c1 = new TCanvas("c1", "  ");
   c1->SetLogx();
   c1->SetLogy();
   c1->SetGrid();

   TF1 *f1 = new TF1("f0", funFlux, 0.1, 2000, 1);
   f1->SetParameter(0, 0.);

   TH1F* hist = new TH1F("", "", 20000-1, 0.1, 2000);

   for(int i = 0; i < 10000000; ++i)
   {
	   hist->Fill(f1->GetRandom());
   }

   hist->Draw();

   c1->Print("genMuon.pdf");
}

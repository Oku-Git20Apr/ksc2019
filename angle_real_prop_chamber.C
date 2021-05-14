static const double pi = 3.141592;
int cos_rand(double);

double myfunc(double *x, double *par){
	double x0 = x[0];
	double a = par[0];
	double b = par[1];
	double c = par[2];

	return a*pow(cos((x0-5)*pi/180),b)+c;
}

//Nuclear Instruments and Methods in Physics Research A 555 (2005) 164-172
double cosmic(double *x, double *par){
	double theta  = x[0];
	double E   = 1.;
	double DE  = 0.02;
	double gpi = 0.78;
	double gk  = 0.52;
	double Bpi = 90.;//GeV
	double Bk  = 442.;//GeV
	double br  = 0.635;
	double gamma = 2.70;
	double W   = 1.;
	double factor1 = A*pow(W,-1.*gamma);
	double factor2 = (pow(gpi,gamma-1.)*Bpi*sec(theta))/(E+DE+Bpi*sec(theta));
	double factor3 = 0.36*br*(pow(gk,gamma-1.)*Bk*sec(theta))/(E+DE+Bk*sec(theta));

	return factor1*(factor2+factor3);
}

void angle_real_prop_chamber(const char* output_text_file = "./prop_monte_sim.txt")
{
  gROOT->Reset();
  FILE* fp;
  char line[300];



    TCanvas *c1 = new TCanvas("simulation","c1");
    //c1->SetGrid();
    c1->SetFillColor(10);
 


  int nofhist = 3;	
//   TH1D *h1 = new TH1D("num_int","",5,0,5);
    TH1D *h[nofhist];
  
  int value;

//  fp = fopen( output_text_file, "w" );

  for (int i=0; i<nofhist; i++){
    h[i] = new TH1D(Form("Monte_Carlo%d",i),"",100,-5,95);
	for (int j=0; j<238000*91/4; j++) {//loop (=total number of events)
		value = cos_rand(1+(double)i*1.);
		h[i]->Fill(value);
	}
	h[i]->Scale(1./1000.);
  }
  

//  if ( fp == NULL ) {
//    printf( "cannot open %s\n", output_text_file );
//    exit(1);
//  }
//
//  fprintf( fp, "%8.5e\n", value);
//    
//   }
//  fclose( fp );
  
  h[nofhist-1]->SetXTitle("Angle [degree]");
  h[nofhist-1]->SetYTitle("Counts");
  h[nofhist-1]->SetStats( 0 );
//  h[nofhist-1]->SetLineStyle(1);
  h[nofhist-1]->SetLineColor(1);
  h[nofhist-1]->SetLineWidth(1);
  h[nofhist-1]->GetXaxis()->SetNdivisions(510);
  h[nofhist-1]->GetXaxis()->SetTitleOffset(1.5);
  h[nofhist-1]->Draw("");
	for(int i=0;i<nofhist;i++){
		h[i]->SetLineColor(nofhist-i);
		h[i]->SetLineWidth(1);
		h[i]->Draw("same");
	}
  h[nofhist-1]->Draw("same");
  
/////////plot only cos^2(t)  
//  h[2]->SetXTitle("Angle [degree]");
//  h[2]->SetYTitle("Counts");
//  h[2]->SetLineColor(kAzure);
//  h[2]->SetLineWidth(1);
//  h[2]->GetXaxis()->SetNdivisions(110);
//  h[2]->GetXaxis()->SetTitleOffset(1.5);
//  h[2]->SetStats( 0 );
//  h[2]->Draw();
///////////
  TGraphErrors *g = new TGraphErrors("cosmic_prop.dat");  
  g->SetLineWidth(3);
  g->SetLineColor(kAzure);
  g->Draw("Lsame");

  TF1 *func = new TF1("func",myfunc,5.,95.,3);
  func->SetNpx(600);
  func->SetParameter(0,500.);
  func->SetParameter(1,2.);
  func->SetParameter(2,0.);
  func->SetLineColor(kRed);
//  h[2]->Fit(func,"","",5.,95.);
//  g->Fit(func,"","",5.,95.);
//  func->Draw("same");


  cout << "output_text_file = " << output_text_file << endl;


}


int cos_rand(double zenith_pow)
{
  //////////first position(x,y) t=theta,p=phi,last position(x_l,y_l)
  double x,y,z,t,p,k,x_l,y_l,e;
  double t_max=pi/2;
  double k_max=1.;
  double p_max=2*pi;
  double x_max=17; //[cm]
  double y_max=1.9; //[cm]
  double val;
 
  double cosine;
  double t0, t0deg;
  double num;
  double theta;

  while(1){
	cosine = gRandom -> Uniform();
    t = acos(cosine);
    p = gRandom ->Uniform()*p_max;
	k = gRandom ->Uniform()*k_max;
    x = gRandom ->Uniform()*x_max;
    y = gRandom ->Uniform()*y_max;
    x_l=x+7.1*tan(t)*cos(p);//length of the chamber [cm]
    y_l=y+7.1*tan(t)*sin(p);//width of the chamber [cm]
 
	double flag = 0;
	t0deg = gRandom->Integer(90);
	t0 = (double)t0deg * pi/180;
	theta = -sin(t0)*sin(t)*sin(p)+cos(t0)*cos(t);
	val = pow(theta,zenith_pow);	
	if (k <= val && x_l>0 && x_l<x_max && y_l>0 && y_l<y_max){
	flag = 1;
			}
	if (flag == 1) break;
  }



// 	cout<< "val=" <<val<<endl;
//	cout<< "theta=" <<t*180/pi<<endl;
//	cout<< "x=" <<x;
//	cout<< "x_l=" <<x_l90<<endl;
//	cout<< "y=" <<y;
//	cout<< "y_l=" <<y_l90<<endl;
	
  
//  cout << "x=" << x << endl;
//  cout << "e=" << e << endl;
//  cout << "z=" << z << endl;
//  cout << "d=" << d << endl;
//  cout << "w=" << w << endl;

	return t0deg;
  
 
}

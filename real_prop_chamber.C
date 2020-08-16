double cos_rand(double);

double myfunc(double *x, double *par){
	double x0 = x[0];
	double a = par[0];
	double b = par[1];
	double c = par[2];

	return a*pow(cos((x0-5)*PI/180),b)+c;
}

void real_prop_chamber(const char* output_text_file = "./prop_monte_sim.txt")
{
  gROOT->Reset();
  FILE* fp;
  char line[300];



    TCanvas *c1 = new TCanvas("simulation","c1");
    //c1->SetGrid();
    c1->SetFillColor(10);
 


  int nofhist = 5;	
//   TH1D *h1 = new TH1D("num_int","",5,0,5);
    TH1D *h[nofhist];
  
  double value;

//  fp = fopen( output_text_file, "w" );

  for (int i=0; i<nofhist; i++){
    h[i] = new TH1D(Form("Monte_Carlo%d",i),"",10,0,100);
	for (int j=0; j<238; j++) {//loop (=total number of events)
		value = cos_rand(1+(double)i*0.5);
		h[i]->Fill(value);
	}
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
  h[nofhist-1]->GetXaxis()->SetNdivisions(110);
  h[nofhist-1]->GetXaxis()->SetTitleOffset(1.5);
  h[nofhist-1]->Draw("");
	for(int i=0;i<nofhist;i++){
		h[i]->SetLineColor(nofhist-i);
		h[i]->SetLineWidth(1);
		h[i]->Draw("same");
	}
  h[nofhist-1]->Draw("same");
  
/////////plot only cos^2(t)  
  h[2]->SetXTitle("Angle [degree]");
  h[2]->SetYTitle("Counts");
  h[2]->SetLineColor(kAzure);
  h[2]->SetLineWidth(1);
  h[2]->GetXaxis()->SetNdivisions(110);
  h[2]->GetXaxis()->SetTitleOffset(1.5);
  h[2]->SetStats( 0 );
  h[2]->Draw();
///////////
  TGraphErrors *g = new TGraphErrors("cosmic_prop.dat");  
  g->SetLineWidth(3);
  g->SetLineColor(kRed);
  g->Draw("Psame");

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


double cos_rand(double zenith_pow)
{
  //////////first position(x,y) t=theta,p=phi,last position(x_l,y_l)
  double pi = 3.141592;
  double x,y,z,t,p,k,x_l,y_l,e;
  double t_max=pi/2;
  double k_max=1.;
  double p_max=2*pi;
  double x_max=17; //[cm]
  double y_max=1.9; //[cm]
  double val;
 
  double cosine;
  double t0;
  double num;
  double theta1, theta2, theta3, theta4;
  int num2, num_int;

  while(1){
	cosine = gRandom -> Uniform();
    t = acos(cosine);
    p = gRandom ->Uniform()*p_max;
	k = gRandom ->Uniform()*k_max;
    x = gRandom ->Uniform()*x_max;
    y = gRandom ->Uniform()*y_max;
    x_l=x+7.1*tan(t)*cos(p);//length of the chamber [cm]
    y_l=y+7.1*tan(t)*sin(p);//width of the chamber [cm]
 
	//////////////////generating 1,2,3,4 randomly
	num = gRandom ->Uniform(39999);
	num2 = (int)num;
	num_int = num2 % 4 +1;
//    cout << "num_int=" << num_int <<endl;

	int flag = 0;
	switch(num_int){
	case 1:
		t0 = 0.;//not tilted
		theta1 = -sin(t0)*sin(t)*sin(p)+cos(t0)*cos(t);
		val = pow(cos(acos(theta1)),zenith_pow);	
		if (k <= val && x_l>0 && x_l<x_max && y_l>0 && y_l<y_max){
		e = 0;
		flag = 1;
			}		
		break;
 
	case 2:
		t0 = pi/6;//tilted by 30 deg
		theta2 = -sin(t0)*sin(t)*sin(p)+cos(t0)*cos(t);
		val = pow(cos(acos(theta2)),zenith_pow);	
		if (k <= val && x_l>0 && x_l<x_max && y_l>0 && y_l<y_max){ 
		e = 30;
		flag = 1;
			}		
		break;

	case 3:
		t0 = pi/3;//tilted by 60 deg
		theta3 = -sin(t0)*sin(t)*sin(p)+cos(t0)*cos(t);
		val = pow(acos(cos(theta3)),zenith_pow);	
		if (k <= val && x_l>0 && x_l<x_max && y_l>0 && y_l<y_max){ 
		e = 60;
		flag = 1;
			}		
		break;

	case 4:
		t0 = pi/2;//tilted by 90 deg
		theta4 = -sin(t0)*sin(t)*sin(p)+cos(t0)*cos(t);
		val = pow(acos(cos(theta4)),zenith_pow);	
		if (k <= val && x_l>0 && x_l<x_max && y_l>0 && y_l<y_max){
		e = 90;
		flag = 1;
			}		
		break;
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



//   return num_int;
	return e;

  
 
}

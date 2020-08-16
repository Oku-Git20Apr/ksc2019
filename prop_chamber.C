double cos_rand();

void prop_chamber(const char* output_text_file = "./prop_monte_sim.txt")
{
  gROOT->Reset();
  FILE* fp;
  char line[300];



    TCanvas *c1 = new TCanvas("simulation","c1");
    //c1->SetGrid();
    c1->SetFillColor(10);
  
   TH1F *h1 = new TH1F("Monte_Carlo","",10,-0.05,1.6);
  
  double value;

  fp = fopen( output_text_file, "w" );

  for (int i=0; i<1000; i++) {
    value = cos_rand();
    h1->Fill(value);

      //input histgram to file
    
  if ( fp == NULL ) {
    printf( "cannot open %s\n", output_text_file );
    exit(1);
  }

  fprintf( fp, "%8.5e\n", value);
    
   }
  fclose( fp );
  
  h1->SetXTitle("angle[rad]");
  h1->SetYTitle("event[count]");

  h1->SetStats( 0 );
  h1->SetLineStyle(2);
  h1->Draw();

    cout << "output_text_file = " << output_text_file << endl;

}


double cos_rand()
{
  //first position(x,y) t=theta,p=phi,last position(x_l,y_l)
   float pi = 3.141592;
  double dt = 0.08; //0.5deg?
  double dp = 0.08;
  double t_max=pi/2;
  double k_max=1.;
  double p_max=2*pi;
  double x_max=19; //[cm]
  double y_max=2; //[cm]
  double x,y,z,t,p,x_l0,y_l0,x_l30,y_l30,x_l60,y_l60,x_l90,y_l90;
  double val;
 
  float c, cc, d, e, g,k,w;

  while(1){
	double cosine;
	cosine = gRandom -> Uniform();
//    t = gRandom ->Uniform()*t_max;
    t = acos(cosine);
	k = gRandom ->Uniform()*k_max;
    p = gRandom ->Uniform()*p_max;
    x = gRandom ->Uniform()*x_max;
    y = gRandom ->Uniform()*y_max;
    x_l0=x+7.1*tan(t)*cos(p);//length of the chamber [cm]
    y_l0=y+7.1*tan(t)*sin(p);//width of the chamber [cm]
    x_l30=x+7.1*cos(pi/6)*tan(t)*cos(p);//length of the chamber [cm]
    y_l30=y+7.1*cos(pi/6)*tan(t)*sin(p);//width of the chamber [cm]
    x_l60=x+7.1*cos(pi/3)*tan(t)*cos(p);//length of the chamber [cm]
    y_l60=y+7.1*cos(pi/3)*tan(t)*sin(p);//width of the chamber [cm]
    x_l90=x;//length of the chamber [cm]
    y_l90=y;//width of the chamber [cm]
  
    //val = 2*pi*sin(t)*dt*pow(cos(t),3.5);
    val = pow(cos(t),2.);
     
    if (k <= val && x_l0>0 && x_l0<x_max && y_l0>0 && y_l0<y_max){ //theta=0deg
	e = 0;
	break;
	}
    if (k <= val && x_l30>0 && x_l30<x_max && y_l30>7.1*sin(pi/6) && y_l30<y_max+7.1*sin(pi/6)){ //theta=30deg
	e = 30*pi/180;
	break;
	}
    if (k <= val && x_l60>0 && x_l60<x_max && y_l60>7.1*sin(pi/3) && y_l60<y_max+7.1*sin(pi/3)){ //theta=60deg
	e = 60*pi/180;
	break;
	}
    if (k < val && x_l90>0 && x_l90<x_max && y_l90>7.1 && y_l90<y_max+7.1){ //theta=90deg
	e = 90*pi/180;
	cout<< "val=" <<val<<endl;
	cout<< "theta=" <<t*180/pi<<endl;
	cout<< "x=" <<x;
	cout<< "x_l=" <<x_l90<<endl;
	cout<< "y=" <<y;
	cout<< "y_l=" <<y_l90<<endl;
	break;
	}
  }
  //cout << "x=" << x << endl;

   
   //cout << "e=" << e << endl;
   //cout << "z=" << z << endl;
   //cout << "d=" << d << endl;
   //cout << "w=" << w << endl;

   return e;
  
 
}

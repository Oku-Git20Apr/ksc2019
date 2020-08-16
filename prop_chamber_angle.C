double cos_rand();

void prop_chamber_angle(const char* output_text_file = "./prop_monte_sim.txt")
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

  for (int i=0; i<100000; i++) {
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
  double x,y,z,t,t2,p,x_l,y_l;
  double val;
 
  float c, cc, d, e, g,k,w;

  while(1){
	double cosine,cosine2;
	cosine = gRandom -> Uniform();
	t2 = gRandom -> Uniform()*pi/2;
//    t = gRandom ->Uniform()*t_max;
    t = acos(cosine);
//	t2 = acos(cosine2);
	k = gRandom ->Uniform()*k_max;
    p = gRandom ->Uniform()*p_max;
    x = gRandom ->Uniform()*x_max;
    y = gRandom ->Uniform()*y_max;
    x_l=x+7.1*cosine2*tan(t)*cos(p);//length of the chamber [cm]
    y_l=y+7.1*cosine2*tan(t)*sin(p);//width of the chamber [cm]
  
    //val = 2*pi*sin(t)*dt*pow(cos(t),3.5);
    val = pow(cos(t),2.);
     
    if (k <= val && x_l>0 && x_l<x_max && y_l>7.1*sin(t2) && y_l<7.1*sin(t2)+y_max){ 
	e = t2;
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

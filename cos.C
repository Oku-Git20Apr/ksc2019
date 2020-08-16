double cos_exp();

void cos(const char* output_text_file = "/home/toyama/spacha/se2/simu_result3_5jou_tes.txt")
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
  h1->Draw("C");

    cout << "output_text_file = " << output_text_file << endl;

}


double* cos_rand()
{
  //first position(x,y) t=theta,p=phi,last position(x_l,y_l)
   float pi = 3.141592;
  double dt = 0.08;
  double dp = 0.08;
  double t_max=1.6;
  double k_max=1.;
  double p_max=2*pi;
  double x_max=100;
  double y_max=10;
  double x, y,z,t,p,x_l,y_l;
  double val;
 
  float c, cc, d, e, g,k,w;

  while(1){
    t = gRandom ->Uniform()*t_max;
    k = gRandom ->Uniform()*k_max;
    p = gRandom ->Uniform()*p_max;
    x = gRandom ->Uniform()*x_max;
    y = gRandom ->Uniform()*y_max;
    x_l=x+33.4*tan(t)*cos(p);
    y_l=y+33.4*tan(t)*cos(p);  
  
    val = 2*pi*sin(t)*dt*pow(cos(t),3.5);
    // val = cos(t)**2;
     
    if (k <= val && x_l<100 && y_l<10)
      break;
  }
  //cout << "x=" << x << endl;


   c=sqrt((tan(t)*cos(p))**2 + 1) ;	
   cc=1/c ; //cos(theta_sokutei)
   e = acos(cc);
   
   //cout << "e=" << e << endl;
   //cout << "z=" << z << endl;
   //cout << "d=" << d << endl;
   //cout << "w=" << w << endl;

   return e;
  
 
}

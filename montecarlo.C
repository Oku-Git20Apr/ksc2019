void montecarlo(){

	double theta[100000];
	int counter = 0;
	double x;
	double y;
	FILE *fp;

	int n = 2;

	for ( int i = 0; i < 100000; i++){
		x=gRandom->Uniform(0,1.5707963); //90[deg]
		y=gRandom->Uniform(0,1);

		double sin = TMath::Sin(x);
		double cos = TMath::Cos(x);
		double cosn = TMath::Power(cos,n);

		if(cosn*sin > y){
			theta[counter] = x;
			counter++;
		}
	}

	const char* montecarlo_data = "./montecarlo_data.txt";

	fp = fopen( montecarlo_data, "w" );

	if (fp == NULL){
			printf( "cannot open %s\n", montecarlo_data);
			exit(1);
	}

	for ( int i = 0; i < counter; i++){
		double deg = theta[i]*100/3.14159265359;
		fprintf( fp, "%8.5e\n", deg);
	}

	fclose(fp);
}

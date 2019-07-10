#include "Initialize.h"
#include <ctime>
#include <sys/time.h>
#include <iostream>
#include <time.h>
#include "ILS-Functions.h"

char* InstanciaFile;
char* OutputFile;
float Opt;
unsigned int N,M,Seed;
float numEvals;
vector < float > Profits;
vector < float > Aux;
//vector < int > BestFactible;
//double BestFitFactible;
vector <vector < float > > Weights;
vector < int > BestSolutionFound;
//vector < int > BestReachedOpt;
double BestFitnessFound;
vector < double > Output;
//bool validado;
//int n_tests;
vector < float > b_i;
float TotalEvaluations;
int numberPerturbations;
int tries;

//LON Structures & Variables

vector < vector <int> > AllSolutionsFrom;
vector < vector <int> > AllSolutionsTo;
vector < float > QualityAllSolutionsFrom;
vector < float > QualityAllSolutionsTo;

using namespace std;

int main(int argc, char** argv) {
    //int localMethod;
    //bool localFS;
    //char* names;
    Capture_Params(argc,argv);
	Read_Instance();
	srand48(Seed);
	ILS();
	GenerateOutputFileLON();
	//PrintInstancia();







        //cout << BestFitnessFound << " " << 100*(Opt - BestFitnessFound)/Opt << " " << gap_avg << endl;

	return 0;
}


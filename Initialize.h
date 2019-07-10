
#ifndef INITIALIZE_H_
#define INITIALIZE_H_
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <iostream>
using namespace std;
using std::ifstream;

void Capture_Params(int argc, char** argv);
bool Read_Instance();
void PrintInstancia();
int int_rand (int a, int b);
float float_rand (float a, float b);
void GenerateOutputFileLON();

extern char* InstanciaFile;
extern char* OutputFile;
extern float Opt,numEvals;
extern int eval;
extern unsigned int N,M,Seed;
extern float TotalEvaluations;
extern vector < float > Profits;
extern vector < float > Aux;
extern vector <vector < float > > Weights;
extern vector < int > BestSolutionFound;
extern double BestFitnessFound;
extern vector < float > b_i;
extern int numberPerturbations;
extern vector < vector <int> > AllSolutionsFrom;
extern vector < vector <int> > AllSolutionsTo;
extern vector < float > QualityAllSolutionsFrom;
extern vector < float > QualityAllSolutionsTo;


#endif /* INITIALIZE_H_ */

//
// Created by Nicolás  Rojas on 7/3/19.
//

#ifndef ILS_MKP_ILS_FUNCTIONS_H
#define ILS_MKP_ILS_FUNCTIONS_H
#include <vector>
#include <iostream>
#include "CandidateSolution.h"

using namespace std;
using std::ifstream;

void ILS();
bool ValidateSolution(vector<int> CS);
void InitialSolution(CandidateSolution &CS);
void LocalSearch(CandidateSolution &CS);
void AddRandomlyObjectsUntilFullKnapsack(CandidateSolution &CS);
void Perturbation(CandidateSolution &CS);
void StoreSolutions(CandidateSolution &From, CandidateSolution &To);

extern char* InstanciaFile;
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
extern int tries;



#endif //ILS_MKP_ILS_FUNCTIONS_H

//
// Created by Nicolás  Rojas on 7/3/19.
//

#ifndef ILS_MKP_CANDIDATESOLUTION_H
#define ILS_MKP_CANDIDATESOLUTION_H

#include <vector>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

extern float Opt;
extern int eval;
extern float numEvals;
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

class CandidateSolution {

public:

    void IncludeObject(int id_obj);
    void DropObject(int id_obj);
    float getQuality();
    vector<int> getSolution();
    vector<float> getRC();
    void InitCS();
    void SetSolution(float Q, vector<float> CR, vector<int> CS);
    int getSizeAllowed();
    void ComputeAllowedObjects(); //al inicio o cuando se hace un drop de object
    vector < int > getIncludedObjects();
    vector < int > getExcludedObjects();
    int getSizeIncluded();
    bool CheckIfObjectIsAllowed(int id_obj);
    void PrintSolution();

private:
    float Quality;
    vector < float > RemCapacity;
    vector < int > Solution;
    vector < int > IncludedObjects;
    vector < int > ExcludedObjects;
    vector < int > AllowedObjects;


};


#endif //ILS_MKP_CANDIDATESOLUTION_H

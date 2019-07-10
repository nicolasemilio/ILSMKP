//
// Created by Nicolás  Rojas on 7/3/19.
//

#include "CandidateSolution.h"
#include "Initialize.h"

using namespace std;
using std::ifstream;


void CandidateSolution::InitCS(){
    unsigned int i;
    this->Quality = 0;
    for (i = 0; i < N; i++) {
        this->Solution.push_back(0);
        this->ExcludedObjects.push_back(i);
    }
    this->RemCapacity = b_i;
}


void CandidateSolution::IncludeObject(int id_obj){

    unsigned int j,toerase;
    bool flag = true;



    //UPDATE OF CAP REM
    for (j = 0; j < Weights.size(); j++) {
        this->RemCapacity[j] -= Weights[j][id_obj];
    }

    this->Quality += Profits[id_obj];
    this->Solution[id_obj] = 1;
    this->IncludedObjects.push_back(id_obj);


    for(j = 0; ((j < this->ExcludedObjects.size()) && flag); j++){
        if(this->ExcludedObjects[j] == id_obj) {
            toerase = j;
            flag = false;
        }
    }

    //Sacamos toerase de ExcludedObjects
    this->ExcludedObjects.erase(this->ExcludedObjects.begin()+toerase);


}

void CandidateSolution::DropObject(int id_obj){

    unsigned int j,toerase;
    bool flag = true;

    //UPDATE OF CAP REM
    for (j = 0; j < Weights.size(); j++) {
        this->RemCapacity[j] += Weights[j][id_obj];
    }

    this->Quality -= Profits[id_obj];
    this->Solution[id_obj] = 0;

    this->ExcludedObjects.push_back(id_obj);


    for(j = 0; ((j < this->IncludedObjects.size()) && flag); j++){
        if(this->IncludedObjects[j] == id_obj){
            toerase = j;
            flag = false;
        }
    }

    //Sacamos toerase de IncludedObjects
    this->IncludedObjects.erase(this->IncludedObjects.begin()+toerase);
}

float CandidateSolution::getQuality(){
    return this->Quality;
}

vector <int> CandidateSolution::getSolution(){
    return this->Solution;
}
vector <float> CandidateSolution::getRC(){
    return this->RemCapacity;
}

int CandidateSolution::getSizeIncluded(){
    return this->IncludedObjects.size();
}

void CandidateSolution::SetSolution(float Q, vector<float> CR, vector<int> CS){
    this->Quality = Q;
    this->RemCapacity = CR;
    this->Solution = CS;
}


int CandidateSolution::getSizeAllowed(){
    return this->AllowedObjects.size();
}

void CandidateSolution::ComputeAllowedObjects(){

    bool flag = true;
    unsigned int i,j;
    int aux_id;

    this->AllowedObjects.clear();

    for(i = 0; i < this->ExcludedObjects.size(); i++){
        aux_id = this->ExcludedObjects[i];
        for(j = 0; ((j < this->RemCapacity.size()) && flag); j++){
            if(this->RemCapacity[j] < Weights[j][aux_id]){
                flag = false;
            }
        }

        if(flag){
            this->AllowedObjects.push_back(aux_id);
        }

        flag = true;
    }

}

vector <int> CandidateSolution::getExcludedObjects(){
    return this->ExcludedObjects;
}

vector <int> CandidateSolution::getIncludedObjects(){
    return this->IncludedObjects;
}

//Input: Object index id_obj will be checked
//Output: True if object id_obj it is allowed to be included, False o.w.
bool CandidateSolution::CheckIfObjectIsAllowed(int id_obj){
    bool flag = true;
    unsigned int j;

    for(j = 0; ((j < this->RemCapacity.size()) && flag); j++){
        if(this->RemCapacity[j] < Weights[j][id_obj]){
            flag = false;
        }
    }

    return flag;
}

void CandidateSolution::PrintSolution(){

    unsigned int i,j;

    cout << "SOLUCION - Quality:" << this->Quality << endl;

    for(i = 0; i < this->RemCapacity.size();i++){
        cout << "Dimension " << i << " RemCap:" << this->RemCapacity[i] << " of " << b_i[i] << endl;
    }

    for(i = 0; i < this->Solution.size();i++){
        if(this->Solution[i] == 1){
            cout << "Object " << i << " Profit: "<< Profits[i] << endl;
        }
        else{
            cout << "******* Discarded Object - Id: " << i << " Weights: " << endl;
            for(j = 0; j < Weights.size(); j++){
                cout << "Dim " << j << " : " << Weights[j][i] << " - RC:" << this->RemCapacity[j] << endl;
            }
        }
    }

    cout << "INCLUDED OBJECTS" << endl;
    for(i = 0; i < this->IncludedObjects.size(); i++){
        cout << IncludedObjects[i] << endl;
    }

    cout << endl;
    cout << "EXCLUDED OBJECTS" << endl;
    for(j = 0; j < this->ExcludedObjects.size();j++){
        cout << ExcludedObjects[j] << endl;
    }


}
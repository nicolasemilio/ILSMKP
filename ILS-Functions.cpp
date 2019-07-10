//
// Created by Nicolás  Rojas on 7/3/19.
//

#include "ILS-Functions.h"
#include "CandidateSolution.h"
#include "Initialize.h"

using namespace std;
using std::ifstream;


vector <int> auxiliar;
vector <int> auxiliarExcl;

float Q_CS;


void ILS(){

    numEvals = 0;
    CandidateSolution CurrentSolution,AuxCS;
    CurrentSolution.InitCS();
    InitialSolution(CurrentSolution);
    LocalSearch(CurrentSolution);

    tries = 0;

    //AGREGAR CONTEO DE EVALUACIONES
    //
    while(numEvals < TotalEvaluations) {
        AuxCS = CurrentSolution;
        Perturbation(AuxCS);
        LocalSearch(AuxCS);
        if (CurrentSolution.getQuality() <= AuxCS.getQuality()) {
            //if(CurrentSolution.getQuality() < AuxCS.getQuality()) StoreSolutions(CurrentSolution, AuxCS);
            StoreSolutions(CurrentSolution, AuxCS);
            CurrentSolution = AuxCS;
        }
        tries++;
    }

    //cout << tries << endl;
    //CurrentSolution.PrintSolution();




}

void StoreSolutions(CandidateSolution &From, CandidateSolution &To){

    AllSolutionsFrom.push_back(From.getSolution());
    AllSolutionsTo.push_back(To.getSolution());
    QualityAllSolutionsFrom.push_back(From.getQuality());
    QualityAllSolutionsTo.push_back(To.getQuality());

}

//Generate a initial solution randomly.
void InitialSolution(CandidateSolution &CS){
    unsigned int id_obj;
    auxiliar.clear();
    auxiliar = CS.getExcludedObjects();
    while(auxiliar.size()>0){
        id_obj = int_rand(0,auxiliar.size()-1);
        if(CS.CheckIfObjectIsAllowed(auxiliar[id_obj])){
            CS.IncludeObject(auxiliar[id_obj]);
            auxiliar.erase(auxiliar.begin()+id_obj);
        }
        else{
            auxiliar.erase(auxiliar.begin()+id_obj);
        }
    }
    numEvals++;
}

void AddRandomlyObjectsUntilFullKnapsack(CandidateSolution &CS){
    unsigned int id_obj;
    float num,den;
    auxiliar.clear();
    auxiliar = CS.getExcludedObjects();
    den = CS.getSizeIncluded();
    num = 0;
    while(auxiliar.size()>0){
        id_obj = int_rand(0,auxiliar.size()-1);
        if(CS.CheckIfObjectIsAllowed(auxiliar[id_obj])){
            CS.IncludeObject(auxiliar[id_obj]);
            auxiliar.erase(auxiliar.begin()+id_obj);
        }
        else{
            auxiliar.erase(auxiliar.begin()+id_obj);
        }
        num++;
    }
    numEvals += ((float)num/N);

}

void Perturbation(CandidateSolution &CS){
    unsigned int id_obj,droppedObjects;

    /*SE SACAN A LO MÁS, numberPerturbations Objects*/
    auxiliar.clear();
    auxiliar = CS.getIncludedObjects();
    droppedObjects = numberPerturbations;
    while((auxiliar.size()>0) && (droppedObjects > 0)){
        id_obj = int_rand(0,auxiliar.size()-1);
        CS.DropObject(auxiliar[id_obj]);
        auxiliar.erase(auxiliar.begin()+id_obj);
        droppedObjects--;
    }

    /*Se agregan objetos aleatoriamente hasta que se llene la mochila*/
    AddRandomlyObjectsUntilFullKnapsack(CS);

}

void LocalSearch(CandidateSolution &CS){
    unsigned int i,id_obj_incl,id_obj_excl,aux_sacado;
    float PreQ,Sum,QualityAux = 0;
    bool LOFlag = true;
    bool DeltaFlag = true;
    CandidateSolution AuxCS;
    AuxCS = CS;
    auxiliar = CS.getIncludedObjects();
    QualityAux = CS.getQuality();

    while(LOFlag){
        //VOY A INTENTAR SACAR OBJETOS UNO A UNO, ALEATORIAMENTE
        while((auxiliar.size() > 0) && DeltaFlag){

            //Escojo aleatoriamente uno
            id_obj_incl = int_rand(0,auxiliar.size()-1);
            //almaceno el sacado
            aux_sacado = auxiliar[id_obj_incl];
            //almaceno la solucion candidata con la que entré.
            AuxCS = CS;
            //saco el objeto
            AuxCS.DropObject(aux_sacado);
            //obtengo los que podría incluir
            auxiliarExcl = AuxCS.getExcludedObjects();
            //VOY A INTENTAR AGREGAR OBJETOS UNO A UNO, ALEATORIAMENTE
            while((auxiliarExcl.size() > 0) && DeltaFlag){
                //De los excluidos, escojo uno aleatoriamente
                id_obj_excl = int_rand(0,auxiliarExcl.size()-1);
                //si no es el que ya estaba adentro
                if(auxiliarExcl[id_obj_excl] != aux_sacado){
                    //Si de mejor calidad y es factible, me cambio
                    PreQ = AuxCS.getQuality() + Profits[auxiliarExcl[id_obj_excl]];
                    Sum = ((float)1/N);
                    numEvals += Sum;

                    if(PreQ > QualityAux) { //Preguntar si es mayor igual
                        if(AuxCS.CheckIfObjectIsAllowed(auxiliarExcl[id_obj_excl])){
                            AuxCS.IncludeObject(auxiliarExcl[id_obj_excl]);
                            DeltaFlag = false;
                            //ME CAMBIO PARA ALLA
                        }
                        else{
                            auxiliarExcl.erase(auxiliarExcl.begin()+id_obj_excl);
                        }
                    }
                    else{
                        auxiliarExcl.erase(auxiliarExcl.begin()+id_obj_excl);
                    }
                }
                else{
                    auxiliarExcl.erase(auxiliarExcl.begin()+id_obj_excl);
                }
            }

            if(DeltaFlag){
                auxiliar.erase(auxiliar.begin()+id_obj_incl);
            }
        }

        if(DeltaFlag){
            LOFlag = false;
            //No me quedan más objetos por sacar, estoy en un óptimo local
        }
        else{
            //Me cambié de Solución. Comienzo a evaluar sobre una nueva solución
            //cout << "Cambio de Solución" << endl;
            DeltaFlag = true;
            CS = AuxCS;
            QualityAux = CS.getQuality();
            auxiliar = CS.getIncludedObjects();
            //CS.PrintSolution();
        }
    }

    //cout << "Terminé la Solución" << endl;

}


bool ValidateSolution(vector<int> CS) {

    float auxmuch = 0;
    unsigned int i, j;

    for (i = 0; i < Weights.size(); i++) {
        for (j = 0; j < Weights[i].size(); j++) {
            auxmuch += Weights[i][j] * CS[j];
        }

        if (auxmuch > b_i[i]) {
            return false;
        }
        auxmuch = 0;
    }

    return true;
}


/*
bool LocalOptimaCheck(float Fit){
//en auxiliar esta la solucion
//en CapRem la cap remanente de cada dimension
//Weights[i][j] el peso de cada cosa
//visited = objeto es 1 cuando no lo han visitado

    unsigned int i,j, indi,indiall,cicles,newallow;
    vector <int> auxiauxi;
    vector <int> auxiVisited;
    vector <float> capAux;
    vector <int> LOActual;

    vector <int> auxiauxiAllowed;
    vector <int> auxiVisitedAllowed;
    vector <float> capAuxAllowed;
    float FitAuxAllowed;

    LOActual = auxiliar;
    bool flagLO = true;
    bool verbose = false;
    float FitAux, LOQ;


    //sol candidata inicial
    auxiauxi = auxiliar;
    capAux = CapRem;
    auxiVisited = visited;
    FitAux = Fit;
    LOQ = Fit;


    if(verbose){
        cout << "ANTES DE EMPEZAR" << endl;
        for(i = 0; i < auxiliar.size(); i++) if(auxiliar[i] == 1) cout << auxiliar[i] << " <--" << i << endl;
        for(i = 0; i < included.size(); i++) cout << included[i] << " " << endl;
        cout << endl;
    }


    for(cicles = 0; ((cicles < included.size()) && flagLO) ; cicles++) {

        //quito el objeto indi de la sol candidata inicial
        indi = included[cicles];
        auxiauxi[indi] = 0;
        auxiVisited[indi] = 1;
        FitAux = FitAux - Profits[indi];

        //devuelvo los recursos que estaba ocupando
        if(verbose) cout << "voy a sacar a indi:-->" << indi << " con Profit:" << Profits[indi] << " - FitAux sin indi:" << FitAux << endl;

        if(verbose) cout << "devuelvo recursos" << endl;
        for (i = 0; i < capAux.size(); i++) {
            capAux[i] += Weights[i][indi];
            if(verbose) cout << capAux[i] << " = " << Weights[i][indi] << " + " << CapRem[i] << endl;

        }

        //Veo cuales son los nuevos objetos allowed al sacar "indi"
        CheckAllowedNodes(capAux,auxiVisited);



        if(verbose){
            for(i = 0; i < allowed.size(); i++) cout << allowed[i] << " ";
            cout << endl;
        }
        if(verbose) cout << "size of allowed-->" << allowed.size() << endl;

        //Almaceno la sol candidata sin indi
        auxiauxiAllowed = auxiauxi;
        auxiVisitedAllowed = auxiVisited;
        capAuxAllowed = capAux;
        FitAuxAllowed = FitAux;

        //recorro los allowed, voy probando uno a uno.
        for(newallow = 0; (newallow < allowed.size()) && flagLO ; newallow++){

            //intento agregar indiall
            indiall = allowed[newallow];
            if(verbose) cout << "allowed#: "<< newallow <<  " intento agregar a --> "<< indiall << endl;

            if(indi != indiall){

                auxiauxiAllowed[indiall] = 1;
                FitAuxAllowed += Profits[indiall];
                for (i = 0; i < capAuxAllowed.size(); i++) {
                    capAuxAllowed[i] -= Weights[i][indiall];
                    if(verbose) cout << capAuxAllowed[i] << " = " << Weights[i][indiall] << " - " << capAux[i] << endl;
                }

                //check if it is better. Si hay un vecino mejor, se acaba.
                if(verbose) cout << "FitAux:" << FitAux <<"ProfObj:" << Profits[indiall] << " - LOQ:" << LOQ << " - FITAUXALLOWED:" << FitAuxAllowed << endl;
                if (LOQ < FitAuxAllowed) {
                    if(verbose) cout << "ES MEJOR" << endl;
                    if(verbose) getchar();
                    flagLO = false;
                }
                else{
                    //Si no es mejor, vuelvo a la sol candidata sin indi
                    auxiauxiAllowed = auxiauxi;
                    auxiVisitedAllowed = auxiVisited;
                    capAuxAllowed = capAux;
                    FitAuxAllowed = FitAux;
                }
            }
            else{
                //Es el mismo que saqué (indi)
            }

        }


        FitAux = Fit;
        auxiauxi = auxiliar;
        capAux = CapRem;
        auxiVisited = visited;

    }


    return flagLO;
}

*/

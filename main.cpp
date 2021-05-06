#include <iostream>
using namespace std;

#include "ClassTP1.hpp"
#include "Generic_station_parser.hpp"
#include "archive_etudiant/Grade.hpp"


int main(){

    //TP1 partie 1:
    cout<<"\n************************"<<endl;

    ClassTP1 a;
    a.afficher();
    a.read_stations("stations.csv");

    
    //obj grade;
    travel::Grade G(true);
    

}
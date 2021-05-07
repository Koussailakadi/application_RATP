#include <iostream>


#include "ClassTP1.hpp"
#include "Generic_station_parser.hpp"
#include "Generic_connection_parser.hpp"
#include "Grade.hpp"


int main(){

    //TP1 partie 1:
    std::cout<<"\n************************"<<endl;

    ClassTP1 a;
    a.afficher();
    a.read_stations("data/s.csv");

    
    //obj grade;
    travel::Grade G1(false);
    G1.stations(a);

    //lire les connections:
    travel::Grade G2(false);
    a.read_connections("data/c.csv");
    G2.connections(a);
    
}
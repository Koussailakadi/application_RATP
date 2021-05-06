#include <iostream>
#include <fstream>
#include <string>

#include "ClassTP1.hpp"
#include "Generic_station_parser.hpp"


//constructeur:
ClassTP1 :: ClassTP1(){cout<<"ClassTP1"<<endl;}
ClassTP1 :: ~ClassTP1(){cout<<"~ClassTP1"<<endl;}

//méthodes:
void ClassTP1 :: afficher() const {
    std::cout<<"affichage: "<<std::endl;
}


void ClassTP1 :: read_stations(const std::string& _filename) {
    fstream ip(_filename);

    if(!ip.is_open()) std::cout<<"Error: File Open"<<std::endl;

    std::string name, line_id, adress,line_name, direction;

    while (ip.good()){
        
        std::getline(ip,name,',');
        std::getline(ip,line_id,',');
        std::getline(ip,adress,',');
        std::getline(ip,line_name,',');
        std::getline(ip,direction,'\n');


	    travel::Station station;
        station.name=name;
        station.line_id =line_id;
		station.address = adress;
		station.line_name = line_name;
		station.direction = direction;

        std::cout<<station<<std::endl;
		//stations_hashmap[stoll(line_id)] = station;
	
        //std::cout<<"Name   "<<"line_id   "<<"adress   "<<"line_name"<<std::endl;
        //std::cout<<name;
        //std::cout<<line_id;
        //std::cout<<adress;
        //std::cout<<line_name;
        //std::cout<<direction<<std::endl;

    }
    
    //fermer le fichier:
    ip.close();

}


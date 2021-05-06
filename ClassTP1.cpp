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
    
    // ouvrir le fichier
    if(!ip.is_open()) std::cout<<"Error: File Open"<<std::endl;

    //déclarer les variable qui vont contenir les données du CSV
    std::string name, line_id, adress,line_name, id;

    //se débarassé de la premiere ligne:
    std::string ligne = "";
	std::getline(ip, ligne);

    while (ip.good()){
        
        std::getline(ip,name,',');
        std::getline(ip,id,',');
        std::getline(ip,line_id,',');
        std::getline(ip,adress,',');
        std::getline(ip,line_name,'\n');
      

        if (id.compare("") == 0) {
			break;
		}

	    travel::Station station;
        station.name=name;
        station.line_id =line_id;
		station.address = adress;
		station.line_name = line_name;
	

        std::cout<<station<<std::endl;

		this->stations_hashmap[stoll(id)] = station;

    }
    
    //fermer le fichier:
    ip.close();

}


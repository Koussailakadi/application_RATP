#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "ClassTP1.hpp"
#include "Generic_station_parser.hpp"
#include "Generic_connection_parser.hpp"
#include "Generic_mapper.hpp"

using namespace std;

//constructeur:
ClassTP1 :: ClassTP1(){cout<<"ClassTP1"<<endl;}
ClassTP1 :: ~ClassTP1(){cout<<"~ClassTP1"<<endl;}

//méthodes:
void ClassTP1 :: afficher() const {
    std::cout<<"affichage: "<<std::endl;
}


// read station:
void ClassTP1 :: read_stations(const std::string& _filename) {
    fstream ip(_filename);
    
    // ouvrir le fichier
    if(!ip.is_open()) throw std::runtime_error("Error: Can not File Open");

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
      

	    travel::Station station;
        station.name=name;
        station.line_id =line_id;
		station.address = adress;
		station.line_name = line_name;
	

        std::cout<<station<<std::endl;
		this->stations_hashmap[stoll(id)] = station;

        //end of file 
        if (ip.eof()) {
			break;
		}

    }

    
    //fermer le fichier:
    ip.close();

}


//read the connections:
void ClassTP1::read_connections(const std::string& _filename){
    fstream ip(_filename);

    //ouvrir le fichier:
    if(!ip.is_open()) throw std::runtime_error("Error: Can not File Open");

    //déclarer les vriables qui vont contenir les données du fichier:
    std::string from_stop_id, to_stop_id, transfer_time;

    //convertir:
    //uint64_t from_stop_id_value,to_stop_id_value, transfer_time_value; 


    //se débarasser de la premiere ligne:
    std::string line=" ";
    std::getline(ip,line); 

    while(ip.good()){

        std::getline(ip,from_stop_id,',');
        std::getline(ip,to_stop_id,',');
        std::getline(ip,transfer_time,'\n');

        
        //convertir en uint64:
        //from_stop_id_value=std::stoll(from_stop_id);
        //to_stop_id_value=std::stoll(to_stop_id);
        //transfer_time_value=std::stoll(transfer_time);

        //vérifier la fin du fichier avant d'affecter:
        if (ip.eof()) {
			break;
		}
       
        this->connections_hashmap[stoll(from_stop_id)][stoll(to_stop_id)]=stoll(transfer_time);
        std::cout<<from_stop_id<<" , "<<to_stop_id<<" , "<<transfer_time<<std::endl;

       
    }
    //close the file:
    ip.close();
}



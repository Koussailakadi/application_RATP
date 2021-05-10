#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "RATP.hpp"
#include "Generic_station_parser.hpp"
#include "Generic_connection_parser.hpp"
//#include "Generic_mapper.hpp"

using namespace std;

//constructeur:
RATP :: RATP(){cout<<"RATP"<<endl;}
RATP :: ~RATP(){cout<<"~RATP"<<endl;}

//méthodes:
void RATP :: afficher() const {
    std::cout<<"affichage: "<<std::endl;
}


// read station:
void RATP :: read_stations(const std::string& _filename) {
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
void RATP::read_connections(const std::string& _filename){
    fstream ip(_filename);

    //ouvrir le fichier:
    if(!ip.is_open()) throw std::runtime_error("Error: Can not File Open");

    //déclarer les vriables qui vont contenir les données du fichier:
    std::string from_stop_id, to_stop_id, transfer_time;

    //convertir:
    uint64_t from_stop_id_value,to_stop_id_value, transfer_time_value; 


    //se débarasser de la premiere ligne:
    std::string line=" ";
    std::getline(ip,line); 

    while(ip.good()){

        std::getline(ip,from_stop_id,',');
        std::getline(ip,to_stop_id,',');
        std::getline(ip,transfer_time,'\n');

        //vérifier la fin du fichier avant d'affecter:
        if (ip.eof()) {
			break;
		}

        //convertir en uint64:
        from_stop_id_value=std::stoull(from_stop_id);
        to_stop_id_value=std::stoull(to_stop_id);
        transfer_time_value=std::stoull(transfer_time);

        
        this->connections_hashmap[from_stop_id_value][to_stop_id_value]=transfer_time_value;
        std::cout<<from_stop_id<<" , "<<to_stop_id<<" , "<<transfer_time<<std::endl;

       
    }
    //close the file:
    ip.close();
}



//----------------------------------------------------------------------
std::vector<std::pair<uint64_t,uint64_t> > RATP::compute_travel(uint64_t _start, uint64_t _end){
	// retourner le court chemin, avec l'algorithme de dijkstra
	std::vector<std::pair < uint64_t, uint64_t> >  Vect_travel;

    std::unordered_map<uint64_t, travel::Station> stations_hashmap;
    stations_hashmap=get_stations_hashmap();
    std::cout<<stations_hashmap[2191]<<std::endl;

    std::unordered_map<uint64_t,std::unordered_map<uint64_t,uint64_t> > connections_hashmap;
    connections_hashmap=get_connections_hashmap();

    auto p = std::make_pair(_start,_end);
    Vect_travel.push_back(p);
    return Vect_travel;
}


std::vector<std::pair<uint64_t,uint64_t> > RATP::compute_and_display_travel(uint64_t _start, uint64_t _end){
    // retourner [id1, id2]= time

	std::vector<std::pair < uint64_t, uint64_t> >  Vect_travel;
    auto p = std::make_pair(_start,_end);
    Vect_travel.push_back(p);

    return Vect_travel;
}

// recherche par string:
std::vector<std::pair<uint64_t, uint64_t> > RATP::compute_travel(const std::string& _start, const std::string& _end){
    std::vector<std::pair < uint64_t, uint64_t> >  Vect_travel;
    std::cout<<_start<<_end<<std::endl;
    auto p = std::make_pair(100,2000);
    Vect_travel.push_back(p);

    return Vect_travel;

   }

std::vector<std::pair<uint64_t, uint64_t> > RATP::compute_and_display_travel(const std::string& _start=" ", const std::string& _end=" "){
    std::vector<std::pair < uint64_t, uint64_t> >  Vect_travel;
    std::cout<<_start<<_end<<std::endl;
    auto p = std::make_pair(100,2000);
    Vect_travel.push_back(p);

    return Vect_travel;

}

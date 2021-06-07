#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "RATP.hpp"
//#include "Generic_station_parser.hpp"
//#include "Generic_connection_parser.hpp"
//#include "Generic_mapper.hpp"

using namespace std;

//constructeur:
RATP :: RATP(){cout<<"RATP"<<endl;}
RATP :: ~RATP(){cout<<"~RATP"<<endl;}



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
	

        //std::cout<<station<<std::endl;
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
        //std::cout<<from_stop_id<<" , "<<to_stop_id<<" , "<<transfer_time<<std::endl;

       
    }
    //close the file:
    ip.close();
}

//----------------------------------------------------------------------
std::vector<std::pair<uint64_t,uint64_t> > RATP::compute_travel(uint64_t _start, uint64_t _end){
	// Algorithme de dijkstra
	std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> list_1o;
	std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> list_2f;

	list_1o[_start] = std::make_pair(0, 0);
	while (!list_1o.empty()) {

		uint64_t meilleurCout = UINT64_MAX;
		uint64_t destination = 0;

		if (list_1o.empty()) {
			break;
		}


		for (auto it = list_1o.begin(); it != list_1o.end(); it++) {
			std::pair<uint64_t, uint64_t> pair = it->second;

			if (pair.second < meilleurCout && list_2f.find(it->first) == list_2f.end()) {
				meilleurCout = pair.second;
				destination = it->first;
			}
		}

		if (this->stations_hashmap.at(destination).name.compare(this->stations_hashmap.at(_end).name) == 0) {
			_end = stoll(this->stations_hashmap.at(destination).line_id);
			std::pair<uint64_t, uint64_t> pair = list_1o[destination];
			list_1o.erase(destination);
			list_2f[destination] = pair;
			break;
		}
		//si on fait un choix
		if (destination != -1) {
			std::pair<uint64_t, uint64_t> pair =list_1o[destination];
			list_1o.erase(destination);
			list_2f[destination] = pair;

			std::unordered_map<uint64_t, uint64_t> listeFils = connections_hashmap[destination];

			for (auto it = listeFils.begin(); it != listeFils.end(); it++) {
		
				if (list_2f.find(it->first) == list_2f.end() && list_1o.find(it->first) == list_1o.end()) {
					std::pair<uint64_t, uint64_t> fils = std::make_pair(destination, it->second + list_2f.at(destination).second);
					list_1o[it->first] = fils;
				}

				if (list_2f.find(it->first) == list_2f.end() && list_1o.find(it->first) != list_1o.end() && list_1o.at(it->first).second > it->second + list_2f.at(destination).second) {
					std::pair<uint64_t, uint64_t> fils = std::make_pair(destination, it->second + list_2f.at(destination).second);
					list_1o.at(it->first) = fils;
				}
			}
		}
	}
	std::vector<std::pair<uint64_t, uint64_t>> chemin;

	if (list_1o.empty() && list_2f.find(_end) == list_2f.end()) {
		std::cout << "Impossible de trouver un chemin" << std::endl;
	}
	else {

		chemin.push_back(std::make_pair(_end, list_2f.at(_end).second));

		std::pair<uint64_t, uint64_t> pair = std::make_pair(list_2f.at(_end).first, list_2f.at(list_2f.at(_end).first).second);
		chemin.push_back(pair);
		while (pair.first != _start) {
			pair = std::make_pair(list_2f.at(pair.first).first, list_2f.at(list_2f.at(pair.first).first).second);
			chemin.push_back(pair);
		}
	}

	return chemin;
}


std::vector<std::pair<uint64_t,uint64_t> > RATP::compute_and_display_travel(uint64_t _start, uint64_t _end){
    // retourner [id1, id2]= time

	std::vector<std::pair < uint64_t, uint64_t> >  Vect_travel;
    auto p = std::make_pair(_start,_end);
    Vect_travel.push_back(p);

    return Vect_travel;
}




// recherche par string:------------------------------------------------
std::vector<std::pair<uint64_t, uint64_t> > RATP::compute_travel(const std::string& _start, const std::string& _end){
 
	uint64_t start;
	uint64_t end;

    //get name ID from name: 
    for (auto it = this->stations_hashmap.begin(); it != this->stations_hashmap.end(); it++) {
		if (it->second.name.compare(_start) == 0) {
			start=it->first;
		}
        if (it->second.name.compare(_end) == 0) {
			end=it->first;
		}
	}

	//si on � pas trouver l'une des station on l�ve une exception
	if (start == 0 || end == 0) {
		throw("Station inconnu");
	}
	else {
		return compute_travel(start, end);
	}

   }

std::vector<std::pair<uint64_t, uint64_t> > RATP::compute_and_display_travel(const std::string& _start=" ", const std::string& _end=" "){

    std::vector<std::pair<uint64_t, uint64_t>> chemin = compute_travel(_start, _end);
	
	std::cout << "Voici les indications a suivre " << std::endl;

	for (int i = chemin.size() - 1; i > 0; i--) {
		travel::Station stationDep = this->stations_hashmap.at(chemin[i].first);
		travel::Station stationArr = this->stations_hashmap.at(chemin[i - 1].first);

		//Si les 2 stations ont le m�me nom c'est une transition qu'on doit afficher (ex Gare de lyon ligne 14 -> Gare de lyon ligne 1)
		if (stationDep.name.compare(stationArr.name) == 0) {
			std::cout << "Station départ: " << stationDep.name <<" vous devez prendre la ligne " << stationArr.line_name << " Duree du transfert : " << ((chemin[i - 1].second - chemin[i].second) / 60) << " min" << std::endl;
		}
		else {
			std::cout << "Prendre la ligne " << stationDep.line_name << " de la station " << stationDep.name << " a la station " << stationArr.name << " Duree du trajet : " << ((chemin[i - 1].second - chemin[i].second) / 60) << " min" << std::endl;

		}
	}
	std::cout << "fin de trajet----------:\nDurée du trajet:" << ((chemin[0].second + chemin[chemin.size() - 1].second) / 60) << " min." << std::endl;
	return chemin;

}

//-------------------
void RATP::AfficherStation(){
	for (auto it = this->stations_hashmap.begin(); it != this->stations_hashmap.end(); it++) {
		std::cout << it->second << std::endl;
	}
}


uint64_t RATP::getId(const std::string& name) {
	for (auto it = this->stations_hashmap.begin(); it != this->stations_hashmap.end(); it++) {
		if (it->second.name.compare(name) == 0) {
			return it->first;
		}
	}
	return 0;
}

bool RATP::isStation(const std::string& station){
	return this->stations_hashmap.find(getId(station)) != this->stations_hashmap.end();
}
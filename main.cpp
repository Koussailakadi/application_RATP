#include <iostream>


#include "RATP.hpp"
//#include "Generic_station_parser.hpp"
#include "Generic_connection_parser.hpp"
#include "Grade.hpp"

//déclaration:
std::string trim(const std::string& s);

int main(){

    //Projet: 


	std::cout<<"\n************************"<<std::endl;
    RATP application;
    /*
    Partie read stations: avec validation de grade.o
     */ 
    application.read_stations("data/s.csv");
    
    //obj grade;
    travel::Grade G1(false);
    //G1.stations(application);
	

    /*
    Partie read connections: avec validation de grade.o
     */ 
    //lire les connections:
    application.read_connections("data/c.csv");

	// Grade 1 et Grade 2: 
    G1.connections(application);


    /* Partie test algorithme Dijkstra*/
    //interface : 
    std::cout << "\n************************"<<"\nBienvenue sur RATP carte métro parésien" << std::endl;
	do {
		std::string station1;
		std::string station2;
		std::cout << "Vous pouvez: " << std::endl;
		std::cout << "	Départ: " << std::endl;
		std::cout << "	Taper 'exit' pour quitter" << std::endl;
		std::cout << "	Taper 'show' pour afficher les stations" << std::endl;
		std::cout << std::endl << "Saisie: ";

		std::cin >> std::ws; 
		std::getline(std::cin, station1);

		if (trim(station1).compare("show") == 0) {
			application.AfficherStation();
			continue;
		}

		else if (trim(station1).compare("exit") == 0) {
			break;
		}


		if (!application.isStation(trim(station1))) {
			std::cerr << "Station inconnue" << std::endl;
			continue;
		}


		std::cout << "le nom de votre station d'arriver" << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, station2);

		if (!application.isStation(trim(station2))) {
			std::cerr << "Station inconnue" << std::endl;
			continue;
		}

		if (station1.compare(station2) == 0) {
			std::cout << "Vous etes deja a destination" << std::endl;
			continue;
		}
		application.compute_and_display_travel(trim(station1), trim(station2));
		std::cout << std::endl << std::endl;
	} while (true);

	system("pause");
	return 0;
}



std::string trim(const std::string& s)
{
	auto start = s.begin();
	while (start != s.end() && isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (std::distance(start, end) > 0 && *end >= 1 && *end < 255 && isspace(*end));

	return std::string(start, end + 1);

}
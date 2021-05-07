#ifndef RATP_H
#define RATP_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

//#include "Generic_station_parser.hpp" 
#include "Generic_connection_parser.hpp"



//la classe RATP hérite des classes Generic_station_parser, et Generic_conection

class RATP : public travel::Generic_connection_parser {
    
    public:
        RATP ();
        ~RATP();
        void afficher() const;
        void read_stations(const std::string& _filename) override;
        void read_connections(const std::string& _filename) override;
};

#endif // RATP_H
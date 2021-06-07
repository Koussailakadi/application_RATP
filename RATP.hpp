#ifndef RATP_H
#define RATP_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

//using namespace std;

#include "Generic_station_parser.hpp" 
#include "Generic_connection_parser.hpp"
#include "Generic_mapper.hpp"


//la classe RATP hérite des classes Generic_station_parser, et Generic_conection

class RATP : public travel::Generic_mapper{
    
    public:
        RATP ();
        ~RATP();
        void read_stations(const std::string& _filename) override;
        void read_connections(const std::string& _filename) override;

        
        //-------------------------
        std::vector<std::pair<uint64_t, uint64_t> > compute_travel(uint64_t _start, uint64_t _end) override;
        std::vector<std::pair<uint64_t, uint64_t> > compute_and_display_travel(uint64_t _start=0, uint64_t _end=0) override;

        //Meme methode mais qui travaille avec le nom des station plutot que leurs ID
        std::vector<std::pair<uint64_t, uint64_t> > compute_travel(const std::string&, const std::string&) override;
        std::vector<std::pair<uint64_t, uint64_t> > compute_and_display_travel(const std::string&, const std::string&) override;

        // additionnal functions:
        void AfficherStation();
        bool isStation(const std::string& station);
        uint64_t getId(const std::string& name);
    
};

#endif // RATP_H

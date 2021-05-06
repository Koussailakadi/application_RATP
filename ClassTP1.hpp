    #ifndef CLASSTP1_H
    #define CLASSTP1_H

    #include <string>
    #include <iostream>
    #include <unordered_map>
    #include <fstream>

    using namespace std;
  
    #include "Generic_station_parser.hpp" 
    #include "Generic_connection_parser.hpp"
    

    //la classe TP1 hérite des classes Generic_station_parser, et Generic_conection

    class ClassTP1 : public travel::Generic_connection_parser {
       
        public:
            ClassTP1 ();
            ~ClassTP1();
            void afficher() const;
            void read_stations(const std::string& _filename) override;
            void read_connections(const std::string& _filename) override;
    };

    #endif // CLASSTP1_H
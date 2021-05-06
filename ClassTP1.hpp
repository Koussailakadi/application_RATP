    #ifndef CLASSTP1_H
    #define CLASSTP1_H

    #include <string>
    #include <iostream>
    #include <unordered_map>
    #include <fstream>

    using namespace std;
  
    //inclure la class mère (dans un dossier)
    #include "Generic_station_parser.hpp" 

    class ClassTP1 : public travel::Generic_station_parser {
       
        public:
            ClassTP1 ();
            ~ClassTP1();
            void afficher() const;
            void read_stations(const std::string& _filename) override;
    };

    #endif // CLASSTP1_H
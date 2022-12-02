// MapClass.h defines a map / vector based class to store AirBnB listing informaiton

#include <map>
#include <vector>
#include <fstream>

#include "ListingData.h"

class mapClass {
    private:
        std::map<std::string, std::vector<int>>; // int refers to line number in source file
        std::string path;
    public:
        mapClass(std::string path);
        getDataFromID(int ID);
}

mapClass::mapClass(std::string path){
    this->path = path;

    std::ifstream input_file;
    input_file.open(path, std::ios::in);

    std::string line;
    std::getline(input_file, line); // First Line is headers

    while (!input_file.eof()){
        std::getline(input_file, line);
        // TODO Parse Line, depends on chosen data set
    }
}
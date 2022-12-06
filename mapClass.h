// MapClass.h defines a map / vector based class to store AirBnB informaiton

#include <map>
#include <vector>
#include <fstream>
#include <string>

#include "ListingData.h"

class MapClass {
    private:
        // string is city name
        // int refers to position in source file
        std::map<std::string, std::vector<int>> data; 
        std::string path;
    public:
        int size;

        MapClass();  //  Empty Constructor
        MapClass(std::string path);
        int getNumberOfListings() const;
        ListingData getDataFromPos(int pos) const;
        ListingDataBundle getAllListingsInCity(std::string city) const;
        std::vector<std::string> getAllCities() const;
};

//  Some strings contain newlines so we need to check for that
bool isStringFinished(std::string test_string) {
    bool result = false;
    for (int i = 0; i < test_string.size(); i++) {
        result = (test_string[i] == '"') ? !result : result;
    }

    return !result;
}

std::string CustomGetLine(std::fstream &file) {
    std::string line;
    std::getline(file, line, '\n');

    while (!isStringFinished(line)) {
        std::string line2;
        std::getline(file, line2, '\n');
        line += line2;
    }

    return line;
}

MapClass::MapClass() {
    //  Do Nothing
}

MapClass::MapClass(std::string path) {
    this->path = path;
    this->size = 0;

    std::fstream input_file;
    input_file.open(path, std::ios::in);

    std::string line;
    std::getline(input_file, line, '\n'); // First Line is headers

    int filePos;
    int commaPos;
    std::string city;

    while (!input_file.eof()) {
        //std::cout << filePos << std::endl;
        filePos = input_file.tellg(); //  Get current pos from file
        line = CustomGetLine(input_file);

        // Parse Line, depends on chosen data set
        commaPos = line.find_last_of(',');
        city = line.substr(commaPos + 1);

        this->data[city].push_back(filePos);
        size++;
    }

    input_file.close();
}

int MapClass::getNumberOfListings() const {
    return this->size;
}

ListingData MapClass::getDataFromPos(int pos) const {
    ListingData result;
    std::fstream input_file;
    input_file.open(path, std::ios::in);

    input_file.seekg(pos);

    std::string line = CustomGetLine(input_file);

    //  City
    int commaPos = line.find_last_of(',');
    result.city = line.substr(commaPos + 1);

    //  Available Days Per Year
    int prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    std::string value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.availableDaysPerYear = stoi(value);
    } catch (const std::invalid_argument& e) {
        result.availableDaysPerYear = 0;
    }

    //  Host Total Listings Count
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.hostTotalListingsCount = stoi(value);
    } catch (const std::invalid_argument& e) {
        result.hostTotalListingsCount = 0;
    }

    //  Reiews Per Month
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.reviewsPerMonth = stod(value);
    } catch (const std::invalid_argument& e) {
        result.reviewsPerMonth = 0;
    }

    //  Last Review Date DD/MM/YY
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    result.lastReviewDate = value;

    //  Number of Reviews
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.numReviews = stoi(value);
    }  catch (const std::invalid_argument& e) {
        result.numReviews = 0;
    }

    //  Minimum Number of Nights (Does Some Slight Data Cleanup)
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.minNights = stoi(value);
    } catch (const std::invalid_argument& e) {
        result.minNights = 0;
    }
    result.minNights = (result.minNights == 0) ? 365 : result.minNights;

    //  Price Per Night
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.price = stod(value);
    } catch (const std::invalid_argument& e) {
        result.price = 0;
    }

    //  Room Type
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    result.roomType = value;

    //  Longitude
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.longitude = stod(value);
    } catch (const std::invalid_argument& e) {
        result.longitude = 0;
    }

    //  Latitude
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.latitude = stod(value);
    } catch (const std::invalid_argument& e) {
        result.latitude = 0;
    }

    //  Neighbourhood
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    result.neighbourhood = value;

    //  Neighbourhood Group
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    result.neighbourhoodGroup = value;

    //  Host Name
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    result.hostName = value;

    //  Host ID
    prevCommaPos = commaPos;
    commaPos = line.find_last_of(',', commaPos - 1);
    value = line.substr(commaPos + 1, prevCommaPos - commaPos - 1);
    try {
        result.hostID = stoi(value);
    } catch (const std::invalid_argument& e) {
        result.hostID = 0;
    }

    //  Listing ID (Note logic is different)
    prevCommaPos = commaPos;
    commaPos = line.find_first_of(',');
    try {
        result.id = stoi(line.substr(0, commaPos));
    } catch (const std::invalid_argument& e) {
        result.id = 0;
    }

    //  Description (Logic is weird, cause it could include commas)
    result.description = line.substr(commaPos, prevCommaPos - commaPos - 1);

    return result;
}

ListingDataBundle MapClass::getAllListingsInCity(std::string city) const {
    std::vector<ListingData> myData;
    for (int i = 0; i < data.at(city).size(); i++) {
        myData.push_back(getDataFromPos(data.at(city)[i]));
    }

    return ListingDataBundle(myData);
}

std::vector<std::string> MapClass::getAllCities() const {
    std::vector<std::string> result;
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        result.push_back(iter->first);
    }

    return result;
}
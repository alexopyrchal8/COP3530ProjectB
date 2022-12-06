// Hey guys, so my plan is to have this file be a master file which will call the map class and graph classes itself depending on which is prefered.
// My idea is the UI code can hopefully call/trigger this class and it's methods itself (not sure how that works)
#include <iostream>
#include <iomanip>
#include <math.h>

#include "mapClass.h"

int main(int argc, char *argv[]) {
    bool useMap = true;
    bool debugMode = false;

    // for (int i = 0; i < argc; i++) {
    //     std::cout << argv[i] << std::endl;
    // }

    switch (argc) {
        case 3:
            if (std::string(argv[2]).find("debug") != std::string::npos){
                debugMode = true;
            }
        case 2:
            if (std::string(argv[1]).find("graph") != std::string::npos) {
                useMap = false;
            }
        default:
            break;
    }

    MapClass myMap;
    if (useMap) {
        myMap = MapClass("AB_US_2020.csv");
    } else {  //  Use Graph
        //  TODO by Alexander
    }

    if (debugMode) {
        int loaded = (useMap) ? myMap.getNumberOfListings() : 0;
        std::cout  //  Menu continued on next line
        << "                    Main Menu                  " << std::endl
        << "-----------------------------------------------" << std::endl
        << "Using: " << ((useMap) ? "Map" : "Graph")         << std::endl
        << "Loaded: " << loaded << " listings"               << std::endl
        << "-----------------------------------------------" << std::endl
        << "1. Print List of Cities"                         << std::endl
        << "Or input city name to advance"                   << std::endl;

        bool advance = false;
        std::string input;

        while (!advance) {
            std::getline(std::cin, input);
            advance = (input != "1");

            if (!advance && useMap) {
                std::vector<std::string> cities = myMap.getAllCities();
                for (int i = 0; i < cities.size(); i++){
                    std::cout << cities[i] << std::endl;
                }
                std::cout << "Input city name to advance" << std::endl;
            }
        }

        ListingDataBundle listings;

        if (useMap) {
            listings = myMap.getAllListingsInCity(input);
        }

        advance = false;

        //  Setup Filter Variables
        int maxPrice     = 1000000;
        int stayLength   = 365;
        int minReviews   = 0;
        int minAvailable = 0;
        int hostListings = 0;
        double minMonthlyReviews = 0.0;
        std::string roomType = "";
        std::string hostName = "";
        bool updateFilter = false;
        input = "R";

        while (!advance) {
            
            updateFilter = false;

            if (input == "R"){
                std::cout  //  Menu continued on next line
                << "                   City Menu                   " << std::endl
                << "-----------------------------------------------" << std::endl
                << "Loaded: " << listings.getNumberOfListings()      << std::endl
                << "-----------------------------------------------" << std::endl
                << " 1. Display Listings"                            << std::endl
                << " 2. Get List of Room Types"                      << std::endl
                << " 3. Get List of Neighbourhoods"                  << std::endl
                << " 4. Get List of Neighbourhood Groups"            << std::endl
                << "  | (Note filters stack together)"               << std::endl
                << " 5. Filter by Price (ex: 5 XX.XX)"               << std::endl
                << " 6. Filter by Minimum Stay (ex: 6 XXX)"          << std::endl
                << " 7. Filter by Total Reviews (ex: 7 XXX)"         << std::endl
                << " 8. Filter by Availability (ex: 8 XXX)"          << std::endl
                << " 9. Filter by Host Listings (ex: 9 XXX)"         << std::endl
                << "10. Filter by Monthly Reviews (ex: 10 XX.XX)"    << std::endl
                << "11. Filter by Room Type (ex: 11 ROOM)"           << std::endl
                << "12. Filter by Host Name (ex: 12 HOST)"           << std::endl
                << "13. Sort by Price ('13D' is descend)"            << std::endl
                << "14. Sort by Total Reviews ('14D' is descend)"    << std::endl
                << "15. Sort by Monthly Reviews ('15D' is descend)"  << std::endl
                << "16. Sort by Host Listings ('16D' is descend)"    << std::endl
                << "17. Exit Application"                            << std::endl;

            } else if (input == "1") {  //  Display Listings
                std::vector<ListingData> list = listings.getVector();
                
                int lenRoom  = 0;
                int lenName  = 0;
                int lenPrice = 0;
                int lenStay  = 0;
                int lenTRev  = 0;
                int lenMRev  = 0;
                int lenL     = 0;

                for (auto iter = list.begin(); iter != list.end(); iter++) {
                    //  Find Longest Room Type
                    lenRoom = (iter->roomType.size() > lenRoom) 
                        ? iter->roomType.size() : lenRoom;
                    
                    //  Find Longest Name
                    lenName = (iter->hostName.size() > lenName) 
                        ? iter->hostName.size() : lenName;

                    //  Find Longest Price
                    lenPrice = ((int)log10(iter->price) + 1 > lenPrice) 
                        ? (int)log10(iter->price) + 1 : lenPrice;

                    //  Find Longest Stay
                    lenStay = ((int)log10(iter->minNights) + 1 > lenStay) 
                        ? (int)log10(iter->minNights) + 1 : lenStay;

                    //  Find Longest Total Reviews
                    lenTRev = ((int)log10(iter->numReviews) + 1 > lenTRev) 
                        ? (int)log10(iter->numReviews) + 1 : lenTRev;

                    //  Find Longest Monthly Reviews
                    lenMRev = ((int)log10(iter->reviewsPerMonth) + 1 > lenMRev)
                        ? (int)log10(iter->reviewsPerMonth) + 1 : lenMRev;

                    //  Find Longest Host Listings
                    lenL = ((int)log10(iter->hostTotalListingsCount)+ 1 > lenL)
                        ? (int)log10(iter->hostTotalListingsCount) + 1 : lenL;
                    
                }

                for (auto iter = list.begin(); iter != list.end(); iter++) {
                    std::cout  //  Formatting Below
                    << std::setw(lenRoom) << std::left << iter->roomType 
                    << " by " << std::setw(lenName) << iter->hostName
                    << " for $" << std::setw(lenPrice + 3) << std::right
                    << std::setprecision(2) << std::fixed << iter->price
                    << "  Min Stay: " << std::setw(lenStay) << iter->minNights
                    << "  Reviews: " << std::setw(lenTRev) << iter->numReviews
                    << "  Monthly Reviews: " << std::setw(lenMRev + 3) 
                    << std::setprecision(2) << iter->reviewsPerMonth
                    << "  Hosts other listings: " << std::setw(lenL)
                    << iter->hostTotalListingsCount
                    << std::endl;
                }

            } else if (input == "2") {  //  List Room Types
                std::vector<std::string> list = listings.getRoomTypes();
                for (auto iter = list.begin(); iter != list.end(); iter++) {
                    std::cout << *iter << std::endl;
                }

            } else if (input == "3") {  //  List neighbourhoods
                std::vector<std::string> list = listings.getNeighbourhoods();
                for (auto iter = list.begin(); iter != list.end(); iter++) {
                    std::cout << *iter << std::endl;
                }

            }  else if (input == "4") {  //  List neighbourhood Groups
                std::vector<std::string> list = listings.getNeighbourGroups();
                for (auto iter = list.begin(); iter != list.end(); iter++) {
                    std::cout << *iter << std::endl;
                }

            } else if (input[0] == '5') {  //  Update Price Filter
                maxPrice = stod(input.substr(2));
                updateFilter = true;
            } else if (input[0] == '6') {  //  Update Min Stay Filter
                stayLength = stoi(input.substr(2));
                updateFilter = true;
            } else if (input[0] == '7') {  //  Update Total Reviews Filter
                minReviews = stoi(input.substr(2));
                updateFilter = true;
            } else if (input[0] == '8') {  //  Update Availability Filter
                minAvailable = stoi(input.substr(2));
                updateFilter = true;
            } else if (input[0] == '9') {  //  Update Total Reviews Filter
                hostListings = stoi(input.substr(2));
                updateFilter = true;
            } else if (input == "13") {  //  Sort by Price ASC
                listings.sortByPrice(false);
            } else if (input == "13D") {  //  Sort by Price DSC
                listings.sortByPrice(true);
            } else if (input == "14") {  //  Sort by Tot Reviews ASC
                listings.sortByTotalReviews(false);
            } else if (input == "14D") {  //  Sort by Tot Reviews DSC
                listings.sortByTotalReviews(true);
            } else if (input == "15") {  //  Sort by Month Reviews ASC
                listings.sortByMonthlyReviews(false);
            } else if (input == "15D") {  //  Sort by Month Reviews DSC
                listings.sortByMonthlyReviews(true);
            } else if (input == "16") {  //  Sort by Host Listing ASC
                listings.sortByHostListings(false);
            } else if (input == "16D") {  //  Sort by Host Listings DSC
                listings.sortByHostListings(true);
            } else if (input[0] == '1') {  
                if (input[1] == '0'){  //  Update Monthly Reviews Filter
                    minMonthlyReviews = stod(input.substr(3));
                    updateFilter = true;
                } else if (input[1] == '1') {  //  Update Room Type Filter
                    roomType = input.substr(3);
                    updateFilter = true;
                } else if (input[1] == '2') {  //  Update Host Name Filter
                    hostName = input.substr(3);
                    updateFilter = true;
                }
            }
            
            std::cout << std::endl << "R. Refresh Menu" << std::endl;

            if (updateFilter == true) {
                listings.filter(
                    maxPrice,
                    stayLength,
                    minReviews,
                    minAvailable,
                    hostListings,
                    minMonthlyReviews,
                    roomType,
                    hostName
                );
            }

            std::getline(std::cin, input);

            advance = (input == "17");

            
        }
    }

    return 0;
}
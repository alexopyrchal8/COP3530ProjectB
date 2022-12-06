#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <map>
#include <iostream>
#include <set>

using namespace std;

struct AirBnB
{
    string ID, name, hostID, hostName, neighborhoodGroup, neighborhood, latitude, longitude, roomType, lastReview, reviewPerMonth, city, price, minNights, numReviews, calcListCount, availability;
    
    AirBnB();
    AirBnB(string ID, string name, string hostID, string hostName, string neighborhoodGroup, string neighborhood, string latitude, string longitude, string roomType, string lastReview, string reviewPerMonth, string city, string price, string minNights, string numReviews, string calcListCount, string availability);
};

AirBnB::AirBnB()
{
    ID = "";
    name = "";
    hostID = "";
    hostName = "";
    neighborhoodGroup = "";
    neighborhood = "";
    latitude =  "";
    longitude = "";
    roomType = "";
    lastReview = "";
    reviewPerMonth = "";
    city = "";
    price = "";
    minNights = "";
    numReviews = "";
    calcListCount = "";
    availability = "";
}

AirBnB::AirBnB(string ID, string name, string hostID, string hostName, string neighborhoodGroup, string neighborhood, string latitude, string longitude, string roomType, string lastReview, string reviewPerMonth, string city, string price, string minNights, string numReviews, string calcListCount, string availability)
{
    this->ID = ID;
    this->name = name;
    this->hostID = hostID;
    this->hostName = hostName;
    this->neighborhoodGroup = neighborhoodGroup;
    this->neighborhood = neighborhood;
    this->latitude = latitude;
    this->longitude = longitude;
    this->lastReview = lastReview;
    this->reviewPerMonth = reviewPerMonth;
    this->city = city;
    this->price = price;
    this->minNights = minNights;
    this->numReviews = numReviews;
    this->calcListCount = calcListCount;
    this->availability = availability;
}

vector<AirBnB> dataLoader()
{
    ifstream file("AB_US_2021.csv");
    vector<AirBnB> listingObj;
    string line;


    if (file.is_open())
    {
        string line;

        getline(file, line);

        for (int i = 0; i < 100; i++)
        {
            string IDv;
            string namev;
            string hostIDv;
            string hostNamev;
            string neighborhoodGroupv; 
            string neighborhoodv; 
            string latitudev;
            string longitudev; 
            string roomTypev;
            string lastReviewv;
            string reviewPerMonthv; 
            string cityv;
            string pricev;
            string minNightsv;
            string numReviewsv;
            string calcListCountv; 
            string availabilityv;

            istringstream header(line);

            getline(header, IDv, ',');
            getline(header, namev, ',');
            getline(header, hostIDv, ',');
            getline(header, hostNamev, ',');
            getline(header, neighborhoodGroupv, ',');
            getline(header, neighborhoodv, ',');
            getline(header, latitudev, ',');
            getline(header, longitudev, ',');
            getline(header, roomTypev, ',');
            getline(header, pricev, ',');
            getline(header, minNightsv, ',');
            getline(header, numReviewsv, ',');
            getline(header, lastReviewv, ',');
            getline(header, reviewPerMonthv, ',');
            getline(header, calcListCountv, ',');
            getline(header, availabilityv, ',');
            getline(header, cityv, ',');

            AirBnB listing(IDv, namev, hostIDv, hostNamev, neighborhoodGroupv, neighborhoodv, latitudev, longitudev, roomTypev, lastReviewv, reviewPerMonthv, cityv, pricev, minNightsv, numReviewsv, calcListCountv, availabilityv);

            listingObj.push_back(listing);
        }
    }

    file.close();

    return listingObj;    
}

string getRoomType()
{
    int choice;

    cout << "Would you like to stay in an Entire Home/Apartment or would you rather just get a Private Room?" << endl;
    cout << "Enter 1 for Entire Home/Apartment" << endl << "Enter 2 for Private Room" << endl;
    cin >> choice;

    while (choice != 1 && choice != 2)
    {
        cout << "Invalid response." << endl << "Enter 1 for Entire Home/Apartment" << endl << "Enter 2 for Private Room" << endl;
    }

    if (choice == 1)
    {
        return "Entire home/apt";
    }

    else if (choice == 2)
    {
        return "Private room";
    }
}

string getPrice()
{
    string price;
    cout << "How much would you like to spend a night for a room?" << endl;
    cin >> price;

    return price;
}

string getCity()
{
    string city;

    cout << "What city would you like to visit this trip?" << endl;
    cin >> city;

    return city;
}

int main()
{
    vector<AirBnB> listing = dataLoader();   
}

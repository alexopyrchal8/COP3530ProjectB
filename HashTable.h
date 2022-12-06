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
#include <list>

using namespace std;

struct AirBnB
{ 
    string ID, name, hostID, hostName, neighborhoodGroup, neighborhood, latitude, longitude, roomType, lastReview, reviewPerMonth, city, price, minNights, numReviews, calcListCount, availability;
    
    AirBnB();
    AirBnB(string ID, string name, string hostID, string hostName, string neighborhoodGroup, string neighborhood, string latitude, string longitude, string roomType, string price, string minNights, string numReviews, string lastReview, string reviewPerMonth, string calcListCount, string availability, string city);
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

AirBnB::AirBnB(string ID, string name, string hostID, string hostName, string neighborhoodGroup, string neighborhood, string latitude, string longitude, string roomType, string price, string minNights, string numReviews, string lastReview, string reviewPerMonth, string calcListCount, string availability, string city)
{
    this->ID = ID;
    this->name = name;
    this->hostID = hostID;
    this->hostName = hostName;
    this->neighborhoodGroup = neighborhoodGroup;
    this->neighborhood = neighborhood;
    this->latitude = latitude;
    this->longitude = longitude;
    this->roomType = roomType;
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
    vector<string> result;
    string line;

    if (file.is_open())
    {
        for (int i = 0; i < 17; i++)
        {
            getline(file, line, ',');
            result.push_back(line);
        }

    }


    if (file.is_open())
    {
        int count = 1;
        string line;

        getline(file, line);

        for (int i = 0; i < 100000; i++)
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

            getline(file, line);

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

           
            AirBnB listing(IDv, namev, hostIDv, hostNamev, neighborhoodGroupv, neighborhoodv, latitudev, longitudev, roomTypev, pricev, minNightsv, numReviewsv, lastReviewv, reviewPerMonthv, calcListCountv, availabilityv, cityv);

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

class HashTable
{
    int hf = 31;
    int bucket;
    int sizeTable = 0;
    list<AirBnB> *tab;
    
public:
    HashTable(int sizeTable)
    {
        bucket = sizeTable;
        if (sizeTable == 0)
        {
            bucket = 1;
        }
        tab = new list<AirBnB>[bucket];
    }

    void insertItem(AirBnB listing, int hashKey)
    {
        if (hashKey == -1)
        {
            hashKey = 0;
        }

        int count = hashFunction(hashKey);
        tab[count].push_back(listing);
        sizeTable++;
    }

    void insertItem(AirBnB listing, string hashKey)
    {
        if (hashKey == "-1")
        {
            hashKey = "0";
        }

        int count = hashFunction(hashKey);
        tab[count].push_back(listing);
        sizeTable++;
    }

    list<AirBnB> searchItem(int hashKey)
    {
        int count = hashFunction(hashKey);
        return tab[count];
    }

    list<AirBnB> findItem(string hashKey)
    {
        int count = hashFunction(hashKey);
        return tab[count];
    }

    list<AirBnB> searchItem(float hashKey)
    {
        int count = hashFunction(hashKey);
        return tab[count];
    }

    list<AirBnB>* returnTable()
    {
        return tab;
    }

    int returnSize()
    {
        return sizeTable;
    }

    int hashFunction(int num)
    {
        int count = 0;
        if (num == -1)
        {
            num = 0;
        }

        while (num != 0)
        {
            count += (num % 10) * hf;
            num /= 10;
        }
        return count % bucket;
    }

    int hashFunction(float num)
    {
        int count = 0;
        count = num * hf;

        return count % bucket;
    }

    int hashFunction(string hashKey)
    {
        int count = 0;
        if (hashKey == "-1")
        {
            return 0;
        }

        for (int i = 0; i < hashKey.length(); i++)
        {
            count += hashKey.at(i) * hf;
        }

        return count % bucket;
    }

    vector<AirBnB> findARoom()
    {
        vector<AirBnB> listings = dataLoader();

        list<AirBnB> hold;
        list<AirBnB>* tab;

        HashTable cityTable(100000);

        for (int i = 0; i < listings.size(); i++)
        {
            cityTable.insertItem(listings.at(i), listings.at(i).city);
        }

        string city = getCity();

        HashTable roomTable(100000);
        hold = cityTable.findItem(city);
        for (auto i : hold)
        {
            if (i.city == city)
            {
                roomTable.insertItem(i, i.roomType);
            }
        }

        if (roomTable.returnSize() == 0)
        {
            cout << "Could not find\n";
        }

        string type = getRoomType();

        HashTable priceTable(roomTable.returnSize());
        hold = roomTable.findItem(type);

        for (auto i : hold)
        {
            if (i.roomType == type)
            {
                priceTable.insertItem(i, i.price);
            }
        }

        string cost = getPrice();

        HashTable nameTable(priceTable.returnSize());
        hold = priceTable.findItem(cost);

        for (auto i : hold)
        {
            if (i.price == cost)
            {
                nameTable.insertItem(i, i.name);
            }
        }

        vector<AirBnB> recommendListing;
        set<string> hasBeen;

        tab = nameTable.returnTable();
        for (int i = 0; i < priceTable.returnSize(); i++)
        {
            for (auto x : tab[i])
            {
                if (!hasBeen.count(x.name))
                {
                    recommendListing.push_back(x);
                    hasBeen.insert(x.name);
                }
            }
        }

        int listNumber = recommendListing.size();

        if (listNumber > 10)
        {
            listNumber = 10;
        }
    
        for (int i = 0; i < listNumber; i++)
        {
            cout << recommendListing.at(i).name << endl;
        }
    }
};

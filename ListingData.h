// ListingData.h stores all data for listing for convenient sorting / additional filtering

struct ListingData {
    int id;
    std::string description;
    int hostID;
    std::string hostName;
    std::string neighbourhoodGroup;
    std::string neighbourhood;
    double latitude;
    double longitude;
    std::string roomType;
    double price;
    int minNights;
    int numReviews;
    std::string lastReviewDate;
    double reviewsPerMonth;
    int hostTotalListingsCount;
    int availableDaysPerYear;
    std::string city;
};


class ListingDataBundle {
    public:
        void filter (  //  The intended use is to pass in the values directly
            int maxPrice,    //  even if they are zero, it will filter
            int minNights,   //  them all, note this will probably be
            int minReviews,  //  an expensive function to call
            int minAvailable,
            int hostListings,
            double minMonthlyReviews,
            std::string roomType,
            std::string hostName
        );

        ListingDataBundle();
        ListingDataBundle(std::vector<ListingData> data);
        void sortByMonthlyReviews(bool descendingFlag);
        void sortByTotalReviews(bool descendingFlag);
        void sortByHostListings(bool descendingFlag);
        void sortByPrice(bool descendingFlag);

        std::vector<ListingData> getVector() const;

        int getNumberOfListings() const;
        std::vector<std::string> getHosts() const;
        std::vector<std::string> getRoomTypes() const;
        std::vector<std::string> getNeighbourhoods() const;
        std::vector<std::string> getNeighbourGroups() const;
        

    private:

        bool dynamicComparer (
            std::string sortBy, 
            ListingData A, 
            ListingData B, 
            bool greaterThenFlag
        );
        std::vector<ListingData> mergeSort (  //  OBSOLETED
            std::string sortBy, 
            std::vector<ListingData> vector, 
            int start, 
            int end,
            bool descendingFlag
        );

        void bubbleSort(std::string sortBy, bool descendingFlag);
        
        std::vector<ListingData> data;
        std::vector<ListingData> displayData;
};

ListingDataBundle::ListingDataBundle() {
    //  Dummy Constructor does nothing
}

ListingDataBundle::ListingDataBundle(std::vector<ListingData> data) {
    this->data = data;
    this->displayData = data;
}

bool ListingDataBundle::dynamicComparer (  //  Returns true for A, false for B
    std::string sortBy, 
    ListingData A, 
    ListingData B, 
    bool flag
) {  //  Function Body Below This Function Is Awful, My Apologies
    bool t1 = true;  // True if less than
    bool t2 = false;  // True if greater than
    if (sortBy == "Price") {
        t1 = A.price <= B.price;
        t2 = A.price >= B.price;
    } else if (sortBy == "HostListings") {
        t1 = A.hostTotalListingsCount <= B.hostTotalListingsCount;
        t2 = A.hostTotalListingsCount >= B.hostTotalListingsCount;
    } else if (sortBy == "TotalReviews") {
        t1 = A.numReviews <= B.numReviews;
        t2 = A.numReviews >= B.numReviews;
    } else if (sortBy == "MonthlyReviews") {
        t1 = A.reviewsPerMonth <= B.reviewsPerMonth;
        t2 = A.reviewsPerMonth >= B.reviewsPerMonth;
    }
    return ((!flag && t1) || (flag && t2));


}
//  Merge Sort Causes Crash With No Error Message
//  I am assuming it is because of all the vectors,
//  but I do not know that for sure. Either way it
//  has been replaced with a simple Bubble sort
std::vector<ListingData> ListingDataBundle::mergeSort(
    std::string sortBy, 
    std::vector<ListingData> vector, 
    int start, 
    int end,
    bool descendingFlag
) {  //  Function Body Below
    std::vector<ListingData> result;
    std::cout << start << " " << end << std::endl;
    if (start == end){

        result.push_back(vector[start]);

    } else {

        int midPoint = (start + end) / 2;  //  Integer division auto floors

        std::vector<ListingData> left;
        std::vector<ListingData> right;
        left  = mergeSort(sortBy, vector, start, midPoint, descendingFlag);
        right = mergeSort(sortBy, vector, midPoint + 1, end, descendingFlag);

        int leftIndex  = 0;
        int rightIndex = 0;
        for (int i = 0; i < (end - start); i++) {

            if (dynamicComparer(
                sortBy, 
                left[leftIndex], 
                right[rightIndex], 
                descendingFlag
            )) {  //  Conditional Block Below
                result.push_back(left[leftIndex]);
                leftIndex++;
            } else {
                result.push_back(right[rightIndex]);
                rightIndex++;
            }
        }
    }

    return result;
}

void ListingDataBundle::bubbleSort(std::string sortBy, bool descendingFlag) {
    bool swapMade = true;
    ListingData temp;

    while (swapMade) {
        swapMade = false;
        for (int i = 1; i < this->displayData.size(); i++){
            if (!dynamicComparer(
                sortBy, 
                this->displayData[i - 1], 
                this->displayData[i], 
                descendingFlag
            )) {  //  Condition Body Below
                temp = this->displayData[i];
                this->displayData[i] = this->displayData[i - 1];
                this->displayData[i - 1] = temp;
                swapMade = true;
            }
        }
    }
    
}

void ListingDataBundle::filter (
        int maxPrice     = 1000000,
        int stayLength   = 365,
        int minReviews   = 0,
        int minAvailable = 0,
        int hostListings = 0,
        double minMonthlyReviews = 0.0,
        std::string roomType = "",
        std::string hostName = ""
) {  //  Function Body Below
    this->displayData.clear();
    //std::cout << "Filtering: " << roomType << std::endl;
    for (auto iter = this->data.begin(); iter != this->data.end(); iter++) {
        //  Price Check
        if (iter->price > maxPrice) {
            continue;
        }

        //  Minimum Nights Check
        if (iter->minNights > stayLength) {
            continue;
        }

        //  Minimum Reviews Check
        if (iter->numReviews < minReviews) {
            continue;
        }

        //  Minimum Availability Check
        if (iter->availableDaysPerYear < minAvailable) {
            continue;
        }

        //  Minimum Host Listings Check
        if (iter->hostTotalListingsCount < hostListings) {
            continue;
        }

        //  Minimum Monthly Reviews Check
        if (iter->reviewsPerMonth < minMonthlyReviews) {
            continue;
        }

        //  Room Type Check
        if (roomType != "") {
            if (iter->roomType != roomType) {
                continue;
            }
        }

        //  Host Name Check
        if (hostName != "") {
            if (iter->hostName != hostName) {
                continue;
            }
        }

        this->displayData.push_back(*iter);
    }

}

void ListingDataBundle::sortByMonthlyReviews(bool descendingFlag) {
    bubbleSort("MonthlyReviews", descendingFlag);
}

void ListingDataBundle::sortByTotalReviews(bool descendingFlag) {
    bubbleSort("TotalReviews", descendingFlag);
}

void ListingDataBundle::sortByHostListings(bool descendingFlag) {
    bubbleSort("HostListings", descendingFlag);
}

void ListingDataBundle::sortByPrice(bool descendingFlag) {
    bubbleSort("Price", descendingFlag);
}

std::vector<ListingData> ListingDataBundle::getVector() const {
    return this->displayData;
}

int ListingDataBundle::getNumberOfListings() const {
    return this->displayData.size();
}

std::vector<std::string> ListingDataBundle::getHosts() const {
    std::vector<std::string> result;
    for (auto iter = this->data.begin(); iter != this->data.end(); iter++) {
        bool found = false;

        for (int i = 0; i < result.size(); i++) {
            if (result[i] == iter->hostName) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(iter->hostName);
        }
    }
    return result;
}

std::vector<std::string> ListingDataBundle::getRoomTypes() const {
    std::vector<std::string> result;
    for (auto iter = this->data.begin(); iter != this->data.end(); iter++) {
        bool found = false;

        for (int i = 0; i < result.size(); i++) {
            if (result[i] == iter->roomType) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(iter->roomType);
        }
    }
    return result;
}

std::vector<std::string> ListingDataBundle::getNeighbourhoods() const {
    std::vector<std::string> result;
    for (auto iter = this->data.begin(); iter != this->data.end(); iter++) {
        bool found = false;

        for (int i = 0; i < result.size(); i++) {
            if (result[i] == iter->neighbourhood) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(iter->neighbourhood);
        }
    }
    return result;
}

std::vector<std::string> ListingDataBundle::getNeighbourGroups() const {
    std::vector<std::string> result;
    for (auto iter = this->data.begin(); iter != this->data.end(); iter++) {
        bool found = false;

        for (int i = 0; i < result.size(); i++) {
            if (result[i] == iter->neighbourhoodGroup) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.push_back(iter->neighbourhoodGroup);
        }
    }
    return result;
}

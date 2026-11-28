#include "CampusCompass.h"
#include <string>
using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not
    ifstream file(edges_filepath);
    if (!file.is_open()) return false;

    //parse the edges file
    string line;
    int count = 0;
    while (getline(file,line)) {
        //skip the first line
        if (count == 0) {
            count++;
            continue;
        }
        
        //parse line by line
        stringstream ss(line);
        string from_str, to_str, weight_str;

        getline(ss, from_str, ',');
        getline(ss, to_str, ',');
        for (int i = 0; i < 3; i++) {
            getline(ss, weight_str, ',');
        }

        graph.addEdge(stoi(from_str), stoi(to_str), stoi(weight_str));
    }

    //NOW parse the classes file!!!
    file.close();
    file.open(classes_filepath);
    if (!file.is_open()) return false;

    //parse the classes file
    count = 0;
    while (getline(file,line)) {
        //skip the first line
        if (count == 0) {
            count++;
            continue;
        }
        
        //parse line by line
        stringstream ss(line);
        string class_str, locationID_str, time_str;
        int time1, time2;
        vector<int> values;

        getline(ss, class_str, ',');
        getline(ss, locationID_str, ',');
        values.push_back(stoi(locationID_str));

        //get the appropriate time, stoi and hour to minutes
        getline(ss, time_str, ':');
        time1 = stoi(time_str) * 60;
        getline(ss, time_str, ',');
        time1 += stoi(time_str);
        getline(ss, time_str, ':');
        time2 = stoi(time_str) * 60;
        getline(ss, time_str, ',');
        time2 += stoi(time_str);
        values.push_back(time1);
        values.push_back(time2);

        classLocations[class_str] = values;
    }






    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}

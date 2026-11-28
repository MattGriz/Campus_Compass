#include "CampusCompass.h"
#include <string>
#include <regex>
using namespace std;

CampusCompass::CampusCompass() {} //constructor

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

        //get the appropriate times, stoi and hour to minutes
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

        //add the elements to the classLocations map 
        classLocations[class_str] = values;
    }

    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    //get command type
    stringstream ss(command);
    string commandType;
    ss >> commandType;

    //regex parsing rules
    static const regex namePattern("[a-zA-Z ]+");
    static const regex UFIDPattern("[0-9]{8}");
    static const regex classPattern("[A-Z]{3}[0-9]{4}");

    //check commandType and handle all command logic
    if (commandType == "insert") {
        string name, UFID, residenceID, num, course;
        set<string> courses;
        
        //extract name and remaining arguments
        if (!getline(ss, name, '"')) return false;
        if (!(ss >> UFID >> residenceID >> num)) return false;

        //validate name and UFID
        if (!regex_match(name, namePattern) || !regex_match(UFID, UFIDPattern)) return false;
        //check uniquesness name and UFID
        if (students.find(UFID) != students.end()) return false;
        //check number of classes
        if (stoi(num) < 1 || stoi(num) > 6) return false;
        //validate class codes
        for (int i = 0; i < stoi(num); i++) {
            if (!(ss >> course)) return false;
            if (!regex_match(course, classPattern)) return false;

            //check if class exists
            if (classLocations.find(course) == classLocations.end()) 
                return false;
            //check for duplicate classes
            if (courses.find(course) != courses.end()) return false;

            courses.insert(course);
        }

        //check for extra arguments
        if (ss >> course) return false;

        //make student object 
        Student stud;
        stud.name = name;
        stud.UFID = UFID;
        stud.residenceID = stoi(residenceID);
        stud.classes = courses;
        students[UFID] = stud;

    } else if (commandType == "removeClass") { //===============================================================================//
    } else if (commandType == "remove") {
        string UFID, extra;
        if (!(ss >> UFID)) return false;

        //validate UFID
        if (!regex_match(UFID, UFIDPattern)) return false;

        //check for extra arguments
        if (ss >> extra) return false;

        //check to see if UFID is there then erase
        if(students.find(UFID) == students.end()) return false;
        students.erase(UFID);
        return true;

    } else if (commandType == "dropClass") { 
        
    } else if (commandType == "replaceClass") { //===============================================================================//
    } else if (commandType == "toggleEdgesClosure") { //===============================================================================//
    } else if (commandType == "checkEdgeStatus") { //===============================================================================//
    } else if (commandType == "isConnected") { //===============================================================================//
    } else if (commandType == "printShortestEdges") { //===============================================================================//
    } else if (commandType == "printStudentZone") { //===============================================================================//
    } else if (commandType == "verifySchedule") { //===============================================================================//
    } else {
        return false;
    }
    return true;
}

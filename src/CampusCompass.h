#pragma once
#include "Graph.h"
#include <set>

struct Student {
    string name;
    string UFID;
    int residenceID;
    set<string> classes;
};

class CampusCompass {
    private:
        Graph graph; //graph of the school, locations, and times
        unordered_map<string, vector<int>> classLocations; //map of vectors bu class name, <ID, start, end>
        unordered_map<string, Student> students; // map of students for the extra credit

        // Think about what member variables you need to initialize
        // perhaps some graph representation?
    public:
        // Think about what helper functions you will need in the algorithm
        CampusCompass(); // constructor
        bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
        bool ParseCommand(const string &command);
};

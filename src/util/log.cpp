#include "stdpch.hpp"

#include "log.hpp"
//#include <iostream>
//#include <fstream>

using namespace std;

namespace Log {
    void error(const std::string& message) {
        ofstream logfile;
        logfile.open("log.txt");
        if(!logfile.is_open()) {
            cout << "Couldn't open logfile for writing!\n";
        }
        logfile << message << "\n";
        logfile.close();
    }
}
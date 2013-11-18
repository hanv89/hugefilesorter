/* 
 * File:   main.cpp
 * Author: hanv
 *
 * Created on November 17, 2013, 10:17 AM
 */

#include <cstdlib>
#include <iostream>

#include "Configurations.h"
#include "Application.h"
using namespace std;

/*
 * 
 */
void showHelp(){
    cout << "Usage: input output <part size>" << endl;
}

int main(int argc, char** argv) {
    cout << "This is HugeFileSorter Project" << endl;
    if (argc == 2 || argc == 3 || argc == 4) {
        if (argc == 2 && (argv[1] == "--help" || argv[1] == "-h")){
            showHelp();
        } else if(argc == 3 || argc == 4){    
            
            Configurations::getInstance()->initialize(argc,argv);
            
            Application::getInstance()->run();            
            cout << "Finished!" << endl;
            Configurations::deInstance();
            
        } else {
            showHelp();
        }
    } else {
        showHelp();
    }
    
    return 0;
}


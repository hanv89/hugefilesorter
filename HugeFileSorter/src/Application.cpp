/* 
 * File:   Application.cpp
 * Author: hanv
 * 
 * Created on November 17, 2013, 12:20 PM
 */

#include "Application.h"
#include "Configurations.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
Application * Application::m_Instance = NULL;

Application::Application() {
}

Application::~Application() {
}

Application* Application::getInstance(){
    if (m_Instance == NULL){
        m_Instance = new Application();
    }
    return m_Instance;
}

void Application::deInstance(){
    delete m_Instance;
    m_Instance = NULL;
}

void Application::run(){
    
}
    

void Application::preprocess(){
    
    cout << "Partitioning file " << Configurations::getInstance()->getInput() << endl;
    
    ifstream ifs;
    ifs.open(Configurations::getInstance()->getInput().c_str());
    
    ofstream ofs;
    
    string currentPartName = "part_0_0"; 
    m_PartFiles.push_back(currentPartName);
    ofs.open(currentPartName.c_str());
    
    string line;
    int lineIndex = 0;
    int currentPartSize = 0;
    int currentPartIndex = 0;
    while (getline(ifs,line)){
        
        lineIndex++;
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cout << "Reading " << lineIndex << " line(s)";
        
        int lineSize = line.size();
        currentPartSize += lineSize;
        
        ofs << line << endl;
        
        if (currentPartSize > Configurations::getInstance()->getPartSize()){
            currentPartIndex ++;
            currentPartSize = 0;
            
            ofs.close();
            
            currentPartName = "part_0_" + currentPartIndex; 
            m_PartFiles.push_back(currentPartName);
            ofs.open(currentPartName.c_str());
        }
    } 
    ifs.close();
    ofs.close();
    cout << endl;
}

void Application::sortParts(){    
    for (int fileIndex = 0; fileIndex < m_PartFiles.size(); fileIndex++){
        
        vector<string> lines;
        
        ifstream ifs;
        ifs.open(m_PartFiles[fileIndex].c_str());
        
        string line;
        while (getline(ifs,line)){
            lines.push_back(line);
            
        }
        
        ifs.close();
        
        struct {
            bool operator()(const string& a, const string& b)
            {   
                return a.compare(b) < 0;
            }   
        } stringLess;
        std::sort(lines.begin(),lines.end(),stringLess);
        
        ofstream ofs;
        ofs.open(m_PartFiles[fileIndex].c_str(), std::fstream::out | std::fstream::trunc);
        for (int lineIndex; lineIndex < lines.size(); lineIndex ++){
            ofs << lines[lineIndex] << endl;
        }
        ofs.close();        
    }
}

void Application::mergeParts(){
    int partGroupSize = 1;
    if (Configurations::getInstance()->getMergeCount() > 1){
        partGroupSize = (int) (log(m_PartFiles.size()) / log(Configurations::getInstance()->getMergeCount()) + 1);
    }    
    
    vector<string> tempPartFiles = m_PartFiles;    
    m_PartFiles.clear();    
    
    do {
        vector<ifstream> parts;
        ofstream ofs;
        string currentPartGroup = "part_1_0";
        ofs.open(currentPartGroup.c_str());
        
        int fileIndex = 0;
        int fileGroupIndex = 0;
        
        for ( ; fileGroupIndex < Configurations::getInstance()->getMergeCount(); fileGroupIndex ++){
        
             
            for ( ; fileIndex < (fileGroupIndex+1)*partGroupSize; fileIndex ++){
                ifstream ifs;
                ifs.open(tempPartFiles[fileIndex].c_str());
            }  
        }
    }
    while (m_PartFiles.size() == 1);

}

void Application::process(){
     
}


/* 
 * File:   Application.cpp
 * Author: hanv
 * 
 * Created on November 17, 2013, 12:20 PM
 */

#include "Application.h"
#include "Configurations.h"
#include <fstream>
#include <algorithm>
#include <math.h>
#include <sstream>
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
    preprocess();
    process();
}
    

void Application::preprocess(){
    
    cout << "Partitioning file " << Configurations::getInstance()->getInput() << endl;
    
    ifstream* ifs = new ifstream;
    ifs->open(Configurations::getInstance()->getInput().c_str());
    
    ofstream* ofs = new ofstream;
    
    string currentPartName = "part_0_0"; 
    m_PartFiles.push_back(currentPartName);
    ofs->open(currentPartName.c_str());
    
    string line;
    int lineIndex = 0;
    int currentPartSize = 0;
    int currentPartIndex = 0;
    while (getline(*ifs,line)){
        
        lineIndex++;
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cout << "Reading " << lineIndex << " line(s)";
        
        int lineSize = line.size();
        currentPartSize += lineSize;
        
        *ofs << line << endl;
        
        if (currentPartSize > Configurations::getInstance()->getPartSize()){
            currentPartIndex ++;
            currentPartSize = 0;
            
            ofs->close();
            
            currentPartName = "part_0_" + currentPartIndex; 
            m_PartFiles.push_back(currentPartName);
            ofs->open(currentPartName.c_str());
        }
    } 
    ifs->close();
    ofs->close();
    delete ifs;
    delete ofs;
    cout << endl;
}

void Application::sortParts(){    
    for (int fileIndex = 0; fileIndex < m_PartFiles.size(); fileIndex++){
        
        vector<string> lines;
        
        ifstream* ifs = new ifstream;
        ifs->open(m_PartFiles[fileIndex].c_str());
        
        string line;
        while (getline(*ifs,line)){
            lines.push_back(line);
            
        }
        
        ifs->close();
        
        
        std::sort(lines.begin(),lines.end(),StringLess);
        
        ofstream* ofs;
        ofs->open(m_PartFiles[fileIndex].c_str(), std::fstream::out | std::fstream::trunc);
        for (int lineIndex; lineIndex < lines.size(); lineIndex ++){
            *ofs << lines[lineIndex] << endl;
        }
        ofs->close();        
    }
}

void Application::mergeParts(vector<string>& _result, const vector<string>& parts, int mergeCount){
    int newPartCount = (parts.size() / 2) + 1;
    
    for (int newPartIndex = 0; newPartIndex < newPartCount; newPartIndex++){
        vector<ifstream*> partISs;
        ofstream* ofs = new ofstream;
        string currentPartGroup;
        if (newPartCount == 1){
            currentPartGroup = Configurations::getInstance()->getOutput();
        } else {
            stringstream ss;
            ss << "part_" << mergeCount << "_" << newPartIndex;
            currentPartGroup = ss.str();
        }
        _result.push_back(currentPartGroup);
        ofs->open(currentPartGroup.c_str());
        
        int lastIndex = (newPartIndex + 1)*2;        
        lastIndex = lastIndex > parts.size() ? parts.size() : lastIndex;
        
        
        for (int i = newPartIndex * 2; i < lastIndex; i++){
            ifstream* ifs = new ifstream;
            ifs->open(parts[i].c_str());
            partISs.push_back(ifs);
        }
        
        //Do read and merge
        string line1;
        string line2;
        getline(*(partISs[0]),line1);
        getline(*(partISs[1]),line2);
        while (true){
            if(line1.compare(line2) < 0){
                *ofs << line1 << endl;
                if (!getline(*(partISs[0]),line1)){
                    break;
                }
            } else {
                *ofs << line2 << endl;
                 if (!getline(*(partISs[1]),line2)){
                    break;
                }
            }
        }
        
        while (getline(*(partISs[1]),line2)) {
            *ofs << line2 << endl;
        }
        while (getline(*(partISs[0]),line1)) {
            *ofs << line1 << endl;
        }

        for (int i = 0; i<partISs.size(); i++){
            partISs[i]->close();
        }
        
        ofs->close();
        
    }
    
//    vector<string> tempPartFiles = m_PartFiles;    
//    m_PartFiles.clear();    
//    
//    do {
//        vector<ifstream> parts;
//        ofstream ofs;
//        string currentPartGroup = "part_1_0";
//        ofs.open(currentPartGroup.c_str());
//        
//        int fileIndex = 0;
//        int fileGroupIndex = 0;
//        
//        for ( ; fileGroupIndex < Configurations::getInstance()->getMergeCount(); fileGroupIndex ++){
//        
//             
//            for ( ; fileIndex < (fileGroupIndex+1)*partGroupSize; fileIndex ++){
//                ifstream ifs;
//                ifs.open(tempPartFiles[fileIndex].c_str());
//            }  
//        }
//    }
//    while (m_PartFiles.size() == 1);

}

void Application::process(){
//    int partGroupSize = m_PartFiles.size();
//    if (Configurations::getInstance()->getMergeCount() > 1){
//        partGroupSize = (int) (log(m_PartFiles.size()) / log(Configurations::getInstance()->getMergeCount()) + 1);
//    }
    
    vector<string> fileList = m_PartFiles;
    int index = 0;
    do {
        vector<string> oldFileList = fileList;
        fileList.clear();
        mergeParts(fileList, oldFileList, index);
        index ++;
    } while(fileList.size() > 1);   
    
}


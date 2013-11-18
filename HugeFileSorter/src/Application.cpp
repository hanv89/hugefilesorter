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
    sortParts();
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
            
            stringstream ss;
            ss << "part_0_" << currentPartIndex;
            currentPartName =  ss.str();
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
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cout << "Sorting part " << (fileIndex + 1) << " of " << m_PartFiles.size();
        vector<string*>* lines = new vector<string*>();
        
        ifstream* ifs = new ifstream;
        ifs->open(m_PartFiles[fileIndex].c_str());
        
        string line;
        while (getline(*ifs,line)){
            
            lines->push_back(new string(line));            
        }
        
        
        ifs->close();
        delete ifs;
        
        std::sort(lines->begin(),lines->end(),StringLess);
        
        ofstream* ofs = new ofstream;
        ofs->open(m_PartFiles[fileIndex].c_str(), std::ofstream::out | std::ofstream::trunc);
        for (int lineIndex = 0; lineIndex < lines->size(); lineIndex ++){
            *ofs << *(lines->at(lineIndex)) << endl;
            
        }
        ofs->close();  
        delete ofs;        
        
        lines->clear();
        delete lines;
        
    }
    cout << endl;
}

void Application::mergeParts(vector<string>& _result, const vector<string>& parts, int mergeCount){
    int newPartCount = (parts.size() / 2) + (parts.size() % 2);
    
    for (int newPartIndex = 0; newPartIndex < newPartCount; newPartIndex++){
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cout << "Merging part " << (newPartIndex + 1) << " of " << newPartCount << " at merge step " << mergeCount;
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
        
        int lastIndex = (newPartIndex + 1)*2;        
        lastIndex = lastIndex > parts.size() ? parts.size() : lastIndex;
        
        if ((lastIndex - newPartIndex * 2) <= 1){
             
            _result.push_back(parts[lastIndex-1]);
        
        } else {
           _result.push_back(currentPartGroup);
           ofs->open(currentPartGroup.c_str());
        
        
        
        
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
                delete partISs[i];
            }
            partISs.clear();

            ofs->close();
            
            //remove merged part file
            for (int i = newPartIndex * 2; i < lastIndex; i++){
                remove(parts[i].c_str());                
            }
            
        }
        delete ofs;
        
    }
    cout << endl;
    
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
        index ++;
        vector<string> oldFileList = fileList;
        fileList.clear();
        mergeParts(fileList, oldFileList, index);
        
    } while(fileList.size() > 1);   
    
}


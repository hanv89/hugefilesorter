/* 
 * File:   Configurations.cpp
 * Author: hanv
 * 
 * Created on November 17, 2013, 11:41 AM
 */

#include "Configurations.h"
#include "SimpleNumberParser.h"
Configurations * Configurations::m_Instance = NULL;

Configurations::Configurations() {
    m_partSize = 10000000;
     
}

Configurations::~Configurations() {
}

Configurations* Configurations::getInstance(){
    if (m_Instance == NULL){
        m_Instance = new Configurations();
    }
    return m_Instance;
}

void Configurations::deInstance(){
    delete m_Instance;
    m_Instance = NULL;
}

void Configurations::initialize(int argc,char** argv){
    if (argc == 3){
        m_Input = argv[1];
        m_Output = argv[2];
    } else if (argc == 4){
        m_Input = argv[1];
        m_Output = argv[2];
        
        bool error;
        int partSize = SimpleNumberParser::parseInt(argv[3],error);
        if (!error){
            m_partSize = partSize;
        }
        
        
    }
}
string& Configurations::getInput(){
    return m_Input;
}
string& Configurations::getOutput(){
    return m_Output;
}
int Configurations::getPartSize(){
    return m_partSize;
}


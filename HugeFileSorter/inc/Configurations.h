/* 
 * File:   Configurations.h
 * Author: hanv
 *
 * Created on November 17, 2013, 11:41 AM
 */

#include <string>

#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H

using namespace std;

class Configurations {
public:
    Configurations();    
    virtual ~Configurations();
    
    static Configurations* getInstance();
    static void deInstance();
    void initialize(int argc,char** argv);
    string& getInput();
    string& getOutput();
    int getPartSize();
    int getMergeCount();
private:
    static Configurations* m_Instance;
    string m_Input;
    string m_Output;
    int m_partSize;
    int m_mergeCount;
};

#endif	/* CONFIGURATIONS_H */


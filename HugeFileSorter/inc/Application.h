/* 
 * File:   Application.h
 * Author: hanv
 *
 * Created on November 17, 2013, 12:20 PM
 */
#include <string>
#include <vector>
#ifndef APPLICATION_H
#define	APPLICATION_H
using namespace std;
class Application {
public:
    Application();
    virtual ~Application();
    
    static Application* getInstance();
    static void deInstance();
    
    void run();
    
private:
    void preprocess();
    void process();
    void sortParts();
    void mergeParts();
    
private:
    static Application* m_Instance;
    
    vector<string> m_PartFiles;
};

#endif	/* APPLICATION_H */


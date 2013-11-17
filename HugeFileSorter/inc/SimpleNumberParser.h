/* 
 * File:   SimpleNumberParser.h
 * Author: hanv
 *
 * Created on September 29, 2013, 7:47 PM
 */

#ifndef SIMPLENUMBERPARSER_H
#define	SIMPLENUMBERPARSER_H
#include <vector>
#include <string>
using namespace std;

class SimpleNumberParser {
    
public:
    SimpleNumberParser();
    SimpleNumberParser(const SimpleNumberParser& orig);
    virtual ~SimpleNumberParser();
    
    static long parseLong(const string& input, bool& error);
    static int parseInt(const string& input, bool& error);
private:
    static string numberChars;

};

#endif	/* SIMPLENUMBERPARSER_H */


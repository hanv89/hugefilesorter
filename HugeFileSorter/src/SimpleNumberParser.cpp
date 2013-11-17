/* 
 * File:   SimpleNumberParser.cpp
 * Author: hanv
 * 
 * Created on September 29, 2013, 7:47 PM
 */

#include <stdlib.h>

#include "SimpleNumberParser.h"
string SimpleNumberParser::numberChars = "-0123456789";
SimpleNumberParser::SimpleNumberParser() {
}

SimpleNumberParser::SimpleNumberParser(const SimpleNumberParser& orig) {
}

SimpleNumberParser::~SimpleNumberParser() {
}

long SimpleNumberParser::parseLong(const string& input, bool& error){
    bool isNumber = false;
    for (int j = 0; j < numberChars.size(); j ++){
        if (input.at(0) == numberChars.at(j)){
            isNumber = true;
            break;
        }
    }
    if (!isNumber){
        error = true;
        return 0;
    }
    for (int i = 1 ; i < input.size() ; i++){
        isNumber = false;
        for (int j = 1; j < numberChars.size(); j ++){
            if (input.at(i) == numberChars.at(j)){
                isNumber = true;
                break;
            }
        }
        if (!isNumber){
            error = true;
            return 0;
        }
    }
    return atol(input.c_str());
}

int SimpleNumberParser::parseInt(const string& input, bool& error){
    bool isNumber = false;
    for (int j = 0; j < numberChars.size(); j ++){
        if (input.at(0) == numberChars.at(j)){
            isNumber = true;
            break;
        }
    }
    if (!isNumber){
        error = true;
        return 0;
    }
    for (int i = 1 ; i < input.size() ; i++){
        isNumber = false;
        for (int j = 1; j < numberChars.size(); j ++){
            if (input.at(i) == numberChars.at(j)){
                isNumber = true;
                break;
            }
        }
        if (!isNumber){
            error = true;
            return 0;
        }
    }
    return atoi(input.c_str());
}

#pragma once
#ifndef EXCEPTION_h
#define EXCEPTION_h
#include<iostream>
using namespace std;

//Exception class 
class Exception {
private:
    string errorMessage;
public:
    Exception(string error = "NULL") {
        errorMessage = error;
    }
    void printError() {
        cout << errorMessage << endl;
    }
};
#endif


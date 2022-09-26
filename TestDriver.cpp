/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * * Purpose:
 *     To run the Test Class.   
 * 
 * by Gabe Smithline, July 29, 2022
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Tests.h"
const string CML = "Usage: ./SixDegrees dataFile [commandFile] [outputFile]";


int main(int argc, char *argv[])
{
    Tests test;
    cout << "Test get_neighbors" << endl;
    test.test_get_neighbors();
    cout << "Test to fill graph" << endl;
    test.test_fill_graph();
    cout << "Test for report path" << endl;
    test.test_report_path();
    cout << "Integration tests for SixDegrees" << endl;
    test.test_situation(argc, argv);
 
}
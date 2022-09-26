/*
 * Tests.h
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 ** Purpose:
 **  To test functionality of the SixDegrees Implementation
 **  
 * 
 * 
 * by Gabe Smithline 
 */
#ifndef __TESTS__
#define __TESTS__

#include <list>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;
#include "SixDegrees.h"
#include "CollabGraph.h"
#include "Tests.h"
#include "Artist.h"

class Tests {
    public:
        
        void test_get_neighbors();
        void test_fill_graph();
        void test_report_path();
        void test_situation(int argc, char *argv[]);

    private:
        list<Artist> buildArtists();
        void print_route(stack<Artist> &artists);

    
};

#endif
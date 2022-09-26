/*
 * SixDegrees.h
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 ** Purpose:
 **  To run the SixDegrees Simulation, it instantiates a CollabGraph class,
 *   fills it and gives the user the ability to run a BFS, DFS, and an
 *   exclusion search.  
 **  
 * 
 * 
 * by Gabe Smithline, July 29, 2022
 */
#ifndef __SIXDEGREES__
#define __SIXDEGREES__
#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <iostream>


using namespace std;
#include "SixDegrees.h"
#include "CollabGraph.h"

class SixDegrees {
    public:
        void runGame(std::istream &artists, std::istream &commands,
std::ostream &output);

    private:
        /* Methods for searches */
        void run_bfs_dfs_not(string search, std::istream &commands, 
            std::ostream &output);
        
        void run_bfs(std::queue<Artist> bfsQueue);
        void run_dfs(std::stack<Artist> dfsStack);
        void DFS(string source, string dest, std::ostream &output);
        void BFS(string source, string dest, std::ostream &output);
        void exclude(string source, string dest, std::ostream &output, 
                std::istream &commands);

        void print_route(std::ostream &output, 
            std::stack<Artist> stackBFS, string s, string d);       
        void get_data(std::istream &artists);
        
        void end_game();
        void print_check_vertex(string a, string b, std::ostream &output);
        bool check_vertex(string a);
        void get_exclusion();


    CollabGraph *graph;

};

#endif
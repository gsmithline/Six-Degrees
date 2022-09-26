/*
 * SixDegrees.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * Purpose:
 **  To run the SixDegrees Simulation, it instantiates a CollabGraph class,
 *   fills it and gives the user the ability to run a BFS, DFS, and an
 *   exclusion search.  
 * 
 * 
 * by Gabe Smithline, July 29, 2022
 */
#include <vector>
#include <list>
#include "SixDegrees.h"
#include "CollabGraph.h"

using namespace std;
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: runGame
 * purpose: Drive the game, responsible for taking input and calling correct
    functions. 
 *
 * parameters: std::istream &artists, std::istream &commands, 
   std::ostream &output
 * returns: void
 */
void SixDegrees::runGame(std::istream &artists, std::istream &commands,
std::ostream &output)
{
    
    graph = new CollabGraph;
    get_data(artists);
    string line = "";
    while(getline(commands, line) and line != "quit" ){
        if(line == "bfs" or line == "dfs" or line == "not"){
           run_bfs_dfs_not(line, commands, output);
        } else if(line == "print"){
            graph->print_graph(output);
        } else {
            output << line << " is not a command. Please try again." << endl;
        }
    }
    end_game();
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: run_bfs_dfs_not
 * purpose: call either bfs, dfs, or exclusion depending on input
 * parameters: string search, std::istream &commands, std::ostream &output 
 *
 * returns: void
 */
void SixDegrees::run_bfs_dfs_not(string search, std::istream &commands, 
std::ostream &output)
{
    graph->clear_metadata();
    string a1; 
    string a2; 
    getline(commands, a1);
    getline(commands, a2);
    if(search == "bfs"){
        BFS(a1, a2, output);
    } else if (search == "dfs"){
        DFS(a1, a2, output);
    } else if(search == "not"){
        exclude(a1, a2, output, commands);
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: get_data
 * purpose: read in data from artists.txt file, create Artists and add to list,
    then calls make graph in Collabgraph to make the graph
 * parameters: std::istream &artists
 *
 * returns: void
 */
void SixDegrees::get_data(std::istream &artists)
{
    string artN = "";
    std::list<Artist> artistList;
    while(getline(artists, artN)){
        Artist newArtist(artN);
        while(getline(artists, artN) and artN != "*" and artN != ""){
            newArtist.add_song(artN);
        } 
        artistList.push_back(newArtist);
        graph->insert_vertex(newArtist);
    }
    graph->add_edges(artistList);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: endGame
 * purpose: clear memory after game is done executing
 * parameters: none
 *
 * returns: void
 */
void SixDegrees::end_game()
{
    delete graph;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: BFS
 * purpose: take in source and dest, call run BFS to do the search, and call
    functions to check_vertex prior, then call print route. 
 * parameters: string source, string dest, std::ostream &output
 *
 * returns: void
 */
void SixDegrees::BFS(string source, string dest, std::ostream &output)
{
    if(!check_vertex(source) or !check_vertex(dest)){
        print_check_vertex(source, dest, output);
        return; 
    } else if(graph->is_marked(graph->get_artist(source))){
        stack<Artist> emptyResult; 
        print_route(output, emptyResult, source, dest);
        return;
    } else {
        Artist start = graph->get_artist(source);
        std::queue<Artist> bsfQ;
        graph->mark_vertex(start);
        bsfQ.push(start);
        run_bfs(bsfQ);
        Artist end = graph->get_artist(dest);
        stack<Artist> result = graph->report_path(start, end);
        print_route(output, result, source, dest);
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: run_bfs
 * purpose: to actually run the bfs search and mark predecessors
 * parameters: std::queue<Artist> bfsQueue
 *
 * returns: void
 */
void SixDegrees::run_bfs(std::queue<Artist> bfsQueue)
{
    while(!bfsQueue.empty()){
        Artist front = bfsQueue.front();
        bfsQueue.pop();
        vector<Artist> neighbors = graph->get_vertex_neighbors(front);
        for(size_t i = 0; i < neighbors.size(); i++)
        {
            if(!graph->is_marked(neighbors.at(i))){
                graph->mark_vertex(neighbors.at(i));
                graph->set_predecessor(neighbors.at(i), front);
                bfsQueue.push(neighbors.at(i));
            }
        }
    } 
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: DFS
 * purpose: to actually run the bfs search and mark predecessors,
 * if invalud vertices are given an error is returned and the search 
 * does not execute. 
 * parameters: string source, string dest, std::ostream &output
 *
 * returns: void
 */
void SixDegrees::DFS(string source, string dest, std::ostream &output)
{
    if(!check_vertex(source) or !check_vertex(dest)){
        print_check_vertex(source, dest, output);
        return;
    } else {
        std::stack<Artist> dfsStack;
        Artist start = graph->get_artist(source);
        graph->mark_vertex(start);
        dfsStack.push(start);
        run_dfs(dfsStack);
        Artist end = graph->get_artist(dest);
        stack<Artist> result = graph->report_path(start, end);
        print_route(output, result, source, dest);
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: run_dfs
 * purpose: to actually run the dfs search and mark predecessors
 * parameters: std::stack<Artist> dfsStack
 *
 * returns: void
 */
void SixDegrees::run_dfs(std::stack<Artist> dfsStack)
{
    while(!dfsStack.empty()){
        Artist front = dfsStack.top();
        dfsStack.pop();
        vector<Artist> neighbors = graph->get_vertex_neighbors(front);
        for(size_t i = 0; i < neighbors.size(); i++)
        {
            if(!graph->is_marked(neighbors.at(i))){
                graph->mark_vertex(neighbors.at(i));
                graph->set_predecessor(neighbors.at(i), front);
                dfsStack.push(neighbors.at(i));
            }
        }
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: exclude
 * purpose: to run the exclusion, it marks names provided as exclusions as 
 visited, so when running the actual search these vertices are avoided.  If 
 the name provided is not found in the graph the search does not run. If
 all the vertices provided are valid a bfs search runs with the exclusions.
 * parameters: string source, string dest, std::ostream &output, 
   std::istream &commands
 *
 * returns: void
 */
void SixDegrees::exclude(string source, string dest, std::ostream &output, 
std::istream &commands)
{
    vector<string> exclusions;  
    int flag = 0;
    string name = "";
    while(getline(commands, name) and name != "*"){
            if(name != "*") {
                exclusions.push_back(name);
            } 
        }
    print_check_vertex(source, dest, output);
    for(size_t i = 0; i < exclusions.size(); i++){
        if(!check_vertex(exclusions.at(i))){
            flag++;
            print_check_vertex(exclusions.at(i), dest, output);
        } else {
            Artist exclude = graph->get_artist(exclusions.at(i)); 
            graph->mark_vertex(exclude);
        }
    }
    if(!check_vertex(source) or !check_vertex(dest) or flag > 0){
        return; 
    } else {
       BFS(source, dest, output); 
    };
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: print_route
 * purpose: print the correct output when a vertex is not found in the graph
 * parameters: std::ostream &output,
 * std::stack<Artist> stackBFS, string s, string d
 *
 * returns: void
 */
void SixDegrees::print_route(std::ostream &output,
std::stack<Artist> stackBFS, string s, string d)
{
    if(stackBFS.size() < 1){
        output << "A path does not exist between " 
        << '"' << s << '"' << " and " << '"' << d << '"' << "." << endl;
        return;
    } else {
        while(stackBFS.size() > 1){
            Artist start = stackBFS.top();
            stackBFS.pop();
            string song = start.get_collaboration(stackBFS.top());
            output << '"' << start << '"'<< " collaborated with " 
            <<'"'<< stackBFS.top() <<'"'<<" in " << '"' << song << '"' 
            << "." << endl;
        }
    output << "***" << endl;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: check_vertex
 * purpose: check if a vertex is in the graph, if it is returns true,
    if it is not in the graph it returns false.
 * parameters: string a 
 *
 * returns: bool
 */
bool SixDegrees::check_vertex(string a)
{
    Artist art(a); 
    if(graph->is_vertex(art)){
        return true;
    } else {
        return false;
    }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: print_check_vertex
 * purpose: print the correct output when a vertex is not found in the graph
 * parameters: string a, string b, std::ostream &output,
 *
 * returns: void
 */
void SixDegrees::print_check_vertex(string a, string b, std::ostream &output)
{
    if(!check_vertex(a) and !check_vertex(b)){
        output << '"' << a << '"'<< " was not found in the dataset :(" << endl;
        output << '"' << b << '"'<< " was not found in the dataset :(" << endl;
    } else if (!check_vertex(a) or !check_vertex(b)){
        if(!check_vertex(a)){
            output << '"' << a 
            << '"'<< " was not found in the dataset :(" << endl;
        } else if (!check_vertex(b)){
            output << '"' << b 
            << '"'<< " was not found in the dataset :(" << endl;
        }
    }
}
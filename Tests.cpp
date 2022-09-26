/*
 * Tests.cpp
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

#include <vector>
#include <list>
#include <unordered_set>
#include "SixDegrees.h"
#include "CollabGraph.h"
#include "Tests.h"
#include "Artist.h"

using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: buildArtists
 * purpose: create artists for CollabGraph tests 
 *
 * parameters: none
 * returns: void
 */
list<Artist> Tests::buildArtists()
{
    list<Artist> result; 
    vector<string> names = {"Joe", "John", "Jake"};
    vector<string> songs = {"song1", "song1", "song1"};
    for(int i = 0; i < names.size(); i++){
        Artist newArtist(names.at(i)); 
        for(int i = 0; i < songs.size(); i++){
            newArtist.add_song(songs.at(i)); 
        }
        result.push_back(newArtist);
    }

    return result; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: test_get_neighbors
 * purpose: to test the get_neighbors functionality
 * It should return the neighbors of all the artists in the artists list
 *
 * parameters: none
 * returns: void
 */
void Tests::test_get_neighbors()
{
    list<Artist> artists = buildArtists();
    CollabGraph graph; 
    for(Artist a : artists){
        graph.insert_vertex(a);
    }
    graph.add_edges(artists);
    
    vector<Artist> John = graph.get_vertex_neighbors(artists.front());
    for(int i = 0; i < John.size(); i++){
        cout << "John's neighbor: " << i+1 << " " 
        << John.at(i).get_name() << endl;
    }
    vector<Artist> Jake = graph.get_vertex_neighbors(artists.back());
    for(int i = 0; i < Jake.size(); i++){
        cout << "Jake's neighbor: " << i+1 << " " 
        << Jake.at(i).get_name() << endl;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: test_fill_graph
 * purpose: test the funtionality of filling the graph from a list 
 * of artists
 *
 * parameters: none
 * returns: void
 */
void Tests::test_fill_graph()
{
    list<Artist> artists = buildArtists();
    CollabGraph graph; 
    for(Artist a : artists){
        graph.insert_vertex(a);
    }
    graph.add_edges(artists);
    graph.print_graph(cout);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: test_report_path
 * purpose: test the funtionality of filling the report_path from CollabGraph
 * reports the path between two of the test artists, also call print_route
 * to print the result
 * 
 * parameters: none
 * returns: void
 */
void Tests::test_report_path()
{
    list<Artist> artists = buildArtists();
    CollabGraph graph; 
    for(Artist a : artists){
        graph.insert_vertex(a);
    }
    graph.add_edges(artists);
    graph.set_predecessor(artists.back(), artists.front());
    stack<Artist> path1 = graph.report_path(artists.back(), artists.front());
    print_route(path1);  
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: test_report_path
 * purpose: test the funtionality of filling the report_path from CollabGraph
 * reports the path between two of the test artists, also call print_route
 * to print the result. 
 * 
 * parameters: none
 * returns: void
 */
void Tests::print_route(stack<Artist> &artists)
{
    while(artists.size() > 1) {
        Artist start = artists.top();
        artists.pop();
        cout << start.get_name() << " with " << artists.top().get_name() << endl;
   }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: test_situation
 * purpose: test the programs functionality under certain scenarios,
 * the scenarios are in the test_situations folder, each situation has a 
 *  file to load the graph and a commands file to test the sitatuation
 * 
 * parameters: int argc, char *argv[]
 * returns: void
 */
void Tests::test_situation(int argc, char *argv[])
{
    SixDegrees degrees;
    std::filebuf fb1, fb2;
    fb1.open(argv[1], std::ios::in);
    fb2.open(argv[2], std::ios::in);
    std::istream artists(&fb1);
    std::istream commands(&fb2);
    degrees.runGame(artists, commands, cout); 
}

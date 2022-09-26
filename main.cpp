/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 **Purpose:
 *   Entry point into the program, it also validates the correct amount of 
 * input files were given. 
 * 
 * by Gabe Smithline, July 29, 2022
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "SixDegrees.h"
const string CML = "Usage: ./SixDegrees dataFile [commandFile] [outputFile]";
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: check_open
 * purpose: checks if if the commands file or artists file cannot be open
 if it cannot be the program does not execute and an error is thrown
 * parameters: string arg
 *
 * returns: void
 */
int checkOpen(string arg)
{
    std::fstream file(arg);
    if(file.fail()){
        std::cerr << arg << " cannot be opened." << endl; 
        file.close();  
        return 0;
    }
    file.close();
    return 1;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: one_command
 * purpose: if only an artists file is given the game executes with the artists
 file, cin, and cout. 
 * parameters: char *argv[], SixDegrees game
 *
 * returns: void
 */
void one_command(char *argv[], SixDegrees game)
{
    std::filebuf fb;
    fb.open(argv[1], std::ios::in);
    std::istream artists(&fb);
    game.runGame(artists, cin, cout);
    fb.close();
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * function: multiple_command
 * purpose: artists file and commands file the game executes with those and 
 cout. If an artists file, a commands file, and output file are given the 
 game executes with all 3. 
 * parameters: int argc, char *argv[], SixDegrees game
 *
 * returns: void
 */
void multiple_command(int argc, char *argv[], SixDegrees game)
{
    std::filebuf fb1, fb2;
    fb1.open(argv[1], std::ios::in);
    fb2.open(argv[2], std::ios::in);
    std::istream artists(&fb1);
    std::istream commands(&fb2);
    if(argc == 4){
        std::filebuf fb3;
        fb3.open(argv[3], std::ios::out);
        std::ostream output(&fb3);
        game.runGame(artists, commands, output);
        fb1.close();
        fb2.close();
        fb3.close();
    } else {
        game.runGame(artists, commands, cout);
        fb1.close();
        fb2.close();
    }
}

int main(int argc, char *argv[])
{
    if(argc > 4 or 1 >= argc){std::cerr << CML << endl; return 0;}
    SixDegrees game;
    if(argc == 2){
        if( checkOpen(argv[1])!= 0){
            one_command(argv, game);
        } else {
            return 0;
        }
    } else if(argc == 3 or argc == 4){
        if( checkOpen(argv[1]) and checkOpen(argv[2]) != 0){
            multiple_command(argc, argv, game); 
        } else {
            return 0;
        }
    }
    return 0;
}
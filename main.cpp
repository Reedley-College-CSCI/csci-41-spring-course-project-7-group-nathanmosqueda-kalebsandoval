#include "movielist.h"
#include <fstream>
#include<iostream>

using namespace std;

int main() {
    ifstream inputFile;
    inputFile.open("movies.txt");

    if (!inputFile.is_open())
        cout << "File: movies.txt is not found" << endl;


    MovieList movieListSystem;

    movieListSystem.runMovieSystem();


    inputFile.close();

    return 0;
}

#pragma once
#pragma once

#include <string>

using namespace std;

const int MAX_REVIEW_LENGTH = 30;
const int TABLE_SIZE = 8; // Adjust the table size based on your requirements

struct Movie {
    string name;
    int rating;
    double releaseYear;
    string review;
    string genre;
    Movie* next;

    Movie() : rating(0), releaseYear(0), next(nullptr) {}

    Movie(string name, int rating, double releaseYear, string review, string genre)
        : name(name), rating(rating), releaseYear(releaseYear), review(review), genre(genre), next(nullptr) {}
};

class MovieList {
private:
    struct HashNode {
        Movie* data;
        HashNode* next;
    };

    HashNode* hashTable[TABLE_SIZE]; // Hash array

public:
    MovieList();
    ~MovieList();

    void runMovieSystem();
    void addMovie();
    void removeMovie();
    void modifyMovie();
    void displayMovieList();
    void displayMoviesInRange();
    void searchMovie();
    void saveDataToFile();
    void loadDataFromFile();
    string movieRec();

private:
    int hashFunction(const string& key);
    void insertIntoHashTable(Movie* movie);
    void removeFromHashTable(const string& key);
    Movie* searchHashTable(const string& key);
    bool hashTableIsEmpty();
};

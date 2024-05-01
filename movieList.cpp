#include "MovieList.h"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

MovieList::MovieList() {
    // Initialize to null ptr
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
    loadDataFromFile();
}

MovieList::~MovieList() {
   // sets all buckets to empty
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp->data;
            delete temp;
        }
    }
}

void MovieList::runMovieSystem() {
    DWORD start = GetTickCount();
    loadDataFromFile();

    int decision = 0;
    do {
        // Display Menu Options
        cout << "Movie List" << endl;
        cout << "1. Add a movie" << endl;
        cout << "2. Remove a movie" << endl;
        cout << "3. Modify a movie" << endl;
        cout << "4. Display movie list" << endl;
        cout << "5. Display movies in a range of years" << endl;
        cout << "6. Search a movie" << endl;
        cout << "7. Exit" << endl;

        cin >> decision;
        cin.ignore();

        
        switch (decision) {
        case 1:
            addMovie();
            break;
        case 2:
            removeMovie();
            break;
        case 3:
            modifyMovie();
            break;
        case 4:
            displayMovieList();
            break;
        case 5:
            displayMoviesInRange();
            break;
        case 6:
            searchMovie();
            break;
        case 7:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (decision != 7); // Continue the loop until the user chooses to exit

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Elapsed time in runMovieSystem(): " << elapsedTime << " ms" << endl;
}

void MovieList::addMovie() {
    DWORD start = GetTickCount();

    string name, review;
    int rating;
    double releaseYear;

    cout << "Enter name of movie: ";
    getline(cin, name);

    do {
        cout << "Enter rating (1 - 5): ";
        cin >> rating;
        cin.ignore();

        if (rating < 1 || rating > 5) {
            cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
        }
    } while (rating < 1 || rating > 5);

    do {
        cout << "Enter release year: ";
        cin >> releaseYear;
        cin.ignore();

        if (releaseYear < 1900 || releaseYear > 2025) {
            cout << "Invalid release year. Please enter a year between 1900 and 2025." << endl;
        }
    } while (releaseYear < 1900 || releaseYear > 2025);

    do {
        cout << "Enter review (up to " << MAX_REVIEW_LENGTH << " characters): ";
        getline(cin, review);

        if (review.length() > MAX_REVIEW_LENGTH) {
            cout << "Review is too long. Please enter a review with a maximum of " << MAX_REVIEW_LENGTH << " characters." << endl;
        }
    } while (review.length() > MAX_REVIEW_LENGTH);

    Movie* newMovie = new Movie(name, rating, releaseYear, review);
    insertIntoHashTable(newMovie); // Insert the new movie into the hash table
    saveDataToFile(); // Save updated data to file

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time taken to add movie: " << elapsedTime << " ms" << endl;
    cout << "Movie Added successfully." << endl;
}

void MovieList::removeMovie() {
    DWORD start = GetTickCount();
    if (hashTableIsEmpty()) {
        cout << "Movie list is empty." << endl;
        return;
    }

    string searchName;
    cout << "Enter the name of the movie you want to remove: ";
    getline(cin, searchName);

    removeFromHashTable(searchName); // Remove the movie from the hash table
    saveDataToFile(); // Save updated data to file

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time to remove movie: " << elapsedTime << " ms" << endl;
    cout << "Movie removed successfully." << endl;
}

void MovieList::modifyMovie() {
    DWORD start = GetTickCount();
    if (hashTableIsEmpty()) {
        cout << "Movie list is empty." << endl;
        return;
    }

    string searchName;
    cout << "Enter the name of the movie you want to modify: ";
    getline(cin, searchName);

    Movie* movieToModify = searchHashTable(searchName); // Searches for the movie in the table
    if (movieToModify == nullptr) {
        cout << "Movie not found." << endl;
        return;
    }

    cout << "What would you like to modify?" << endl;
    cout << "1. Name" << endl;
    cout << "2. Rating" << endl;
    cout << "3. Release Year" << endl;
    cout << "4. Review" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        cout << "Enter the new name: ";
        getline(cin, movieToModify->name);
        break;
    }
    case 2: {
        cout << "Enter the new rating: ";
        cin >> movieToModify->rating;
        cin.ignore();
        break;
    }
    case 3: {
        cout << "Enter the new release year: ";
        cin >> movieToModify->releaseYear;
        cin.ignore();
        break;
    }
    case 4: {
        cout << "Enter the new review: ";
        getline(cin, movieToModify->review);
        break;
    }
    default:
        cout << "Invalid choice." << endl;
    }

    saveDataToFile(); // Save updated data to file

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time taken to modify movie: " << elapsedTime << " ms" << endl;
    cout << "Movie modified successfully." << endl;
}

void MovieList::displayMovieList() {
    DWORD start = GetTickCount();
    if (hashTableIsEmpty()) {
        cout << "Movie list is empty." << endl;
        return;
    }

    cout << "Movie List:" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            cout << "Name: " << current->data->name << endl;
            cout << "Rating: " << current->data->rating << endl;
            cout << "Release Year: " << current->data->releaseYear << endl;
            cout << "Review: " << current->data->review << endl;
            cout << endl;
            current = current->next;
        }
    }

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time taken to display movie list: " << elapsedTime << " ms" << endl;
}

void MovieList::displayMoviesInRange() {
    DWORD start = GetTickCount();
    if (hashTableIsEmpty()) {
        cout << "Movie list is empty." << endl;
        return;
    }

    int startYear, endYear;
    cout << "Enter the start year: ";
    cin >> startYear;
    cin.ignore();

    cout << "Enter the end year: ";
    cin >> endYear;
    cin.ignore();

    cout << "Movies released between " << startYear << " and " << endYear << ":" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            if (current->data->releaseYear >= startYear && current->data->releaseYear <= endYear) {
                cout << "Name: " << current->data->name << endl;
                cout << "Rating: " << current->data->rating << endl;
                cout << "Release Year: " << current->data->releaseYear << endl;
                cout << "Review: " << current->data->review << endl;
                cout << endl;
            }
            current = current->next;
        }
    }

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time taken to display movies in range: " << elapsedTime << " ms" << endl;
}

void MovieList::searchMovie() {
    DWORD start = GetTickCount();
    if (hashTableIsEmpty()) {
        cout << "Movie list is empty." << endl;
        return;
    }

    string searchName;
    cout << "Enter the name of the movie you want to search for: ";
    getline(cin, searchName);

    Movie* foundMovie = searchHashTable(searchName); 
    if (foundMovie != nullptr) {
        cout << "Movie found:" << endl;
        cout << "Name: " << foundMovie->name << endl;
        cout << "Rating: " << foundMovie->rating << endl;
        cout << "Release Year: " << foundMovie->releaseYear << endl;
        cout << "Review: " << foundMovie->review << endl;
    }
    else {
        cout << "Movie not found." << endl;
    }

    DWORD end = GetTickCount();
    DWORD elapsedTime = end - start;
    cout << "Time taken to search movie: " << elapsedTime << " ms" << endl;
}

void MovieList::saveDataToFile() {
    ofstream outFile("movies.txt");
    if (!outFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != nullptr) {
            outFile << current->data->name << '|' << current->data->rating << '|' << current->data->releaseYear << '|' << current->data->review << endl;
            current = current->next;
        }
    }

    outFile.close();
}

void MovieList::loadDataFromFile() {
    ifstream inputFile("movies.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    // Clear the existing hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }

    string name, review;
    int rating;
    double releaseYear;

    while (getline(inputFile, name, '|')) {
        inputFile >> rating;
        inputFile.ignore();
        inputFile >> releaseYear;
        inputFile.ignore();
        getline(inputFile, review);

        Movie* newMovie = new Movie(name, rating, releaseYear, review);
        insertIntoHashTable(newMovie);
    }

    inputFile.close();
}

int MovieList::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash += c;
    }
    return hash % TABLE_SIZE; // mapping to table size
}

void MovieList::insertIntoHashTable(Movie* movie) {
    int index = hashFunction(movie->name);
    HashNode* newNode = new HashNode;
    newNode->data = movie;
    newNode->next = nullptr;

    if (hashTable[index] == nullptr) {
        hashTable[index] = newNode;
    }
    else {
        HashNode* current = hashTable[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void MovieList::removeFromHashTable(const string& key) {
    int index = hashFunction(key);
    HashNode* current = hashTable[index];
    HashNode* prev = nullptr;

    while (current != nullptr && current->data->name != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Movie not found." << endl;
        return;
    }

    if (prev == nullptr) {
        hashTable[index] = current->next;
    }
    else {
        prev->next = current->next;
    }

    delete current->data;
    delete current;
}

Movie* MovieList::searchHashTable(const string& key) {
    int index = hashFunction(key);
    HashNode* current = hashTable[index];

    while (current != nullptr) {
        if (current->data->name == key) {
            return current->data;
        }
        current = current->next;
    }

    return nullptr; // Movie was not found
}

bool MovieList::hashTableIsEmpty() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != nullptr) {
            return false; // Hash table is not empty
        }
    }
    return true; // Hash table is empty
}


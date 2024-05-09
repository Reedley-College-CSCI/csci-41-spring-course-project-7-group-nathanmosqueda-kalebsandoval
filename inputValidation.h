#pragma once

// InputValidation.h


#include <iostream>
#include <string>

using namespace std;



int getValidRating() {
    int rating;
    do {
        cout << "Enter rating (1 - 5): ";
        cin >> rating;
        cin.ignore();

        if (rating < 1 || rating > 5) {
            cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
        }
    } while (rating < 1 || rating > 5);
    return rating;
}

double getValidReleaseYear() {
    double releaseYear;
    do {
        cout << "Enter release year: ";
        cin >> releaseYear;
        cin.ignore();

        if (releaseYear < 1900 || releaseYear > 2025) {
            cout << "Invalid release year. Please enter a year between 1900 and 2025." << endl;
        }
    } while (releaseYear < 1900 || releaseYear > 2025);
    return releaseYear;
}

string getValidReview() {
    string review;
    do {
        cout << "Enter review (up to " << MAX_REVIEW_LENGTH << " characters): ";
        getline(cin, review);

        if (review.length() > MAX_REVIEW_LENGTH) {
            cout << "Review is too long. Please enter a review with a maximum of " << MAX_REVIEW_LENGTH << " characters." << endl;
        }
    } while (review.length() > MAX_REVIEW_LENGTH);
    return review;
}

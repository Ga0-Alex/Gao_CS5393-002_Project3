#include "SentimentAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Break text into words, converting to lowercase and removing punctuation
vector<string> SentimentAnalyzer::tokenize(const string& text) {
    vector<string> tokens;
    string currentToken;

    for (char c : text) {
        if (isspace(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else if (!ispunct(c)) {
            currentToken += tolower(c);
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

// Train model using labeled dataset
void SentimentAnalyzer::train(const string& trainingFile) {
    ifstream file(trainingFile);
    if (!file.is_open()) {
        throw runtime_error("Could not open training file");
    }

    string line;
    getline(file, line); // Skip CSV header

    // Process each tweet in training file
    while (getline(file, line)) {
        istringstream ss(line);
        string sentiment, id, date, query, user, tweet;

        // Parse CSV fields
        getline(ss, sentiment, ',');
        getline(ss, id, ',');
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);

        // Update word statistics based on sentiment
        bool isPositive = (sentiment == "4");
        auto tokens = tokenize(tweet);
        for (const auto& token : tokens) {
            if (token.length() > 2) {  // Ignore very short words
                wordStats[token].update(isPositive);
            }
        }
    }
}

// Analyze tweets and output sentiment predictions
void SentimentAnalyzer::analyze(const string& testFile, const string& outputFile) {
    ifstream inFile(testFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        throw runtime_error("Could not open files");
    }

    string line;
    getline(inFile, line); // Skip header
    outFile << "Sentiment,id" << endl;

    // Process each tweet in test file
    while (getline(inFile, line)) {
        istringstream ss(line);
        string id, date, query, user, tweet;

        // Parse CSV fields
        getline(ss, id, ',');
        getline(ss, date, ',');
        getline(ss, query, ',');
        getline(ss, user, ',');
        getline(ss, tweet);

        // Calculate average sentiment score for the tweet
        double sentimentScore = 0.0;
        int wordCount = 0;
        auto tokens = tokenize(tweet);

        for (const auto& token : tokens) {
            if (token.length() > 2) {
                auto it = wordStats.find(token);
                if (it != wordStats.end()) {
                    sentimentScore += it->second.getSentimentScore();
                    wordCount++;
                }
            }
        }

        if (wordCount > 0) {
            sentimentScore /= wordCount;
        }

        // Convert score to binary sentiment (4 for positive, 0 for negative)
        int sentiment = (sentimentScore >= 0) ? 4 : 0;
        outFile << sentiment << "," << id << endl;
    }
}

// Calculate accuracy by comparing predictions with truth data
double SentimentAnalyzer::evaluateAccuracy(const string& predictedFile,
                                         const string& truthFile,
                                         const string& accuracyFile) {
    ifstream predicted(predictedFile);
    ifstream truth(truthFile);
    ofstream accuracy(accuracyFile);

    if (!predicted.is_open() || !truth.is_open() || !accuracy.is_open()) {
        throw runtime_error("Could not open one or more files for accuracy evaluation");
    }

    int correct = 0;
    int total = 0;
    string predLine, truthLine;

    // Skip CSV headers
    getline(predicted, predLine);
    getline(truth, truthLine);

    // Track misclassified tweets
    vector<string> errors;

    // Compare predictions with ground truth
    while (getline(predicted, predLine) && getline(truth, truthLine)) {
        istringstream predSS(predLine);
        istringstream truthSS(truthLine);

        string predSentiment, predId, truthSentiment, truthId;

        getline(predSS, predSentiment, ',');
        getline(predSS, predId);
        getline(truthSS, truthSentiment, ',');
        getline(truthSS, truthId);

        // Count correct predictions and log errors
        if (predSentiment == truthSentiment) {
            correct++;
        } else {
            errors.push_back(predSentiment + ", " + truthSentiment + ", " + predId);
        }
        total++;
    }

    // Calculate and output accuracy score
    double accuracyScore = static_cast<double>(correct) / total;

    // Write accuracy and errors to file
    accuracy << fixed << setprecision(3) << accuracyScore << endl;
    for (const auto& error : errors) {
        accuracy << error << endl;
    }

    return accuracyScore;
}

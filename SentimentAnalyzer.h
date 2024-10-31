#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Analyzes sentiment of text using word frequency statistics
class SentimentAnalyzer {
public:
    // Train analyzer with labeled data from CSV file
    void train(const string& trainingFile);

    // Predict sentiment for tweets in test file
    void analyze(const string& testFile, const string& outputFile);

    // Compare predictions against known values and calculate accuracy
    double evaluateAccuracy(const string& predictedFile,
                          const string& truthFile,
                          const string& accuracyFile);

private:
    // Tracks positive/negative occurrences of words
    struct WordStats {
        int positiveCount = 0;    // Number of times word appears in positive context
        int totalCount = 0;       // Total number of word appearances

        // Calculate sentiment score from -1 to 1
        double getSentimentScore() const {
            if (totalCount == 0) return 0.0;
            return (2.0 * positiveCount / totalCount) - 1.0;
        }

        // Update word statistics with new occurrence
        void update(bool isPositive) {
            totalCount++;
            if (isPositive) positiveCount++;
        }
    };

    // Map words to their sentiment statistics
    unordered_map<string, WordStats> wordStats;

    // Split text into individual words
    vector<string> tokenize(const string& text);
};

#endif // SENTIMENTANALYZER_H

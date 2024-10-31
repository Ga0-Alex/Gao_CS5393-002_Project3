#include "SentimentAnalyzer.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    // Check for correct number of command line arguments
    if (argc != 6) {
        cerr << "Usage: " << argv[0]
             << " <train_dataset> <test_dataset> <test_sentiment> <output_file> <accuracy_file>"
             << endl;
        return 1;
    }

    // Print command line
    cout << argv[0];
    for (int i = 1; i < argc; i++) {
        cout << " " << argv[i];
    }
    cout << endl;

    try {
        // Create sentiment analyzer instance
        SentimentAnalyzer analyzer;

        // Start total timing
        auto start_total = high_resolution_clock::now();

        // Train model using labeled dataset
        cout << "Training classifier..." << endl;
        auto start_train = high_resolution_clock::now();
        analyzer.train(argv[1]);
        auto end_train = high_resolution_clock::now();

        // Generate predictions for test data
        cout << "Analyzing test data..." << endl;
        auto start_analyze = high_resolution_clock::now();
        analyzer.analyze(argv[2], argv[4]);
        auto end_analyze = high_resolution_clock::now();

        // Calculate and display accuracy
        cout << "Evaluating accuracy..." << endl;
        auto start_eval = high_resolution_clock::now();
        double accuracy = analyzer.evaluateAccuracy(argv[4], argv[3], argv[5]);
        auto end_eval = high_resolution_clock::now();

        // Calculate timing durations
        auto total_duration = duration_cast<milliseconds>(high_resolution_clock::now() - start_total);
        auto train_duration = duration_cast<milliseconds>(end_train - start_train);
        auto analyze_duration = duration_cast<milliseconds>(end_analyze - start_analyze);
        auto eval_duration = duration_cast<milliseconds>(end_eval - start_eval);

        // Output final results
        cout << "Analysis complete! Accuracy: "
             << fixed << setprecision(3) << accuracy << endl;
        cout << "\nTiming Analysis:" << endl;
        cout << "Training time:   " << train_duration.count() << "ms" << endl;
        cout << "Analysis time:   " << analyze_duration.count() << "ms" << endl;
        cout << "Evaluation time: " << eval_duration.count() << "ms" << endl;
        cout << "Total time:      " << total_duration.count() << "ms" << endl;

    } catch (const exception& e) {
        // Handle any runtime errors
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

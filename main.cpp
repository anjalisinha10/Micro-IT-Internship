
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

// Structure for a Question
struct Question {
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctOption; // 'A', 'B', 'C', 'D'
};

// Function to ask a question
bool askQuestion(const Question& q) {
    cout << "\n" << q.questionText << endl;
    cout << "A. " << q.optionA << endl;
    cout << "B. " << q.optionB << endl;
    cout << "C. " << q.optionC << endl;
    cout << "D. " << q.optionD << endl;
    cout << "Your answer (A/B/C/D): ";

    auto start = chrono::steady_clock::now();

    char answer;
    cin >> answer;
    answer = toupper(answer); // Make case insensitive

    auto end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::seconds>(end - start);

    if (elapsed.count() > 10) { // 10 seconds timer
        cout << "Time's up! You took too long.\n";
        return false;
    }

    if (answer == q.correctOption) {
        cout << "Correct!\n";
        return true;
    } else {
        cout << "Wrong! Correct answer was: " << q.correctOption << "\n";
        return false;
    }
}

// Function to run a quiz
void runQuiz(vector<Question>& questions) {
    int score = 0;
    vector<char> userAnswers;

    cout << "\nStarting quiz... You have 10 seconds per question!\n";

    for (auto& q : questions) {
        bool correct = askQuestion(q);
        if (correct) score++;
        cout << "----------------------\n";
        this_thread::sleep_for(chrono::seconds(1)); // Small delay
    }

    // Show Final Score
    cout << "\nQuiz Completed!\n";
    cout << "Your final score: " << score << "/" << questions.size() << endl;

    double percentage = (double)score / questions.size() * 100;
    cout << "Percentage: " << percentage << "%\n";

    if (percentage >= 90) cout << "Excellent Performance!\n";
    else if (percentage >= 70) cout << "Good Job!\n";
    else cout << "Keep Practicing!\n";
}

// Main Program
int main() {
    vector<Question> mathQuestions = {
        {"What is 5 + 7?", "10", "12", "14", "15", 'B'},
        {"What is 8 * 6?", "42", "46", "48", "50", 'C'},
        {"Square root of 64?", "6", "7", "8", "9", 'C'}
    };

    vector<Question> computerscienceQuestions = {
        {"who is the father of c language?", "Steve Jobs", "James Gosling", "Dennis Ritchie", "Rasmus Lerdorf", 'C'},
        {"All keywords in C are in?", "LowerCase letters", " UpperCase letters", "CamelCase letters", "None of the mentioned", 'A'},
        {"Which of the following cannot be a variable name in C?", "volatile", " true", "friend", " export", 'A'},
        {"What is 5 + 7?", "10", "11", "12", "13", 'C'},
        {"What is short int in C programming?","The basic data type of C", "Qualifier","Short is the qualifier and int is the basic data type","All of the mentioned",'C'}
    };

    cout << "=== Welcome to the Ultimate Quiz App ===\n";
    cout << "Select a Category:\n";
    cout << "1. Math\n";
    cout << "2. Science\n";
    cout << "Enter your choice (1/2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        runQuiz(mathQuestions);
    } else if (choice == 2) {
        runQuiz(computerscienceQuestions);
    } else {
        cout << "Invalid choice. Exiting.\n";
    }

    cout << "\nThank you for playing!\n";

    return 0;
}

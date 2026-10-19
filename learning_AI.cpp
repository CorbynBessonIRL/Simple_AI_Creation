#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

unordered_map<string, string> knowledge;

string normalizeTopic(string topic) {
    // Convert to lowercase
    transform(topic.begin(), topic.end(), topic.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    // Remove spaces at the beginning
    while (!topic.empty() &&
           isspace(static_cast<unsigned char>(topic.front()))) {
        topic.erase(0, 1);
    }

    // Remove spaces and punctuation at the end
    while (!topic.empty() &&
           (isspace(static_cast<unsigned char>(topic.back())) ||
            topic.back() == '?' ||
            topic.back() == '.' ||
            topic.back() == '!')) {
        topic.pop_back();
    }

    // Remove common question phrases
    if (topic.rfind("what is ", 0) == 0) {
        topic.erase(0, 8);
    } else if (topic.rfind("define ", 0) == 0) {
        topic.erase(0, 7);
    }

    // Remove articles
    if (topic.rfind("a ", 0) == 0) {
        topic.erase(0, 2);
    } else if (topic.rfind("an ", 0) == 0) {
        topic.erase(0, 3);
    } else if (topic.rfind("the ", 0) == 0) {
        topic.erase(0, 4);
    }

    return topic;
}

void loadKnowledge() {
    ifstream file("knowledge.txt");
    if (!file) {
        return;
    }
    string topic, answer;

    while (getline(file, topic, '|') && getline(file, answer)) {
        knowledge[topic] = answer;
    }
}

void saveKnowledge() {
    ofstream file("knowledge.txt");

    for (auto item : knowledge) {
        file << item.first << "|" << item.second << endl;
    }
}

void askAI() {
    string topic;
    cout << "What do you want to ask about? ";
    getline(cin, topic);

    if (knowledge.find(topic) != knowledge.end()) {
        cout << "My answer: " << knowledge[topic] << endl;
        while (true){
            cout << "Is this answer correct? (y/n): ";
            string feedback;
            getline(cin, feedback);
            if (feedback == "n") {
              cout << "What is the correct answer? ";
              string correction;
              getline(cin, correction);

              knowledge[topic] = correction;
              saveKnowledge();

              cout << "Correction saved!" << endl;
              break;
            }
            if (feedback == "y"){
                break;
            }
            if (feedback != "n" && feedback != "y"){
              cout << "Please answer with either y or n." << endl;
            }
        }

    } else {
        cout << "I don't know that yet." << endl;
        cout << "Teach me the answer: ";

        string answer;
        getline(cin, answer);

        knowledge[topic] = answer;
        saveKnowledge();

        cout << "I learned something new!" << endl;
    }
}

int main() {
    loadKnowledge();

    while (true) {
        cout << "\n1. Ask or teach\n";
        cout << "2. Quit\n";
        cout << "Choose: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            askAI();
        } else if (choice == "2") {
            break;
        }
    }

    return 0;
}

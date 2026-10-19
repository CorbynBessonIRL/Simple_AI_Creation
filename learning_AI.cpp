#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

unordered_map<string, string> knowledge;

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

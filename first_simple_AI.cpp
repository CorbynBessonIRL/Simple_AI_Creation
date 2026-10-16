#include <iostream>
#include <string>
using namespace std;

struct Node{
    string text;
    Node* yes;
    Node* no;
};

bool isLeaf(Node *p){
    return p->yes == nullptr && p -> no == nullptr;
}

void runAI(Node* p){
    if (isLeaf(p)){
        cout<<"Feedback: "<<p->text<<endl;
        return;
    }

    char answer;
    cout << p->text << " (y/n): ";
    cin >> answer;

    if (answer == 'y' || answer == 'Y'){
        runAI(p->yes);
    }else if(answer == 'n'|| answer == 'N'){
        runAI(p->no);
    }else{
        cout << "Please enter y or n." << endl;
        runAI(p);
    }
}

int main() {
    Node good = {
        "Great! Try writing a linked-list insertion function WOW.",
        nullptr, nullptr
    };

    Node review = {
        "Review how pointers connect nodes, then try again. again again",
        nullptr, nullptr
    };

    Node root = {
        "Do you understand pointers? ",
        &good, &review
    };

    runAI(&root);
}


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
        "Great! We'll talk about the concept called \"Node\" in the next session!",
        nullptr, nullptr
    };

    Node review = {
        "Review what pointers point to, then try again.",
        nullptr, nullptr
    };

    Node root = {
        "Do you understand how pointers work? ",
        &good, &review
    };

    runAI(&root);
}


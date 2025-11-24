import <iostream>;

import Student;

using namespace std;

int main(){
    Student Blue;
    Student Red;
    Student Orange;
    Student Yellow;

    Student * turnOrder[4] = {Blue, Red, Orange, Yellow};

    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << // to_string(students[i]) 
        cout << ", where do you want to complete an Assignment?";
        int intersection;
        cin >> intersection;
        //studentcolor.accquire(intersection);
    }
    // only one direction right now, can do recursion but would need to make a function?
    // is that ok in main, (design wise)
    
    // printBoard();


    // start turn
    for (int i = 0; i < turnOrder.length(); ++i){
        cout << "Student " << //to_string(students[i]) << "'s turn.";
    }

}

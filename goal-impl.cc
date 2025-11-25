module Goal;

import <string>;
import <vector>;
import ISubject;
using namespace std;

Goal::Goal(int location): 

void Goal::addAdjacentcourse_criterion(const vector<int> &v) { adjacent_course_criterion = v; }
void Goal::addAdjacentgoal(const vector<int> &e) { adjacent_goals = e; }

bool Goal::adjacent_goal_check(ISubject * location) {
    while (auto it = adjacent_goals.begin(); it != adjacent_goals.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}
bool Goal::adjacent_criteria_check(ISubject * location) {
    while (auto it = adjacent_course_criterion.begin(); it != adjacent_course_criterion.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

string Goal::getnum() {
    if (owner != ' ') {
        return owner + "A";
    }
    
    if (number < 10) {
        return " " + to_string(number);
    
    }
    return to_string(number);
}
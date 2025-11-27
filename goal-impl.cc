module Goal;

import <string>;
import <vector>;
import ISubject;
import Resource;

// CONSTRUCTOR
Goal::Goal(int location): ISubject(location), owner(' ') {}

// GET METHODS
std::string Goal::getnum() const {
    if (owner) {
        return owner->get_name()[0] + "A";
    }

    // else no owner
    if (location < 10) {
        return " " + std::to_string(location);
    
    }
    return std::to_string(location);
}


// Subscription Method
void Goal::acquire(IObserver* student){
    // set owner to student pointer
    owner = student;
}

// ADJACENCY LOGIC METHODS: subject to change
bool Goal::adjacent_goal_check(int location) {
    for (auto it = adjacent_goals.begin(); it != adjacent_goals.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

bool Goal::adjacent_criteria_check(int location) {
    for (auto it = adjacent_course_criterion.begin(); it != adjacent_course_criterion.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

void Goal::set_adjacent_criteria(const std::vector<int> & criteria) { 
    adjacent_criteria = criteria; 
}

void Goal::set_adjacent_goals(const std::vector<int> & goals) { 
    adjacent_goals = goals; 
}

// BUY LOGIC METHODS:

// checks for ownership used by student
bool Goal::owned() const{
    return owner != nullptr;
}

bool adjacent(vector<int> &criteria, vector<int> &goals) const{
    break;
}

// returns the cost in Resource
Resource & Goal::cost() const {
    return cost;
}

// Save method for saves
std::string get_save_string() const{
    return location;
}

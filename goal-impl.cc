module Goal;

import <string>;
import <vector>;
import ISubject;
import Resource;

// CONSTRUCTOR
Goal::Goal(int location): ISubject(location), owner(' ') {}

// GET METHODS
std::string Goal::getnum() const {
    if (owner != ' ') {
        return owner + "A";
    }
    
    if (location < 10) {
        return " " + std::to_string(location);
    
    }
    return std::to_string(location);
}


char Goal::get_owner(){
    if(owner){
        return owner->get_name()[0];
    } else {
        return ' ';
    }
}

// Subscription Method
void Goal::acquire(IObserver* student){
    return;
}

// ADJACENCY LOGIC METHODS:
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

bool Goal::owned(){
    return owner != nullptr;
}


Resource Goal::cost(){
    Resource goalCost = {0, 0, 0, 1, 1};
    return goalCost;
}

// Save method for saves
std::string get_save_string(){
    return location;
}

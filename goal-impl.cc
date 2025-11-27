module Goal;

import <string>;
import <vector>;
import Resource;
import IObserver;
import ISubject;

// DECLARING THE CONSTANT
export const Resource Goal::resource_cost{0, 0, 0, 1, 1};

// CONSTRUCTOR
Goal::Goal(int location): ISubject(location), owner_char(' ') {}

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
bool Goal::adjacent_goal_check(int location) const {
    for (auto it = adjacent_goals.begin(); it != adjacent_goals.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

bool Goal::adjacent_criteria_check(int location) const {
    for (auto it = adjacent_criteria.begin(); it != adjacent_criteria.end(); ++it) {
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

// returns the eligibility of the goal based on adjacent goals/criteria
bool adjacent_check(std::vector<int> &criteria, std::vector<int> &goals) const{
    // WIP
    return false;
}

// returns the cost in Resource
const Resource & Goal::cost() const {
    return resource_cost;
}

// Save method for saves
std::string Goal::get_save_string() const{
    return location;
}

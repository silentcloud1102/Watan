module Criteria;

import <string>;
import <sstream>;
import <vector>;
import ISubject;

// CONSTANTS
const char Criteria::level_chars[3] = {'A','M','E'};
const Resource Criteria::level_costs[3] = {
    Resource {1, 1, 1, 0, 1},
    Resource {0, 0, 2, 3, 0},
    Resource {3, 2, 2, 1, 2}
};

// CONSTRUCTOR
Criteria::Criteria(int location, int level):
    ISubject{location}, 
    upgradeLevel{level} {}

// GET METHODS: printing

// returns a string representing the correct representation for printing
// on the board. Different representation when owned.
std::string Criteria::get_num() const {
    // note: we will not use stringstream here because it is a simple concatenation
    // stringstream will be used when there are multiple fields to loop through

    // if owner is not nullptr, owned. Return with owner char and current level
    if (owner) {
        return owner->get_name[0] + levels[upgradeLevel - 1];
    }

    // else, not owned. if the location is not two digits, add a space in front
    if (location < 10) {
      return " " + std::to_string(location);
    }

    // return location as a string otherwise
    return std::to_string(location);
}


int Criteria::get_level() const{
    return upgradeLevel;
}

// BUY LOGIC METHODS: for use post save loading

// boolean value representing whether the adjacency requirements are achieved
// indicates whether it is valid to attempt to buy
bool Criteria::adjacent() const{
    // check that there is no adjacent Criteria already owned
    // check that there is an adjacent owned Goal
    return false;
}

// boolean value representing whether an owner is already defined
// indicates whether it is valid to attempt to buy
bool Criteria::owned() const{
    return owner != nullptr;
}


// UPGRADE LOGIC METHODS:

// returns the upgrade cost of the current level as a resource
Resource & Criteria::upgradeCost() const{
    if(!owned()){
        return level_costs[0]; // cost to "upgrade" to level 1
    } else if(max_level()){
        return level_costs[upgradeLevel - 1];
    } else{
        return level_costs[upgradeLevel];
    }
}

// boolean value of whether the max level has been achieved
// indicates whether it is valid to upgrade the Criteria
bool Criteria::max_level() const{
    return get_level() == 3;
}

// simply upgrades without any major logic
void Criteria::upgrade() {
    if(upgradeLevel < 3){
        upgradeLevel++;
    }
    return;
}


// Save string production, used by get_save_string of containing classes
std::string Criteria::get_save_string() const{
    std::ostringstream oss;
    oss << location << ' ' << get_level();
    return oss.str();
}


// ADJACENCY LOGIC METHODS: utilized by Criteria::adjacent()


bool Criteria::adjacent_goal_check(int location) {
    for (auto it = adjacent_goals.begin(); it != adjacent_goals.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

bool Criteria::adjacent_criteria_check(int location) {
    for (auto it = adjacent_course_criterion.begin(); it != adjacent_course_criterion.end(); ++it) {
        if (*it == location) {
            return true;
        }
    }
    return false;
}

void Criteria::addAdjacentcourse_criterion(const std::vector<int> &v) { 
    adjacent_course_criterion = v; 
}

void Criteria::addAdjacentgoal(const std::vector<int> &e) { 
    adjacent_goals = e; 
}


void Criteria::newResource(string r) const {
    Resource rchange{r, upgradeLevel};
    if (owned()) {
        owner->resourceNotify(rchange);
    }
}

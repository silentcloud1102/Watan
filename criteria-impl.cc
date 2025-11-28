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
        return owner->get_name()[0] + std::to_string(upgradeLevel - 1);
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
bool Criteria::adjacent_check(std::vector<int> &criteria, std::vector<int> &goals) const{
    // check that there is no adjacent Criteria already owned
    for (auto adj = adjacent_criteria.begin(); adj != adjacent_criteria.end(); ++adj) {
        for(auto other = criteria.begin(); other != criteria.end(); ++other){
            if(*other == *adj){
                // if there is an adjacent completed criteria, cannot complete
                return false;
            }
        }
    }

    for (auto adj = adjacent_goals.begin(); adj != adjacent_goals.end(); ++adj) {
        for(auto other = goals.begin(); other != goals.end(); ++other){
            if(*other == *adj){
                // if there is an adjacent completed goal, and no adjacent criteria
                // then we can complete this criteria.
                return true;
            }
        }
    }

    // no adjacencies.
    return false;
}

// boolean value representing whether an owner is already defined
// indicates whether it is valid to attempt to buy
bool Criteria::owned() const{
    return owner != nullptr;
}

// UPGRADE LOGIC METHODS:

// returns the upgrade cost of the current level as a resource
const Resource & Criteria::upgradeCost() const{
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


// adding the adjacent course criterion
void Criteria::set_adjacent_criteria(const std::vector<int> &criteria) {
    adjacent_criteria = criteria;
}

// adding the adjacent goals
void Criteria::set_adjacent_goals(const std::vector<int> &goals) { 
    adjacent_goals = goals;
}

// Notify Observer
void Criteria::newResource(std::string r) const {
    Resource rchange{r, upgradeLevel};
    if (owned()) {
        owner->resource_notify(rchange);
    }
}

void Criteria::acquire(IObserver* student) {
    owner = student;
}
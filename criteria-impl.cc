module Criteria;

import <string>;
import <sstream>;
import <vector>;
import ISubject;

const char Criteria::level_chars[3] = {'A','M','E'};
const Resource Criteria::level_costs[3] = {
    Resource {1, 1, 1, 0, 1},
    Resource {0, 0, 2, 3, 0},
    Resource {3, 2, 2, 1, 2}
};

// constructor
Criteria::Criteria(int location, int level):
    ISubject{location}, 
    upgradeLevel{level} {}

std::string Criteria::get_num() {
    if (get_owner() != ' ') {
        return get_owner() + levels[upgradeLevel - 1];
    }

    if (location < 10) {
      return " " + std::to_string(location);
    }
    return std::to_string(location);
}


Resource Criteria::upgradeCost(){
    if(!owned()){
        return level_costs[0]; // cost to "upgrade" to level 1
    } else if(max_level()){
        return level_costs[upgradeLevel - 1];
    } else{
        return level_costs[upgradeLevel];
    }
}

void Criteria::upgrade() {
    if(upgradeLevel < 3){
        upgradeLevel++;
    }
    return;
}

char Criteria::get_owner(){
    if(owner){
        return owner->get_name()[0];
    } else {
        return ' ';
    }
}

bool Criteria::adjacent(){
    // fill in later: check whether there are adjacent values.
    return false;
}

bool Criteria::owned(){
    return owner != nullptr;
}

int Criteria::get_level() const{
    return upgradeLevel;
}

bool Criteria::max_level() const{
    return get_level() == 3;
}

std::string Criteria::get_save_string() const{
    std::ostringstream oss;
    oss << location << ' ' << get_level();
    return oss.str();
}


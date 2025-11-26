module Criteria;

import <string>;
import <sstream>;
import <vector>;
import ISubject;

const char Criteria::level_chars = = {'A','M','E'};

// constructor
Criteria::Criteria(int location):
    ISubject{location}, 
    upgradeLevel{1} {}

std::string Criteria::get_num() {
    if (get_owner() != ' ') {
        return get_owner() + levels[upgradeLevel - 1];
    }

    if (location < 10) {
      return " " + std::to_string(location);
    }
    return std::to_string(location);
}

void Criteria::upgrade() {
    if ()
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


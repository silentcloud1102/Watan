module Goal;

import <string>;
import <vector>;
import ISubject;
import Resource;

Goal::Goal(int location): ISubject(location), owner(' ') {}

std::string Goal::getnum() const {
    if (owner != ' ') {
        return owner + "A";
    }
    
    if (location < 10) {
        return " " + std::to_string(location);
    
    }
    return std::to_string(location);
}

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

void Goal::addAdjacentcourse_criterion(const std::vector<int> &v) { adjacent_course_criterion = v; }
void Goal::addAdjacentgoal(const std::vector<int> &e) { adjacent_goals = e; }

bool Goal::owned(){
    return owner != nullptr;
}

char Goal::get_owner(){
    if(owner){
        return owner->get_name()[0];
    } else {
        return ' ';
    }
}

Resource Goal::cost(){
    Resource goalCost = {0, 0, 0, 1, 1};
    return goalCost;
}

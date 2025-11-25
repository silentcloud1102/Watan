module Goal;

import <string>;
import <vector>;
import ISubject;

Goal::Goal(int location): ISubject(location), owner(' ') {}

void Goal::addAdjacentcourse_criterion(const std::vector<int> &v) { adjacent_course_criterion = v; }
void Goal::addAdjacentgoal(const std::vector<int> &e) { adjacent_goals = e; }

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

std::string Goal::getnum() const {
    if (owner != ' ') {
        return owner + "A";
    }
    
    if (number < 10) {
        return " " + std::to_string(number);
    
    }
    return std::to_string(number);
}
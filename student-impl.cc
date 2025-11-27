module Student;

import <vector>;
import <string>;
import <sstream>;
import <iostream;

import Board;
import ISubject;
import Resource;
import IObserver

Student(const std::string colour, Board * board): 
    name{colour}, board{board} {}

std::string get_name() {
    return name;
}

// set_up boolean to override checks: useful for setting up from saves
void buy_criteria(int id, bool set_up){
    Criteria * target = board->getCriteria(id);
    Resource & cost = target->upgradeCost();

    bool affordable = can_afford(cost);
    bool adjacent = target->adjacent(criteria, goals);
    bool owned = target->owned();

    if(!set_up){
        if (affordable && adjacent && !owned) {
            held_resources -= cost;
        } else if (!adjacent){
            throw "This criteria is not ellegible to be bought.";
        } else if (owned){
            throw "This criteria is already owned.";
        } else if (!affordable){
            throw "You do not have enough resources.";
        }
    }

    // if no exceptions were thrown or set_up is true, then add to list.
    criteria.push_back(id);
    ++criteria_count;
    target->acquire(this);
    return;
}

void buy_goal(int id, bool set_up){
    Goal * target = board->getGoal(id);
    Resource & cost = target->cost();

    bool affordable = can_afford(cost);
    bool adjacent = target->adjacent(criteria, goals);
    bool owned = target->owned();

    if(!set_up){
        if(affordable && adjacent && !owned){
            
            held_resources -= cost;
            
        } else if (!adjacent){
            throw "This goal is not adjacent to any of your goals and criterion.";
        } else if (owned){
            throw "This goal is already owned.";
        } else if (!affordable){
            throw "You do not have enough resources.";
        }
    }
    Goal->acquire(this);
    goals.push_back(id);
}

// will not be run at set-up, no need to include a set-up override
void upgrade_criteria(int id) {
    bool found = false;
    for(auto val: criteria){
        if (val == id) {
            found = true;
            break;
        }
    }

    if(!found){
        throw "This criteria is not owned by student.";
    }

    Criteria * target = board->getCriteria(id);
    Resource & cost = target->upgradeCost();

    if(can_afford(cost) && !target->max_level()){
        held_resources -= cost;
        target->upgrade();
    } else if (target->max_level()){
        throw "This criteria is already max level.";
    } else if (!can_afford(cost)){
        throw "The student does not have enough resources.";
    } 

}

bool can_afford(const Resource & query) const {
    return held_resources >= query;
}

// main method to modify resources, inherited from IObserver
void resource_notify(Resource rchange) {
    held_resources += rchange;
}

// save logic
std::string get_save_string() const {
    std::ostringstream oss;
    oss << held_resources.get_save_string();

    oss << " g";
    for(auto it = goals.begin(); it != goals.end(); it++){
        Goal * target = board->getGoal(*it);
        oss << ' ' << target->get_save_string();
    }

    oss << " c";
    for(auto it = criteria.begin(); it != criteria.end(); it++){
        Criteria * target = board->getCriteria(*it);
        oss << ' ' << target->get_save_string();
    }

    // turns the stringstream buffer to string
    return oss.str();
    // consider just passing oss instead of returning string
}

void read_save_string(std::string save_data) {
    // placeholder for now: add for construction from save strings
    istringstream iss {save_data};
    int read;
    int resources[5];
    for (int i = 0; i < 5; ++i){
        iss >> read;
        resources[i] = read;
    }
    Resource r = {resources[0], resources[1], resources[2], resources[3], resources[4]};
    this->resource_notify(r);

    iss.ignore();
    while (iss >> read){
        this->buy_goal(read, true);
    }
    iss.clear();
    iss.ignore();
    while (iss >> read){
        this->buy_criteia(read, true);
    }
    
}

void print_status(){
    cout << this->name << " has ";
    cout << this->critiera.size() << " course criteria,";
    cout << this->held_resources.print_resource_status() << endl;
}

void trade(Student * colour, string give_r, string take_r){
    Resource r1 = Resource(give_r, 1);
    Resource r2 = Resource(take_r, 1);

    colour->held_resources += r2;
    this->held_resources -= r1;
}

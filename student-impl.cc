module Student;

import <iostream>;
import <sstream>;
import <vector>;
import <string>;
import <iostream>;
import <stdexcept>;

import Resource;
import Criteria;
import Goal;
import IObserver;
import ISubject;
import Board;

Student::Student(const std::string & colour, Board * board): 
    name{colour}, board{board} {}


// Board interaction methods: includes logic override
// set_up boolean to override checks: useful for setting up from saves
void Student::buy_criteria(int id, bool set_up){
    Criteria * target = board->get_criteria(id);
    const Resource & cost = target->upgrade_cost();

    // save results for less repetition
    bool affordable = can_afford(cost);
    bool adjacent = target->adjacent_check(criteria, goals);
    bool owned = target->owned();
    
    // problematic regardless of if setup or not...
    if (owned){
        // if from save file, no need to catch: error in save file...
        // if from setup of game, must be caught.
        throw std::runtime_error("This criteria is already owned, cannot have two owners!");
    } else if (!adjacent){
        throw std::runtime_error("This criteria is not elligible to be bought.");
    }

    if(!set_up){
        if (affordable) {
            held_resources -= cost;
        } else if (!affordable){
            throw std::runtime_error("You do not have enough resources.");
        }
    } 

    // if no exceptions were thrown or set_up is true, then add to list.
    criteria.push_back(id);
    target->acquire(this);
    return;
}

// buy method for goal, again providing a set_up switch
void Student::buy_goal(int id, bool set_up){
    Goal * target = board->get_goal(id);
    const Resource & cost = target->cost();

    // save results for less repetition
    bool affordable = can_afford(cost);
    bool adjacent = target->adjacent_check(criteria, goals);
    bool owned = target->owned();
    
    if (owned){
        throw std::runtime_error("This goal is already owned, cannot have two owners!");
    }

    if(!set_up){
        if(affordable && adjacent){
            
            held_resources -= cost;
            
        } else if (!adjacent){
            throw std::runtime_error("This goal is not adjacent to any of your goals and criterion.");
        } else if (!affordable){
            throw std::runtime_error("You do not have enough resources.");
        }
    }
    target->acquire(this);
    goals.push_back(id);
}

// will not be run at set-up, no need to include a set-up override
void Student::upgrade_criteria(int id) {
    bool found = false;
    for(auto val: criteria){
        if (val == id) {
            found = true;
            break;
        }
    }

    if(!found){
        throw std::runtime_error("This criteria is not owned by student.");
    }

    Criteria * target = board->get_criteria(id);
    const Resource & cost = target->upgrade_cost();

    // save results 
    bool affordable = can_afford(cost);
    bool maxed = target->max_level();

    if(affordable && !maxed){
        held_resources -= cost;
        target->upgrade();
    } else if (maxed){
        throw std::runtime_error("This criteria is already max level.");
    } else if (!affordable){
        throw std::runtime_error("The student does not have enough resources.");
    } 

}

// boolean check against held_resources, used for trades and upgrades/purchases
bool Student::can_afford(const Resource & query) const {
    return held_resources >= query;
}

// trades method, no logic to check whether trade is valid: assumed
void Student::trade(Student * colour, std::string give_r, std::string take_r){
    // by default we trade 1 of each resource
    Resource r1 = Resource(give_r, 1);
    Resource r2 = Resource(take_r, 1);

    colour->held_resources += r1;
    this->held_resources += r2;
    this->held_resources -= r1;
    colour->held_resources -= r2;
}

// main method to modify resources, inherited from IObserver (Notify)
void Student::resource_notify(Resource rchange) {
    held_resources += rchange;
}

// get name for use by owned objects
std::string Student::get_name() {
    return name;
}

// get number of criteria for use in checking for win conditions
int Student::get_criteria_count() const {
    return criteria.size();
}

// Geese methods: beware
// gets a vector of resources, to be used for geese operations
std::vector<int> Student::resource_vector() const {
    return held_resources.to_vector();
}

Resource Student::get_resource() const {
    return held_resources;
}

// number of resources to know when to tax collect.
int Student::resource_count() const{
    return held_resources.count();
}

// it's like resource_notify but in reverse!
void Student::goosed(Resource rchange){
    held_resources -= rchange;
}

// save methods:

// produces a string for calling method to use
std::string Student::get_save_string() const {
    std::ostringstream oss;
    oss << held_resources.get_save_string();

    oss << " g";

    // list all owned goals
    for(auto it = goals.begin(); it != goals.end(); it++){
        Goal * target = board->get_goal(*it);
        oss << ' ' << target->get_save_string();
    }

    oss << " c";

    // list all owned criteria, note we need to get_criteria because we need their level
    for(auto it = criteria.begin(); it != criteria.end(); it++){
        Criteria * target = board->get_criteria(*it);
        oss << ' ' << target->get_save_string();
    }

    // turns the stringstream buffer to string
    return oss.str();
    // consider just passing oss instead of returning string
}

// set student values based on save string
void Student::read_save_string(std::string save_data) {
    // string stream using given data (one line of save file)
    // we assume that the given save string is properly formatted
    std::istringstream iss {save_data};

    // read in integers
    int read;
    std::string garbage;
    int resources[5];
    for (int i = 0; i < 5; ++i){
        iss >> read;
        resources[i] = read;
    }

    // move assignment works by default since all fields are primitives, (yay)
    held_resources = Resource{resources[0], resources[1], resources[2], resources[3], resources[4]};

    // read in g
    iss >> garbage;
    while (iss >> read){
        this->buy_goal(read, true);
    }
    iss.clear();
    // read in c
    iss >> garbage;
    while (iss >> read){
        this->buy_criteria(read, true);
    }
}


// equality operator
bool Student::operator==(std::string other) const{
    return other == name;
}

// output operator for student status
std::ostream &operator<<(std::ostream& os, Student &student){
    os << student.name << " has " << student.get_criteria_count() << " course criteria, ";
    os << student.held_resources;
    return os;
}

// output method for student completions
std::string Student::completions() const {
    std::ostreamstring oss;
    oss << name << " has completed:" << std::endl;
    for(auto it = criteria.begin(); it != criteria.end(); it++){
        Criteria * target = board->get_criteria(*it);
        oss << target->get_save_string() << std::endl;
    }

    return oss.str();
}

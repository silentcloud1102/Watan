module Student;
import <sstream>;
import Board;

explicit Student(const std::string colour, Board * board): 
    colour{colour}, board{board} {}

std::string get_colour() const{
    return colour;
}

// set_up boolean to override checks: useful for setting up from saves
void buy_criteria(int id, bool set_up){
    Criteria * target = board->getGoal(id);
}

void buy_goal(int id, bool set_up){
    Goal * target = board->getGoal(id);
}

void upgrade_criteria(int id){
    Criteria * target = board->getCriteria(id);
    Resource cost = target->upgradeCost();


    if(can_afford(cost) && !target->max_level()){
        held_resources -= cost;
        criteria.push_back(id);
        target->acquire(this);
    } else if (target->max_level()){
        throw "Criteria is already max level.";
    } else if (!can_afford(cost)){
        throw "You do not have enough resources.";
    } 

}

bool can_afford(const Resource & query){
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
    // placeholder for now: add for construction from save files
    return;
}
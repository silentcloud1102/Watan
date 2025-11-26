module Student;
import Board;

explicit Student(const std::string colour, Board * board): 
    colour{colour}, board{board} {}

std::string get_colour() const{
    return colour;
}

void buy_criteria(int id){

}
void buy_goal(int id);
void upgrade_criteria(int id);

bool can_afford(Resource query){
    return held_resources >= query;
}

// main method to modify resources, inherited from IObserver
void resource_notify(Resource rchange) {
    held_resources += rchange;
}

// save logic
std::string get_save_string() const {

}
std::string read_save_string(std::string save_data);
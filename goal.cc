export module Goal;

import <string>;
import <vector>;
import ISubject;

export class Goal : public ISubject {
  int index;
  std::string owner;
  vector<int> adjacent_course_criterion;
  vector<int> adjacent_goals;
  public:
    explicit Goal(int location): 
    string getnum() const {
      if (owner != "") {
          return owner;
        }

          if (number < 10) {
          return " " + to_string(number);
          }
          return to_string(number);
    }
    void addAdjacentcourse_criterion(const vector<int> &v) { adjacent_course_criterion = v; }
    void addAdjacentgoal(const vector<int> &e) { adjacent_goals = e; }
};

class goal {
  public:
    int number;
    string owner;
    
    
      goal(int num, string str) : number(num), owner(str) {}
      
};
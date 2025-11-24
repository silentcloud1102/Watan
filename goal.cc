export module Goal;

import ISubject;

export class Goal : public ISubject {
    vector<int> adjacent_course_criterion;
    vector<int> adjacent_goals;

    Goal(int location): 
    string getnum() const {
      if (owner != "") {
          return owner;
        }

          if (number < 10) {
          return " " + to_string(number);
          }
          return to_string(number);
    }
};

class goal {
  public:
    int number;
    string owner;
    
    
      goal(int num, string str) : number(num), owner(str) {}
      void addAdjacentcourse_criterion(const vector<int> &v) { adjacent_course_criterion = v; }
      void addAdjacentgoal(const vector<int> &e) { adjacent_goals = e; }
};
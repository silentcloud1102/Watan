export module Goal;

import ISubject;

export class Goal : public ISubject {
    Goal(int location): 
};

class goal {
  public:
    int number;
    string owner;
    vector<int> adjacent_course_criterion;
    vector<int> adjacent_goals;
    
      goal(int num, string str) : number(num), owner(str) {}
      void addAdjacentcourse_criterion(const vector<int> &v) { adjacent_course_criterion = v; }
      void addAdjacentgoal(const vector<int> &e) { adjacent_goals = e; }
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
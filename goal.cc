export module Goal;

import <string>;
import <vector>;
import ISubject;

export class Goal : public ISubject {
  int index;
  char owner;
  vector<int> adjacent_course_criterion;
  vector<int> adjacent_goals;
  public:
    explicit Goal(int location): 
    std::string getnum() const;
    bool adjacent_goal_check(ISubject * location) const;
    bool adjacent_criteria_check(ISubject * location) const;
    void addAdjacentcourse_criterion(const vector<int> &v);
    void addAdjacentgoal(const vector<int> &e);
};

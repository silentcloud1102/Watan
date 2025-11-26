export module Goal;

import <string>;
import <vector>;
import ISubject;

export class Goal : public ISubject {
  char owner;
  vector<int> adjacent_course_criterion;
  vector<int> adjacent_goals;
  public:
    explicit Goal(int location); 

    // Printing method
    std::string getnum() const;

    // Adjacency Methods
    bool adjacent_goal_check(int location) const;
    bool adjacent_criteria_check(int location) const;
    void addAdjacentcourse_criterion(const vector<int> &v);
    void addAdjacentgoal(const vector<int> &e);
};

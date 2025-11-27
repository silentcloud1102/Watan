export module Goal;

import <string>;
import <vector>;
import ISubject;

export class Goal : public ISubject {
  char owner;

  static const Resource cost = {0, 0, 0, 1, 1};

  vector<int> adjacent_criteria;
  vector<int> adjacent_goals;
  public:
    explicit Goal(int location); 

    // "subscription" method
    void acquire(IObserver* student) override;
   
    // Printing method
    std::string getnum() const;

    // Buy logic methods:
    Resource & cost() const;
    bool owned() const;
    bool adjacent(vector<int> &criteria, vector<int> &goals) const;

    // Adjacency Methods
    bool adjacent_goal_check(int location) const;
    bool adjacent_criteria_check(int location) const;
    void set_adjacent_criteria(const vector<int> & criteria);
    void set_adjacent_goals(const vector<int> & goals);

    // Saving methods
    std::string get_save_string() const;
};

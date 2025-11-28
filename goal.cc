export module Goal;

import <string>;
import <vector>;
import Resource;
import IObserver;
import ISubject;

export class Goal : public ISubject {
  static const Resource resource_cost;

  std::vector<int> adjacent_criteria;
  std::vector<int> adjacent_goals;
  public:
    explicit Goal(int location); 

    // "subscription" method
    void acquire(IObserver* student) override;
   
    // Printing method
    std::string getnum() const;

    // Buy logic methods:
    const Resource & cost() const;
    bool owned() const;
    bool adjacent_check(std::vector<int> &criteria, std::vector<int> &goals) const;

    // Adjacency Methods
    void set_adjacent_criteria(const std::vector<int> & criteria);
    void set_adjacent_goals(const std::vector<int> & goals);

    // Saving methods
    std::string get_save_string() const;
};

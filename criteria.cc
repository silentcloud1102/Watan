export module Criteria;

import <string>;
import <vector>;
import Resource;
import IObserver;
import ISubject;

export class Criteria : public ISubject {
    // levels
    static const char level_chars[3];
    static const Resource level_costs[3];
  
    int upgradeLevel;
    vector<int> adjacent_criteria;
    vector<int> adjacent_goals;

    public:
      explicit Criteria(int location, int level = 1);

      // "subscription" method
      void acquire(IObserver* student) override;

      // Notification method
      void newResource(std::string r) const;
      
      // Printing methods
      std::string get_num() const;
      int get_level() const;

      // Checks for buying
      bool max_level() const;
<<<<<<< HEAD
      bool adjacent_check(vector<int> &criteria, vector<int> &goals) const;
=======
      bool adjacent(std::vector<int> &criteria, std::vector<int> &goals) const;
>>>>>>> eccd77ef972c37fecc7f920b8890402968f56dc4
      bool owned() const;

      // Upgrade logic
      const Resource & upgradeCost() const;
      void upgrade();

      // save method
      std::string get_save_string() const;
      
      void addAdjacentgoal(const std::vector<int> &e);
      void addAdjacentcourse_criterion(ISubject* criteria);
      bool adjacent_criteria_check(int location);
      bool adjacent_goal_check(int location);
};

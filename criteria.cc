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
    std::vector<ISubject *> adjacent_course_criterion;
    std::vector<int> adjacent_goals;

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
      bool adjacent(std::vector<int> &criteria, std::vector<int> &goals) const;
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

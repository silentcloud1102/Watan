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
    std::vector<int> adjacent_criteria;
    std::vector<int> adjacent_goals;

    public:
      explicit Criteria(int location, int level = 1);

      // "subscription" method
      void acquire(IObserver* student) override;

      // Notification method
      void new_resource(std::string r) const;
      
      // Printing methods
      std::string get_num(bool format = true) const;
      int get_level() const;

      // Checks for buying
      bool max_level() const;
      bool criteria_check(std::vector<int> &criteria) const;
      bool goal_check(std::vector<int> &goals) const;
      bool owned() const;

      // Upgrade logic
      const Resource & upgrade_cost() const;
      void upgrade();

      // save method
      std::string get_save_string() const;
      
      // configuration methods to be used by Board
      void set_adjacent_goals(const std::vector<int> &goals);
      void set_adjacent_criteria(const std::vector<int> &criteria);
      std::vector<int> get_adjacent_criteria() const;
};

export module Criteria;

import <string>;
import <vector>;
import Resource;
import IObserver;
import ISubject;

export class Criteria : public ISubject {
    // levels
    static const std::string level_str[3];
    static const Resource level_costs[3];
  
    bool colour;
    int upgradeLevel;
    std::vector<int> adjacent_criteria;
    std::vector<int> adjacent_goals;

    public:
      explicit Criteria(int location, bool colour);

      // "subscription" method
      void acquire(IObserver* student) override;

      // Notification method
      void new_resource(std::string r) const;
      
      // Printing methods
      std::string get_num(bool format = true) const;
      std::string get_completion() const;
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

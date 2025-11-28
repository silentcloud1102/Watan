export module Criteria;

import <string>;
import <vector>;
import Resource;
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
      void newResource(string r) const;
      
      // Printing methods
      std::string get_num() const;
      int get_level() const;

      // Checks for buying
      bool max_level() const;
      bool adjacent_check(vector<int> &criteria, vector<int> &goals) const;
      bool owned() const;

      // Upgrade logic
      Resource & upgradeCost() const;
      void upgrade();

      // save method
      std::string get_save_string() const;

      
};

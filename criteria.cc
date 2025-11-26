export module Criteria;

import <string>;
import <vector>;
import Resource;
import ISubject;

export class Criteria : public ISubject {
    int upgradeLevel;

    // levels
    static const level_chars[3];
    std::vector<Resource> level_costs;

    public:
      explicit Criteria(int location, int level = 1);

      // Printing methods
      std::string get_num() const;
      char get_owner();
      int get_level() const;

      // Checks for buying
      bool max_level() const;
      bool adjacent() const;
      bool owned() const;

      // Upgrade logic
      Resource upgradeCost();
      void upgrade();

      // save method
      std::string get_save_string() const;
};
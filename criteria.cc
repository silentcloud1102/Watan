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
      explicit Criteria(int location);

      std::string get_num() const;

      int get_level() const;
      bool max_level() const;
      void upgrade();

      char get_owner();

      
      std::string get_save_string() const;
};
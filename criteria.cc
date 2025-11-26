export module Criteria;

import ISubject;

export class Criteria : public ISubject {
    int upgradeLevel;
    char owner;
    public:
      explicit Criteria(int location): ISubject{location}, upgradeLevel{1} {
          owner = ' ';
      }
      std::string get_num() const;

      int get_level() const;

      void upgrade();

      void set_owner(char owner_char);
};
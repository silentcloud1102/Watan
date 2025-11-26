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
      void upgrade();
};
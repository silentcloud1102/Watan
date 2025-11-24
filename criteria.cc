export module Criteria;

import ISubject;

export class Criteria : public ISubject {
    int upgradeLevel;
    Criteria(int location): 
        ISubject{location}, 
        upgradeLevel{1} {}
};

class course_criterion {
  public:
  int number;
  string displaystr;
  
  course_criterion(int num, string str) : number(num), displaystr(str) {}
  
  string getnum() const {
    if (displaystr != "") {
      return displaystr;
    }

    if (number < 10) {
      return " " + to_string(number);
    }
    return to_string(number);
  }
};
export module Criteria;

import <string>;
import ISubject;
import Resource;

export class Criteria : public ISubject {
    int upgradeLevel;
    char owner;
    public:
      explicit Criteria(int location);
      std::string getnum() const;
      void upgrade(Resource &resource);
      void newResource(Resource res);
};
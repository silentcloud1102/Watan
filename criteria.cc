export module Criteria;

import ISubject;

export class Criteria : public ISubject {
    int upgradeLevel;
    Criteria(int location): 
        ISubject{location}, 
        upgradeLevel{1} {}
};
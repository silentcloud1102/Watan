export module Student;

import <iostream>;
import <vector>;

import Resource;
import IObserver;

export class Student : public IObserver {
    Resource held_resources;
    vector<IObserver *> criteria;
    public:
        explicit Student(const string colour);
};

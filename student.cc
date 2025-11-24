export module Student;

import <iostream>;

import Resource;
import IObserver;

export class Student : public IObserver {
    public:
        Student(const string colour);
}
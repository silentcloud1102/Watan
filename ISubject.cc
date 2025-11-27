export module ISubject;

import IObserver;
import <string>;

export class ISubject{
    protected:
        int location;
        ISubject * owner;
    
    public:
        ISubject(int location): location{location}, owner{nullptr} {}
        virtual void acquire(IObserver* student) = 0;
};

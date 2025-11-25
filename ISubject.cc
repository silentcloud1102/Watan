export module ISubject;

import IObserver;
import <string>;

export class ISubject{
    protected:
        ISubject * owner;
        int location;
    
    public:
        ISubject(int location): location{location}
        virtual void acquire(IObserver* student) = 0;
};

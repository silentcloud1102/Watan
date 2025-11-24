export module ISubject;

import IObserver;

export class ISubject{
    protected:
        ISubject * owner;
        int location;
    
    public:
        virtual void acquire(IObserver* student) = 0;
};

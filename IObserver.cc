export module IObserver;

import Resource;
import <string>;

export class IObserver{
    public:
        virtual void resource_notify(Resource rchange) = 0;
        
        // added here to be made visible for Subjects
        virtual std::string get_name() = 0;
        virtual std::string colour() = 0; //
};

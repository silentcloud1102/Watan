export module IObserver;

import Resource;

export class IObserver{
    public:
        virtual void resource_notify(Resource rchange) = 0;
        virtual void get_name() = 0;
};

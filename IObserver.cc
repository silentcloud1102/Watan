export module IObserver;

import Resource;

export class IObserver{
    public:
        virtual void resourceNotify(Resource rchange) = 0;
};

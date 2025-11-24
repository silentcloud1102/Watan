export module IObserver;

import Resource;

export class IObserver{
    virtual void resourceNotify(Resource rchange) = 0;
};

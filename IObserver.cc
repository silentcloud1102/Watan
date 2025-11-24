export module IObserver;

import Resources;

export class IObserver{
    virtual void resourceNotify(Resource rchange) = 0;
};

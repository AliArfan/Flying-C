#ifndef ICHAINHANDLER_H
#define ICHAINHANDLER_H

#include <QtGlobal>

template<class T, class O>
class IChainHandler {
public:
    virtual void requestView(uint value, T*& viewObject, O*& resultObject) = 0;
    virtual void validateResult(uint value, T*& viewObject, O*& resultObject) = 0;
};

#endif // ICHAINHANDLER_H

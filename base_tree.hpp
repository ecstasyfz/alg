#ifndef BASE_TREE_H
#define BASE_TREE_H

#include "vector.hpp"

template<typename T>
class BaseTree {
public:
    void Init();

protected:
    Vector<Node> nodes_;
};

#endif

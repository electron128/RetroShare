#pragma once

#include "rsserial.h"
#include "new_operations.h"

// specialisation of this template function provide real ids
template <class T>
uint32_t packet_id();

// RsItem wiht automatic clear() and print() methods
template<class ItemT>
class NewRsItem: public RsItem{
public:
    NewRsItem(): RsItem(packet_id<ItemT>()){}

    virtual void clear();
    virtual std::ostream &print(std::ostream &out, uint16_t indent = 0);
};

template<class ItemT>
void NewRsItem<ItemT>::clear()
{
    ClearOperation op;
    // todo
    //process(op, *this);
}


template<class ItemT>
std::ostream & NewRsItem<ItemT>::print(std::ostream &out, uint16_t indent)
{
    PrintOperation op(out);
    // todo
    //process(op, *this);
    return out;
}

#pragma once

#include "rsserial.h"
#include "new_operations.h"

// this class handles the switch(itemtype) of the old serialisers
// for serialisation item->PacketId and a dynamic_cast is done
// deserialisation reads the item header, and calls operator new on the right item type

class CallProcess;

class SerialTypeBase: public RsSerialType{
public:
    SerialTypeBase(uint8_t version, uint16_t servicetype) : RsSerialType(version, servicetype) {}

    // RsSerialType interface
    // called from RsSerialiser
    virtual uint32_t size (RsItem *item);
    virtual bool serialise(RsItem *item, void *data, uint32_t *size);
    virtual RsItem *deserialise (void *data, uint32_t *size);

protected:
    // interface for child classes
    // call it to add ItemT to the serialiser
    template<class ItemT>
    void addItemType();

private:

    // implementations of this class handle exactly one item type
    class ItemFunctions{
    public:
        virtual uint32_t size (RsItem *item) = 0;
        virtual bool serialise(RsItem *item, void *data, uint32_t *size) = 0;
        virtual RsItem *deserialise (void *data, uint32_t *size) = 0;
    };

    // <item type, functions to handle the type>
    std::map<uint32_t, ItemFunctions*> mFunctions;

    template<class ItemT>
    class ItemFunctionsIMPL: public ItemFunctions{
    public:
        virtual uint32_t size (RsItem *item);
        virtual bool serialise(RsItem *item, void *data, uint32_t *size);
        virtual RsItem *deserialise (void *data, uint32_t *size);
    };
};

// template implementations below

template<class ItemT>
void SerialTypeBase::addItemType()
{
    ItemT item;
    ItemFunctions* funcs = new ItemFunctionsIMPL<ItemT>();
    if(mFunctions.find(item.PacketId()) == mFunctions.end())
        mFunctions[item.PacketId()] = funcs;
    else
        std::cerr << "SerialTypeBase::addItemType() ERROR: duplicate item id." << std::endl;
}

template<class ItemT>
uint32_t SerialTypeBase::ItemFunctionsIMPL<ItemT>::size(RsItem *item)
{
    ItemT* new_item = dynamic_cast<ItemT*>(item);
    if(new_item)
    {
        SizeOperation op;
        process(op, *new_item);
        return op.getSum();
    }
    return 0;
}

template<class ItemT>
bool SerialTypeBase::ItemFunctionsIMPL<ItemT>::serialise(RsItem *item, void *data, uint32_t *size)
{
    ItemT* new_item = dynamic_cast<ItemT*>(item);
    if(new_item)
    {
        SerialiseOperation op;
        op.setBuffer(static_cast<uint8_t*>(data), *size);
        process(op, *new_item);
        return op.isOk();
    }
    return false;
}

template<class ItemT>
RsItem *SerialTypeBase::ItemFunctionsIMPL<ItemT>::deserialise (void *data, uint32_t *size)
{
    uint32_t type = getRsItemId(data);
    ItemT* item = new ItemT();
    if(type == item->PacketId())
    {
        DeserialiseOperation op;
        op.setBuffer(static_cast<uint8_t*>(data), *size);
        process(op, *item);
        if(op.isOk())
            return item;
    }
    delete item;
    return NULL;
}

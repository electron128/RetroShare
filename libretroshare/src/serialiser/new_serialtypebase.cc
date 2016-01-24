#include "new_serialtypebase.h"

uint32_t SerialTypeBase::size (RsItem *item)
{
    std::map<uint32_t, ItemFunctions*>::iterator mit = mFunctions.find(item->PacketId());
    if(mit != mFunctions.end())
        return mit->second->size(item);
    return false;
}

bool SerialTypeBase::serialise(RsItem *item, void *data, uint32_t *size)
{
    std::map<uint32_t, ItemFunctions*>::iterator mit = mFunctions.find(item->PacketId());
    if(mit != mFunctions.end())
        return mit->second->serialise(item, data, size);
    return false;
}

RsItem *SerialTypeBase::deserialise (void *data, uint32_t *size)
{
    uint32_t type = getRsItemId(data);
    std::map<uint32_t, ItemFunctions*>::iterator mit = mFunctions.find(type);
    if(mit != mFunctions.end())
        return mit->second->deserialise(data, size);
    return NULL;
}

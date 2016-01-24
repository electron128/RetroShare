#pragma once

#include "new_RsItem.h"
#include "new_serialtypebase.h"
#include "new_baseserial.h"

const uint16_t RS_SERVICE_TYPE_NEW = 0xFFFF;

class NewItem;

// 1. define packet id
template <>
uint32_t packet_id<NewItem>(){ return (RS_PKT_VERSION_SERVICE << 24)|(RS_SERVICE_TYPE_NEW << 8)| 0x00; }

// 2. define item members in item class
// parent NewRsItem<T> implements clear() and print() for us
class NewItem: public NewRsItem<NewItem>{
public:
    std::string msg;
    uint8_t number;
};

// 3. define serialisation format
template<class OperationT>
void process(OperationT& op, NewItem& item)
{
    // TODO: add item header
    process(op, item.msg);
    process_uint8(op, item.number);

    // we could also use TLV format
    // process_tlv(op, TLV_TYPE_STR_MSG, item.msg);
}

class NewItemSerialiser: public SerialTypeBase
{
public:
    NewItemSerialiser(): SerialTypeBase(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_NEW)
    {
        // 4. add item type to serialiser
        addItemType<NewItem>();
    }
};

// 5. that's all

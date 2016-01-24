#include "new_baseserial.h"

#include <string>

// ---------- uint8_t ----------

// suffix _uint8 is needed
// else the compiler could expand uint8 to uint32 and call the wrong function
void process_uint8(SizeOperation& op, uint8_t /*val*/)
{
    op.add(1);
}

void process_uint8(SerialiseOperation& op, const uint8_t val)
{
    // the decision if data can be written to the serialisation buffer
    // is in SerialiseOperation. we don't don't care if it works or not
    // we just provide source buffer and length
    op.readFrom(&val, 1);
}

void process_uint8(DeserialiseOperation& op, uint8_t& val)
{
    op.writeTo(&val, 1);
}

// ---------- uint32_t ----------

void process_uint32(SizeOperation& op, uint32_t /*val*/)
{
    op.add(4);
}

void process_uint32(SerialiseOperation& op, const uint32_t val)
{
    // todo: hton
    // this is the lowest layer, where ugly casts are unavoidable
    op.readFrom(reinterpret_cast<const uint8_t*>(&val), 4);
}

void process_uint32(DeserialiseOperation& op, uint32_t& val)
{
    // todo: ntoh
    op.writeTo(reinterpret_cast<uint8_t*>(&val), 4);
}

// ---------- std::string ----------

void process(SizeOperation& op, std::string val)
{
    uint8_t str_length = val.length();
    process_uint8(op, str_length);
    op.add(str_length);
}

void process(SerialiseOperation& op, std::string val)
{
    uint8_t str_length = val.length();
    process_uint8(op, str_length);
    op.readFrom(reinterpret_cast<const uint8_t*>(val.c_str()), str_length);
}

void process(DeserialiseOperation& op, std::string& val)
{
    uint8_t str_length = 0;
    process_uint8(op, str_length);
    if(!op.isOk())
        return;
    if(!op.canRead(str_length))
    {
        op.setFail();
        return;
    }
    val = std::string(reinterpret_cast<char*>(op.getDataPtr()), str_length);
    op.didRead(str_length);
}

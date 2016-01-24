#pragma once

#include <stdint.h>
#include <iosfwd>

class SizeOperation{
public:
    // interface for the functions which process the data
    // increment counter by size bytes
    void add(uint32_t size);

    // interface for the function above (e.g. RsSerialType)
    uint32_t getSum();
    bool isOk();
private:
    bool ok;
    uint32_t count;
};

class SerialiseOperation{
public:
    // interface for the functions which process the data
    // read size bytes from data and store it in the serialisation buffer
    void readFrom(const uint8_t *data, uint32_t size);
    void setFail();
    bool isOk();

    // interface for the function above (e.g. RsSerialType)
    // set buffer to write to
    void setBuffer(uint8_t *data, uint32_t size);
private:
    bool ok;
    uint8_t *data;
    uint32_t size;
    uint32_t offset;
};

class DeserialiseOperation{
public:
    // interface for the functions which process the data
    // write size bytes from the serialisation buffer into data
    void writeTo(uint8_t *data, uint32_t size);
    void setFail();
    bool isOk();

    // returns true if size bytes are available for reading
    bool canRead(uint32_t size);

    // return a pointer to the current read position
    // the caller must test with canRead(size) if his read is valid!
    uint8_t* getDataPtr();

    // tell DeserialiseOperation that you have read size bytes
    // this invalidates values returned by canRead() and getDataPtr()
    void didRead(uint32_t size);

    // interface for the function above (e.g. RsSerialType)
    // set buffer to read from
    void setBuffer(const uint8_t *data, uint32_t size);
private:
    bool ok;
    uint8_t *data;
    uint32_t size;
    uint32_t offset;
};

// clear item
// initialise ints to 0 and make string/vectors/lists empty
class ClearOperation{
public:

};

// generate human readable output
class PrintOperation{
public:
    PrintOperation(std::ostream &o): out(o){}
    std::ostream &out;
};

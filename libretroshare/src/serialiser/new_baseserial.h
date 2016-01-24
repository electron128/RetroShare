#pragma once

#include "new_operations.h"
#include <vector>

// serialisation routines for basic data types
// every serialisable type has a bunch of functions
// these functions define, how the type should be processed:
// - how is the size calculated?
// - how is it serialised?
// - how is it deserialised?
// additional functions could define
// - how to clear the type
// - how to pretty print the type

// once a function is defined, it must not change the binary format,
// because others depend on it
// other serialisation formats could be added with new function names
// example: process_uint32_little_endian();

// ---------- uint8_t ----------

// suffix is _uint8 is needed
// else the compiler could expand uint8 to uint32 and call the wrong function
void process_uint8(SizeOperation& op, uint8_t /*val*/);
void process_uint8(SerialiseOperation& op, const uint8_t val);
void process_uint8(DeserialiseOperation& op, uint8_t& val);

// ---------- uint32_t ----------
void process_uint32(SizeOperation& op, uint32_t /*val*/);
void process_uint32(SerialiseOperation& op, const uint32_t val);
void process_uint32(DeserialiseOperation& op, uint32_t& val);

// ---------- std::string ----------
void process(SizeOperation& op, std::string val);
void process(SerialiseOperation& op, std::string val);
void process(DeserialiseOperation& op, std::string& val);

// ---------- std::vector<T> ----------
// three functions have to be defined for type T:
//
//     process(SizeOperation&, const T&);
//     process(SerialiseOperation&, const T&);
//     process(DeserialiseOperation&, T&);
//
template <class T> void process(SizeOperation& op, const std::vector<T>& val);
template <class T> void process(SerialiseOperation& op, const std::vector<T>& val);
template <class T> void process(DeserialiseOperation& op, std::vector<T>& val);

// other idea, to define how members should be serialised
// f is called like this: f(op, val)
template <class T, class F> void process(SizeOperation& op, const std::vector<T>& val, F f);
template <class T, class F> void process(SerialiseOperation& op, const std::vector<T>& val, F f);
template <class T, class F> void process(DeserialiseOperation& op, std::vector<T>& val, F f);

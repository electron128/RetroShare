#pragma once

#include "new_operations.h"

void process_tlv(SizeOperation & op, uint16_t type, std::string &val);
void process_tlv(SerialiseOperation & op, uint16_t type, std::string &val);
void process_tlv(DeserialiseOperation & op, uint16_t type, std::string &val);

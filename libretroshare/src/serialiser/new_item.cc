#include "new_item.h"

void use()
{
    NewItem item;
    NewItemSerialiser* serialiser = new NewItemSerialiser();
    uint32_t size = serialiser->size(&item);

    void* data = malloc(size);
    serialiser->serialise(&item, data, &size);

    RsItem* item2 = serialiser->deserialise(data, &size);
    if(item2)
        delete item2;

    free(data);
}

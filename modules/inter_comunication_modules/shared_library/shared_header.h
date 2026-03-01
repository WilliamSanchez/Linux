#ifndef __SHARED_HEADER_H__
#define __SHARED_HEADER_H__

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/mutex.h>

typedef struct shared_data
{
    void *data;
    uint16_t len;
} _shared_data;

extern _shared_data *data1;
struct mutex etx_mutex;

#endif

#ifndef __TRANSPORT_H__
#define __TRANSPORT_H__

#include <thrift/types.h>

typedef struct tn_transport_t
{
	bool (*tn_is_open)(struct tn_transport_t *self);
	size_t (*tn_read)(struct tn_transport_t *self, void *buf, size_t len, tn_error_t *error);
	size_t (*tn_write)(struct tn_transport_t *self, void *buf, size_t len, tn_error_t *error);
    void (*tn_reset)(struct tn_transport_t* self);
} tn_transport_t;
tn_transport_t* tn_transport_init(tn_transport_t *self, tn_error_t *error);
tn_transport_t* tn_transport_create(tn_error_t *error);
void tn_transport_destroy(tn_transport_t* self);

typedef struct tn_transport_memory_t
{
	tn_transport_t parent;
	tn_buffer_t* buf;
} tn_transport_memory_t;
tn_transport_t* tn_transport_memory_init(tn_transport_memory_t *self, size_t bufferSize, tn_error_t *error);
tn_transport_t* tn_transport_memory_create(size_t bufferSize, tn_error_t *error);
void tn_transport_memory_destroy(tn_transport_memory_t* self);

#endif

#ifndef POLYFILL_UUID_H
#define POLYFILL_UUID_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uuid_t[16];

void uuid_generate(uuid_t out);

#ifdef __cplusplus
}
#endif

#endif // POLYFILL_UUID_H

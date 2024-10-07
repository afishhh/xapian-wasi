#include <stdint.h>
#include <assert.h>

#include "uuid.h"

extern int16_t random_get(unsigned char *ptr, uint32_t sz) __attribute__((
    __import_module__("wasi_snapshot_preview1"), __import_name__("random_get"),
));

void uuid_generate(uuid_t out) {
  assert(random_get(out, 16) == 0);
}

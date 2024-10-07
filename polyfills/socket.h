#include <assert.h>

static int socket(int __domain, int __type, int __protocol) { assert(false); }

static int socketpair(int __domain, int __type, int __protocol, int __fds[2]) {
  assert(false);
}

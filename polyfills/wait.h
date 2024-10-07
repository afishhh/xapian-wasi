#ifndef POLYFILL_WAIT_H
#define POLYFILL_WAIT_H

#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint64_t locked = 0;

#define flock this_is_not_flock

int flock(int fd, int op) {
	fd &= 0x3F;
	uint64_t mask = (uint64_t)1 << fd;
	if(op & LOCK_EX) {
		if(locked & mask) {
			if(op & LOCK_NB) {
				errno = EWOULDBLOCK;
				return -1;
			}
			fprintf(stderr, "<!> flock locked twice <!>\n");
			abort();
		}
		locked |= mask;
		return 0;
	} else if(op == LOCK_UN) {
		if(!(locked & mask)) {
			fprintf(stderr, "<!> flock unlocked twice <!>\n");
			abort();
		}
		locked ^= mask;
		return 0;
	} else {
		fprintf(stderr, "<!> unknown flags to flock <!>\n");
		fprintf(stderr, "value: %i\n", op);
		fprintf(stderr, "LOCK_EX: %i\n", op & LOCK_EX);
		fprintf(stderr, "LOCK_UN: %i\n", op & LOCK_UN);
		fprintf(stderr, "LOCK_NB: %i\n", op & LOCK_NB);
		abort();
	}
}

#endif // POLYFILL_WAIT_H

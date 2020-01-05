#include "memory.h"

#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <unistd.h>

#include "exit.h"

void lock_memory_and_drop_privileges(void) {
	int r;
	int original_uid;

	// Prevent our memory from being swapped out
	r = mlockall(MCL_CURRENT | MCL_FUTURE);
#if WARN_ON_MEMORY_LOCK_ERRORS
	if (r != 0) {
		warn("Unable to lock memory, which means secrets may be swapped to "
		     "disk");
	}
#endif

	// Set memory to not-dumpable
	r = prctl(PR_SET_DUMPABLE, 0);
#if WARN_ON_MEMORY_LOCK_ERRORS
	if (r != 0) {
		warn("Unable to set dumpable flag to 0, which means a core dump "
		     "(including  secrets) may be written to disk in the event of a "
		     "crash");
	}
#endif

	// Limit core dump size to 0 bytes
	r = setrlimit(RLIMIT_CORE, &(struct rlimit){0, 0});
#if WARN_ON_MEMORY_LOCK_ERRORS
	if (r != 0) {
		warn("Unable to set RLIMIT_CORE to {0, 0}, which means a core dump "
		     "(including secrets) may be written to disk in the event of a "
		     "crash");
	}
#endif

	// Drop privileges if running as root
	if (geteuid() == 0) {
		if (geteuid() != getuid()) {
			original_uid = getuid();
		} else if (getenv("SUDO_UID") != NULL) {
			original_uid = atoi(getenv("SUDO_UID"));
		} else {
			original_uid = 0;
		}

		if (original_uid != 0 && setuid(original_uid) != 0) {
			err(EXIT_OVER_PRIVILEGED, "Unable to drop privileges");
		}
	}
}

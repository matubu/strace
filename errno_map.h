#pragma once

#define MAX_ERRNO 4096

#define ERESTARTSYS 512
#define ERESTARTNOINTR 513
#define ERESTARTNOHAND 514
#define ERESTART_RESTARTBLOCK 516

extern const char *errno_map[MAX_ERRNO];
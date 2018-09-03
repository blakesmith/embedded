#ifndef KEEBIRD_LOG_H_
#define KEEBIRD_LOG_H_

#include <stdio.h>

#define keebird_log_verbose(LABEL, MSG, ...) fprintf(stdout, "%s: ", LABEL); \
    fprintf(stdout, MSG, ##__VA_ARGS__)

#endif

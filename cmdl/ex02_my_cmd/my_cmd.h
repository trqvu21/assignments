#ifndef MY_CMD_H
#define MY_CMD_H

#include <stdint.h>

#define MY_CMD_NAME_MAX 16

typedef enum {
    MY_CMD_OK = 0,
    MY_CMD_TABLE_NULL,
    MY_CMD_INPUT_NULL,
    MY_CMD_NOT_FOUND,
    MY_CMD_NAME_TOO_LONG
} my_cmd_status_t;

typedef int32_t (*my_cmd_handler_t)(const char *args);

typedef struct {
    const char *name;
    my_cmd_handler_t handler;
    const char *help;
} my_cmd_t;

my_cmd_status_t my_cmd_execute(const my_cmd_t *table, const char *input);

#endif

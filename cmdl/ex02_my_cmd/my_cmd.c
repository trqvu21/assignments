#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include "my_cmd.h"

static const char *skip_spaces(const char *s) {
    while (*s && isspace((unsigned char)*s)) {
        s++;
    }
    return s;
}

static my_cmd_status_t read_command_name(const char *input, char *name, const char **args) {
    unsigned int len = 0;
    input = skip_spaces(input);

    while (input[len] && !isspace((unsigned char)input[len])) {
        if (len >= MY_CMD_NAME_MAX - 1) {
            return MY_CMD_NAME_TOO_LONG;
        }
        name[len] = input[len];
        len++;
    }

    name[len] = '\0';
    *args = skip_spaces(input + len);
    return MY_CMD_OK;
}

static const my_cmd_t *find_command(const my_cmd_t *table, const char *name) {
    for (unsigned int i = 0; table[i].name != 0; i++) {
        if (strcmp(table[i].name, name) == 0) {
            return &table[i];
        }
    }
    return 0;
}

my_cmd_status_t my_cmd_execute(const my_cmd_t *table, const char *input) {
    char name[MY_CMD_NAME_MAX];
    const char *args = 0;
    const my_cmd_t *cmd = 0;
    my_cmd_status_t status;

    if (table == 0) {
        return MY_CMD_TABLE_NULL;
    }
    if (input == 0) {
        return MY_CMD_INPUT_NULL;
    }

    status = read_command_name(input, name, &args);
    if (status != MY_CMD_OK) {
        return status;
    }

    cmd = find_command(table, name);
    if (cmd == 0) {
        return MY_CMD_NOT_FOUND;
    }

    cmd->handler(args);
    return MY_CMD_OK;
}

#include <stdint.h>
#include <string.h>
#include "cmd_line.h"

uint8_t cmd_line_parser(cmd_line_t *cmd_table, uint8_t *command) {
    uint8_t cmd[MAX_CMD_SIZE];
    uint8_t *p_command = command;
    uint8_t cmd_index = 0;
    uint8_t table_index = 0;

    if (cmd_table == (cmd_line_t *)0) {
        return CMD_TBL_NOT_FOUND;
    }

    /* Lấy tên command đầu tiên, dừng ở space / CR / LF. */
    while (*p_command) {
        if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
            cmd[cmd_index] = 0;
            break;
        }

        cmd[cmd_index++] = *p_command++;
        if (cmd_index >= MAX_CMD_SIZE) {
            return CMD_TOO_LONG;
        }
    }

    /* Nếu input kết thúc luôn, vẫn cần đóng chuỗi. */
    if (*p_command == 0) {
        cmd[cmd_index] = 0;
    }

    /* Duyệt bảng command để tìm handler tương ứng. */
    while (cmd_table[table_index].cmd) {
        if (strcmp((const char *)cmd_table[table_index].cmd, (const char *)cmd) == 0) {
            cmd_table[table_index].func(command);
            return CMD_SUCCESS;
        }
        table_index++;
    }

    return CMD_NOT_FOUND;
}

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cmd_line.h"

static int total = 0;
static int passed = 0;
static const char *last_handler = "";
static char last_argv[64];

#define CHECK(name, expr) do {                         \
    total++;                                            \
    if (expr) {                                         \
        passed++;                                       \
        printf("[PASS] %s\n", name);                    \
    }                                                   \
    else {                                              \
        printf("[FAIL] %s\n", name);                    \
    }                                                   \
} while (0)

static int32_t help_handler(uint8_t *argv) {
    last_handler = "help";
    snprintf(last_argv, sizeof(last_argv), "%s", argv);
    return 0;
}

static int32_t reset_handler(uint8_t *argv) {
    last_handler = "reset";
    snprintf(last_argv, sizeof(last_argv), "%s", argv);
    return 0;
}

static cmd_line_t test_table[] = {
    {(const int8_t *)"help", help_handler,  (const int8_t *)"show help"},
    {(const int8_t *)"reset", reset_handler, (const int8_t *)"reset board"},
    {0, 0, 0}
};

static void clear_state(void) {
    last_handler = "";
    last_argv[0] = 0;
}

static void test_null_table(void) {
    uint8_t input[] = "help\n";
    CHECK("null table", cmd_line_parser(0, input) == CMD_TBL_NOT_FOUND);
}

static void test_existing_command(void) {
    clear_state();
    uint8_t input[] = "help\n";
    uint8_t ret = cmd_line_parser(test_table, input);

    CHECK("existing command return", ret == CMD_SUCCESS);
    CHECK("existing command handler", strcmp(last_handler, "help") == 0);
}

static void test_command_with_argument(void) {
    clear_state();
    uint8_t input[] = "reset now\n";
    uint8_t ret = cmd_line_parser(test_table, input);

    CHECK("command with arg return", ret == CMD_SUCCESS);
    CHECK("command with arg handler", strcmp(last_handler, "reset") == 0);
    CHECK("handler receives full input", strcmp(last_argv, "reset now\n") == 0);
}

static void test_unknown_command(void) {
    clear_state();
    uint8_t input[] = "led_on\n";
    CHECK("unknown command", cmd_line_parser(test_table, input) == CMD_NOT_FOUND);
}

static void test_too_long_command(void) {
    uint8_t input[] = "very_long_command_name\n";
    CHECK("too long command", cmd_line_parser(test_table, input) == CMD_TOO_LONG);
}

int main(void) {
    test_null_table();
    test_existing_command();
    test_command_with_argument();
    test_unknown_command();
    test_too_long_command();

    printf("cmd_line unit test: %d/%d passed\n", passed, total);
    return (passed == total) ? 0 : 1;
}

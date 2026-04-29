#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "my_cmd.h"

static int total = 0;
static int passed = 0;
static const char *last_command = "";
static char last_args[64];

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

static int32_t led_on_handler(const char *args) {
    last_command = "led_on";
    snprintf(last_args, sizeof(last_args), "%s", args);
    return 0;
}

static int32_t led_off_handler(const char *args) {
    last_command = "led_off";
    snprintf(last_args, sizeof(last_args), "%s", args);
    return 0;
}

static int32_t status_handler(const char *args) {
    last_command = "status";
    snprintf(last_args, sizeof(last_args), "%s", args);
    return 0;
}

static const my_cmd_t app_cmd_table[] = {
    {"led_on",  led_on_handler,  "turn LED on"},
    {"led_off", led_off_handler, "turn LED off"},
    {"status",  status_handler,  "show status"},
    {0, 0, 0}
};

static void clear_state(void) {
    last_command = "";
    last_args[0] = 0;
}

static void test_table_null(void) {
    CHECK("table null", my_cmd_execute(0, "led_on") == MY_CMD_TABLE_NULL);
}

static void test_input_null(void) {
    CHECK("input null", my_cmd_execute(app_cmd_table, 0) == MY_CMD_INPUT_NULL);
}

static void test_led_on(void) {
    clear_state();
    CHECK("led_on return", my_cmd_execute(app_cmd_table, "led_on") == MY_CMD_OK);
    CHECK("led_on handler", strcmp(last_command, "led_on") == 0);
}

static void test_command_with_args(void) {
    clear_state();
    CHECK("status return", my_cmd_execute(app_cmd_table, "status board_1") == MY_CMD_OK);
    CHECK("status handler", strcmp(last_command, "status") == 0);
    CHECK("status args", strcmp(last_args, "board_1") == 0);
}

static void test_skip_space(void) {
    clear_state();
    CHECK("skip leading space", my_cmd_execute(app_cmd_table, "   led_off   fast") == MY_CMD_OK);
    CHECK("led_off handler", strcmp(last_command, "led_off") == 0);
    CHECK("led_off args", strcmp(last_args, "fast") == 0);
}

static void test_not_found(void) {
    CHECK("not found", my_cmd_execute(app_cmd_table, "reboot") == MY_CMD_NOT_FOUND);
}

static void test_name_too_long(void) {
    CHECK("name too long", my_cmd_execute(app_cmd_table, "this_command_name_is_too_long") == MY_CMD_NAME_TOO_LONG);
}

int main(void) {
    test_table_null();
    test_input_null();
    test_led_on();
    test_command_with_args();
    test_skip_space();
    test_not_found();
    test_name_too_long();

    printf("my_cmd test: %d/%d passed\n", passed, total);
    return (passed == total) ? 0 : 1;
}

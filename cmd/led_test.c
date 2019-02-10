// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2018 zfl
 * Written by zfl <460342522@qq.com>
 */

#include <common.h>
#include <command.h>
#include <dm.h>
#include <led_test.h>
#include <dm/uclass-internal.h>

static const char *const state_label_test[] = {
	[LEDST_OFF]	= "off",
	[LEDST_ON]	= "on",
	[LEDST_TOGGLE]	= "toggle",
};

enum led_state_t get_led_cmd_test(char *var)
{
	int i;

	for (i = 0; i < LEDST_COUNT; i++) {
		if (!strncmp(var, state_label_test[i], strlen(var)))
			return i;
	}

	return -1;
}

int do_led_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	enum led_state_t cmd;
	const char *led_label;

	/* Validate arguments */
	if (argc < 2)
		return CMD_RET_USAGE;
	led_label = argv[1];
	if (*led_label == 'l') {
        printf("led list\n");
        return 0;
    }

	cmd = argc > 2 ? get_led_cmd_test(argv[2]) : LEDST_COUNT;

	switch (cmd) {
	case LEDST_OFF:
        printf("turn off led\n");
        break;
	case LEDST_ON:
        printf("turn on led\n");
        break;
	case LEDST_TOGGLE:
        printf("toggle led\n");
		break;
    default:
        printf("wrong command\n");
        break;
	}

	return 0;
}

U_BOOT_CMD(
	led_test, 4, 1, do_led_test,
	"manage LEDs",
	"<led_label> on|off|toggle\tChange LED state\n"
	"led [<led_label>\tGet LED state\n"
	"led list\t\tshow a list of LEDs"
);

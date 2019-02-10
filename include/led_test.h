/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2019 zfling
 * Written by zfl <460342522@qq.com>
 */

#ifndef __LED_TEST_ZFL_H
#define __LED_TEST_ZFL_H

/**
 * struct led_test_uc_plat - Platform data the uclass stores about each device
 *
 * @label:	LED label
 */
struct led_test_uc_plat {
	const char *label;
};

/**
 * struct led_test_uc_priv - Private data the uclass stores about each device
 *
 * @period_ms:	Flash period in milliseconds
 */
struct led_test_uc_priv {
	int period_ms;
};

enum led_test_state_t {
	LEDST_OFF = 0,
	LEDST_ON = 1,
	LEDST_TOGGLE,

	LEDST_COUNT,
};

struct led_test_ops {
	/**
	 * set_state() - set the state of an LED
	 *
	 * @dev:	LED device to change
	 * @state:	LED state to set
	 * @return 0 if OK, -ve on error
	 */
	int (*set_state)(struct udevice *dev, enum led_state_t state);

	/**
	 * led_get_state() - get the state of an LED
	 *
	 * @dev:	LED device to change
	 * @return LED state led_state_t, or -ve on error
	 */
	enum led_test_state_t (*get_state)(struct udevice *dev);
};

#define led_test_get_ops(dev)	((struct led_ops *)(dev)->driver->ops)

/**
 * led_test_get_by_label() - Find an LED device by label
 *
 * @label:	LED label to look up
 * @devp:	Returns the associated device, if found
 * @return 0 if found, -ENODEV if not found, other -ve on error
 */
int led_test_get_by_label(const char *label, struct udevice **devp);

#endif

// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2019 zfling
 * Written by zfl <460342522@qq.com>
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <led_test.h>
#include <dm/device-internal.h>
#include <dm/root.h>
#include <dm/uclass-internal.h>


int led_test_get_by_label(const char *label, struct udevice **devp)
{
	struct udevice *dev;
	struct uclass *uc;
	int ret;

	ret = uclass_get(UCLASS_LED_TEST, &uc);
	if (ret)
		return ret;
	uclass_foreach_dev(dev, uc) {
		struct led_test_uc_plat *uc_plat = dev_get_uclass_platdata(dev);

		/* Ignore the top-level LED node */
		if (uc_plat->label && !strcmp(label, uc_plat->label))
			return uclass_get_device_tail(dev, 0, devp);
	}

	return -ENODEV;
}

#if 0
int led_test_set_state(struct udevice *dev, enum led_state_t state)
{
	struct led_ops *ops = led_get_ops(dev);

	if (!ops->set_state)
		return -ENOSYS;

	return ops->set_state(dev, state);
}

enum led_test_state_t led_test_get_state(struct udevice *dev)
{
	struct led_ops *ops = led_get_ops(dev);

	if (!ops->get_state)
		return -ENOSYS;

	return ops->get_state(dev);
}

int led_test_default_state(void)
{
	struct udevice *dev;
	struct uclass *uc;
	const char *default_state;
	int ret;

	ret = uclass_get(UCLASS_LED_TEST, &uc);
	if (ret)
		return ret;
	for (uclass_find_first_device(UCLASS_LED_TEST, &dev);
	     dev;
	     uclass_find_next_device(&dev)) {
		default_state = dev_read_string(dev, "default-state");
		if (!default_state)
			continue;
		ret = device_probe(dev);
		if (ret)
			return ret;
		if (!strncmp(default_state, "on", 2))
			led_set_state(dev, LEDST_ON);
		else if (!strncmp(default_state, "off", 3))
			led_set_state(dev, LEDST_OFF);
		/* default-state = "keep" : device is only probed */
	}

	return ret;
}
#endif

UCLASS_DRIVER(led_test) = {
	.id		= UCLASS_LED_TEST,
	.name		= "led_test",
	.per_device_platdata_auto_alloc_size = sizeof(struct led_test_uc_plat),
};

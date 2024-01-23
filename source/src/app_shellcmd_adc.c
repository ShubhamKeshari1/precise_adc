#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <version.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/usb/usb_device.h>
#include <ctype.h>
#ifdef CONFIG_ARCH_POSIX
#include <unistd.h>
#else
#include <zephyr/posix/unistd.h>
#endif
#include <unistd.h>
	
#include "adc_sampling.h"
#include "calc_avg.h"

#define DEFAULT_PRINT_INTERVAL 1000

extern struct adc_dt_spec adc_channels[];
static int i = 0;
static int prnt_var = 0;

static int shellcmd_adc_start(const struct shell *shell, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	int ret = adc_enable();
	if (!ret) {
		shell_print(shell, "OK");
		printk("- %s, channel %d: ",
			       adc_channels[i].dev->name,
			       adc_channels[i].channel_id);
		printk("ADC enabled\n");
	}
	else {
		shell_print(shell, "ERR");
	}
	return ret;
}

static int shellcmd_adc_stop(const struct shell *shell, size_t argc, char **argv) {
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	int ret = adc_disable();
	if (!ret) {
		shell_print(shell, "OK");
		printk("ADC disabled\n");
	}
	else {
		shell_print(shell, "ERR");
	}
	return ret;
}

static int shellcmd_print_set_interval(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	prnt_var = strtol(argv[1], NULL, 10);
	shell_print(shell,"Print interval = %d ms", prnt_var);
	printk("ADC print interval set = %d ms\n", prnt_var);
	int ret = print_interval(prnt_var);

	if (!ret)	shell_print(shell, "OK");
	else		shell_print(shell, "ERR");

	return ret;
}

static int shellcmd_print_get_interval(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
        
    int p_prnt_interval_ms = 0;
        
	int ret = print_interval_get(&p_prnt_interval_ms);
	if (!ret){	
	    shell_print(shell, "OK");
	    shell_print(shell,"ADC print interval set = %d ms", p_prnt_interval_ms);
	    printk("ADC print interval set = %d ms\n", p_prnt_interval_ms);
	}
	else		shell_print(shell, "ERR");

	return ret;
}

SHELL_STATIC_SUBCMD_SET_CREATE(adc_log_subcmds,
		SHELL_CMD(start, NULL, "Adc enable", shellcmd_adc_start),
		SHELL_CMD(stop, NULL, "Adc disable", shellcmd_adc_stop),
		SHELL_CMD(prnt_intr_get, NULL, "print interval set in ms", shellcmd_print_get_interval),
		SHELL_CMD_ARG(prnt_intr_set, NULL, "print interval set in ms", shellcmd_print_set_interval, 2, 0),
		SHELL_SUBCMD_SET_END /* Array terminated. */
		);
SHELL_CMD_REGISTER(adc_log, &adc_log_subcmds, "ADC sub commands", NULL);

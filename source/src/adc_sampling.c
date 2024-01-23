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

#include "calc_avg.h"

#define LOOP_DELAY 10
#define DEFAULT_PRINT_INTERVAL 1000
#define DEFAULT_SAMPLE_COUNT (DEFAULT_PRINT_INTERVAL / LOOP_DELAY)

#define RESET 0
#define LOW 0
#define HIGH 1


static int adc_state = LOW;
static int prnt_intr = DEFAULT_PRINT_INTERVAL;
static int sample_count = DEFAULT_SAMPLE_COUNT;

extern struct adc_dt_spec adc_channels[];
size_t i;

static int sampling_counter,raw_counter = 0;
static float return_avg = 0;
static int adc_sample[1000]={0};
static int index,raw_adc_total = 0;

int adc_enable ()
{
  adc_state = HIGH;
  return 0;
}

int adc_disable ()
{
  adc_state = LOW;
  sampling_counter = RESET;
  prnt_intr = DEFAULT_PRINT_INTERVAL;
  sample_count = DEFAULT_SAMPLE_COUNT;
  return 0;
}

int print_interval (int interval_ms)
{
 prnt_intr = interval_ms;
 sampling_counter = RESET;
 raw_counter = RESET;
 sample_count = RESET;
 sample_count = DEFAULT_SAMPLE_COUNT;
 sample_count = prnt_intr/LOOP_DELAY;
 return 0;
}

int print_interval_get (int *p_prnt_interval_ms)
{
  *p_prnt_interval_ms = prnt_intr;
  return 0;
}

int adc_sampling (int32_t val_mv, int32_t adc_raw)
{
    if (adc_state == HIGH){
		if (sampling_counter == prnt_intr && raw_counter == sample_count){
			float raw_adc_avg = raw_adc_total/sample_count;
			return_avg = calc_avg(adc_sample,sample_count);
			printk("- %s, channel %d: ", adc_channels[i].dev->name, adc_channels[i].channel_id);
			printk("raw = %dbin value = %dmV\n",(int)raw_adc_avg, (int)return_avg);
			index = RESET;
			sampling_counter = RESET;
			raw_adc_total = RESET;
			raw_counter = RESET;
			return 0;
		}
		else {
			adc_sample[index] = val_mv;
			index ++;
			if(raw_counter ==  sample_count);
			else {
				raw_adc_total = raw_adc_total + adc_raw;
				raw_counter ++;
			}
			sampling_counter = sampling_counter + LOOP_DELAY;
			return 0;
		}
  }
  else {
	  return 0;
  }
}

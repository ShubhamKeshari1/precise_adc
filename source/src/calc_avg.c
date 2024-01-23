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

float calc_avg(int adc_sample[], int sample_count)
{
  int index,total_value = 0;
  float adc_avg=0;
  
  for (index=0;index<sample_count;index++){
  total_value += adc_sample[index];
  }
  adc_avg = (float)total_value/sample_count;
  //printk("Avg adc=%0.2fmV\n", adc_avg);
  
  return adc_avg;
}

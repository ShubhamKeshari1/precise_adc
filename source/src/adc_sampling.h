
#ifndef ADC_SAMPLING_H_INCLUDED
#define ADC_SAMPLING_H_INCLUDED

int adc_enable ();
int adc_disable ();
int print_interval (int interval_ms);
int print_interval_get (int *p_prnt_interval_ms);
int adc_sampling (int32_t val_mv, int32_t adc_raw);

#endif 


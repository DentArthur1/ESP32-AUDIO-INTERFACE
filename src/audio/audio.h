#include "adc_sampler.h"
#include "i2s_output.h"

//TX INTERROMPE RX SE NECESSARIO
//RX SI ATTIVA SOLE SE TX NON È IN FUNZIONE

void switch_to_tx(i2s_chan_handle_t i2s_handle, adc_continuous_handle_t adc_handle);
bool switch_to_rx(adc_continuous_handle_t adc_handle, i2s_chan_handle_t i2s_handle); //true se TX non è attiva
void end_tx(adc_continuous_handle_t adc_handle);
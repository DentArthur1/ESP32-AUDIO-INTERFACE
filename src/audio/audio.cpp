#include "audio.h"

void switch_to_tx(i2s_chan_handle_t i2s_handle, adc_continuous_handle_t adc_handle)
{ 
    if (i2s_handle != NULL){ //RX è attivo
        stop_i2s_output(i2s_handle);
    }
    if (adc_handle == NULL){ //TX non ancora attivo
       //Attivo TX
       adc_handle = initialize_adc();
       start_adc(adc_handle);
    }
}

bool switch_to_rx(adc_continuous_handle_t adc_handle, i2s_chan_handle_t i2s_handle)
{
    if (adc_handle == NULL){
        //Non sto trasmettendo
        if (i2s_handle != NULL){
            //Non ho ancora attivato il canale di ricezione
            i2s_handle = initialize_i2s_output();
            start_i2s_output(i2s_handle);
        }
        return true;
    }
    //Sto trasmettendo, priorità alla trasmissione
    return false;
}

void end_tx(adc_continuous_handle_t adc_handle)
{
   if (adc_handle != NULL){ //per sicurezza, anche se non dovrebbe servire
      stop_adc(adc_handle);
   }
}

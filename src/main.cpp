#include <Arduino.h>
#include "audio/audio.h"

adc_continuous_handle_t my_adc_handle;
i2s_chan_handle_t my_i2s_handle;

void setup() {
    Serial.begin(115200);
    //ADC
    my_adc_handle = initialize_adc();
    start_adc(my_adc_handle);
    //I2S
    my_i2s_handle = initialize_i2s_output();
    start_i2s_output(my_i2s_handle);
}

void loop() {
    // Crea il buffer PCM
    int16_t pcm_buffer[BUFFER_SIZE];
    // Riempi il buffer con i dati PCM
    read_and_convert_to_pcm(my_adc_handle, pcm_buffer, BUFFER_SIZE);
    // Per il debug, visualizza i primi 10 campioni PCM
    //preview_pcm(pcm_buffer, BUFFER_SIZE, 10);
    //Scrivo i dati sulla periferica I2S
    write_pcm(pcm_buffer, BUFFER_SIZE, my_i2s_handle);
}


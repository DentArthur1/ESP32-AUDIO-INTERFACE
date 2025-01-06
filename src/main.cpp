#include <Arduino.h>
#include "audio/audio.h"

adc_continuous_handle_t my_handle;

void setup() {
    Serial.begin(115200);
    my_handle = initialize_adc();
    start_adc(my_handle);
}

void loop() {
    
    int16_t prova[64];
    // Crea il buffer PCM
    int16_t pcm_buffer[BUFFER_SIZE];

    // Riempi il buffer con i dati PCM
    read_and_convert_to_pcm(my_handle, pcm_buffer, BUFFER_SIZE);

    // Per il debug, visualizza i primi 10 campioni PCM
    preview_pcm(pcm_buffer, BUFFER_SIZE, 10);
    delay(1000);
}


#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include <Arduino.h>

#define SAMPLE_RATE 44100
#define DOUT_PIN GPIO_NUM_22
#define BCLK_PIN GPIO_NUM_26
#define WS_PIN GPIO_NUM_25
#define BIT_WIDTH I2S_DATA_BIT_WIDTH_16BIT

i2s_chan_handle_t initialize_i2s_output();
void start_i2s_output(i2s_chan_handle_t my_handle);
size_t write_pcm(int16_t *pcm_data, int pcm_data_len, i2s_chan_handle_t tx_handle);
void stop_i2s_output(i2s_chan_handle_t tx_handle);
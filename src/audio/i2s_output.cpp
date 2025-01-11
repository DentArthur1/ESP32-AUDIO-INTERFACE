#include "i2s_output.h"

i2s_chan_handle_t initialize_i2s_output()
{
    i2s_chan_handle_t tx_handle;
    /* Get the default channel configuration by the helper macro.
    * This helper macro is defined in `i2s_common.h` and shared by all the I2S communication modes.
    * It can help to specify the I2S role and port ID */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    /* Allocate a new TX channel and get the handle of this channel */
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_handle, NULL));

    /* Setting the configurations, the slot configuration and clock configuration can be generated by the macros
    * These two helper macros are defined in `i2s_std.h` which can only be used in STD mode.
    * They can help to specify the slot and clock configurations for initialization or updating */
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE),
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(BIT_WIDTH, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = BCLK_PIN,
            .ws = WS_PIN,
            .dout = DOUT_PIN,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    /* Initialize the channel */
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_handle, &std_cfg));
    return tx_handle;
}

void start_i2s_output(i2s_chan_handle_t my_handle){

    ESP_ERROR_CHECK(i2s_channel_enable(my_handle));
    Serial.println("I2S OUTPUT inizializzato correttamente");
}

void stop_i2s_output(i2s_chan_handle_t tx_handle) {
    // Disabilita il canale
    ESP_ERROR_CHECK(i2s_channel_disable(tx_handle));
    Serial.println("I2S OUTPUT disabilitato correttamente");

    // Cancella il canale e libera le risorse
    ESP_ERROR_CHECK(i2s_del_channel(tx_handle));
    Serial.println("I2S OUTPUT canale eliminato e risorse liberate");
}


size_t write_pcm(int16_t *pcm_data, int pcm_data_len, i2s_chan_handle_t tx_handle){
    size_t bytes_written;
    // Scrivere i dati PCM nel buffer I2S
    i2s_channel_write(tx_handle, (const char*)pcm_data, pcm_data_len * sizeof(int16_t), &bytes_written, 1000);
    return bytes_written;
}
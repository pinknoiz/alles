// alles.h

#ifndef __ALLES_H
#define __ALLES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_intr_alloc.h"
#include "esp_attr.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"

#include "driver/i2s.h"
#include "nvs_flash.h"
#include "lwip/netdb.h"

#include "wifi.h"

#define SAMPLE_RATE 44100

#define MAX_RECEIVE_LEN 127
#define UDP_PORT 3333
#define MULTICAST_TTL 1
#define MULTICAST_IPV4_ADDR "232.10.11.12"
#define PING_TIME_MS 10000

extern void mcast_listen_task(void *pvParameters);
extern void mcast_send(char * message, uint16_t len);
extern void create_multicast_ipv4_socket();
extern void update_map(uint8_t client, uint8_t ipv4, int64_t time);
extern void handle_sync(int64_t time, int8_t index);
extern uint8_t alive;
extern int64_t computed_delta; // can be negative no prob, but usually host is larger # than client
extern uint8_t computed_delta_set; // have we set a delta yet?
extern int16_t client_id;

// FM 
extern void fm_init();
extern void render_fm(float * buf, uint8_t voice); 
extern void fm_new_note_number(uint8_t voice);
extern void fm_new_note_freq(uint8_t voice);

// bandlimted oscillators
extern void oscillators_init();
extern void blip_the_buffer(float * ibuf, int16_t * obuf,  uint16_t len ) ;
extern void render_ks(float * buf, uint8_t voice); 
extern void render_sine(float * buf, uint8_t voice); 
extern void render_pulse(float * buf, uint8_t voice); 
extern void render_saw(float * buf, uint8_t voice); 
extern void render_triangle(float * buf, uint8_t voice); 
extern void render_noise(float * buf, uint8_t voice); 
extern void ks_new_note_freq(uint8_t voice); 

#define SINE_LUT_SIZE 16383

#define BLOCK_SIZE 256
#define VOICES 10 
#define SINE 0
#define PULSE 1
#define SAW 2
#define TRIANGLE 3
#define NOISE 4
#define FM 5
#define KS 6
#define OFF 7

#define EVENT_FIFO_LEN 400
#define EMPTY 0
#define SCHEDULED 1
#define PLAYED 2
#define LATENCY_MS 500
#define MAX_MS_DRIFT 2500

#define UP    16383
#define DOWN -16384

struct event {
    uint64_t time;
    int16_t voice;
    int16_t wave;
    int16_t patch;
    int16_t midi_note;
    float amp;
    float duty;
    float feedback;
    float freq;
    uint8_t status;
    int8_t velocity;
    float step;
    float substep;
    float sample;

};

#ifdef __cplusplus
}
#endif

#endif




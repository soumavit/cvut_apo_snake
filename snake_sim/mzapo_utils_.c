#include "mzapo_utils.h"


void my_sleep(struct timespec delay){
	if (delay.tv_sec != 0){
		sleep(delay.tv_sec);
		return;
	}
	usleep(delay.tv_nsec);
}


knobs_t* knobs_init(){
	knobs_t *k = malloc(sizeof(knobs_t));
	if (!k){
		fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
		exit(MEM_ALLOC_ERROR_KNOBS);
	}

	k->r = 0;
	k->g = 0;
	k->b = 0;

	k->r_pressed = false;
	k->g_pressed = false;
	k->b_pressed = false;

	return k;
}


void update_input(knobs_t* knobs){
	uint32_t value = *(volatile uint32_t*)(MEM_BASE + SPILED_REG_KNOBS_8BIT_o);

	knobs->b = value & 0xFF;
	knobs->g = (value >> 8) & 0xFF;
	knobs->r = (value >> 16) & 0xFF;

	knobs->b_pressed = (value>>24) & 0x01;
	knobs->g_pressed = (value>>25) & 0x01;
	knobs->r_pressed = (value>>26) & 0x01;
}


int get_input_red(knobs_t* new, knobs_t* old){

	if (old->r > SKIP_HIGH && new->r < SKIP_LOW){
		return 1;
	}

	if (old->r < SKIP_LOW && new->r > SKIP_HIGH){
		return -1;
	}

	if (((new->r - old->r) > STEP) || ((new->r - old->r) < -1*STEP)) {
		return new->r - old->r;
	}
	else {
		return 0;
	}
}


int get_input_green(knobs_t* new, knobs_t* old){
	if (old->g > SKIP_HIGH && new->g < SKIP_LOW){
		return 1;
	}

	if (old->g < SKIP_LOW && new->g > SKIP_HIGH){
		return -1;
	}

	if (((new->g - old->g) > STEP) || ((new->g - old->g) < -1*STEP)) {
		return new->g - old->g;
	}
	else {
		return 0;
	}
}


int get_input_blue(knobs_t* new, knobs_t* old){
	if (old->b > SKIP_HIGH && new->b < SKIP_LOW){
		return 1;
	}

	if (old->b < SKIP_LOW && new->b > SKIP_HIGH){
		return -1;
	}

	if (((new->b - old->b) > STEP) || ((new->b - old->b) < -1*STEP)) {
		return new->b - old->b;
	}
	else {
		return 0;
	}
}


bool get_press_red(knobs_t* knobs){
	return knobs->r_pressed;
}


bool get_press_green(knobs_t* knobs){
	return knobs->g_pressed;
}


bool get_press_blue(knobs_t* knobs){
	return knobs->b_pressed;
}


void refresh_display(unsigned int **buffer){
	parlcd_write_cmd(PARLCD_MEM_BASE, 0x2c);
  	for (int i = 0; i < HEIGHT ; i++) {
		for (int j = 0; j < WIDTH ; j++) {
			parlcd_write_data(PARLCD_MEM_BASE, buffer[i][j]);
		}
  	}
}


void set_led1(uint8_t r, uint8_t g, uint8_t b){
	uint32_t val = 0;
	val |= r;
	val<<= 8;
	val |= g;
	val <<= 8;
	val |= b;
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_RGB1_o ) = val;
}


void set_led2(uint8_t r, uint8_t g, uint8_t b){
	uint32_t val = 0;
	val |= r;
	val<<= 8;
	val |= g;
	val <<= 8;
	val |= b;
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_RGB2_o ) = val;
}


void set_leds(uint8_t r, uint8_t g, uint8_t b){
	set_led1(r, g, b);
	set_led2(r, g, b);
}


void set_ledline_on(int* ledline, int idx){
	*ledline |= (1 << idx);
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_LINE_o) = *ledline;
}


void set_ledline_off(int *ledline, int idx){
	*ledline &= ~(1 << idx);
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_LINE_o) = *ledline;
}


void reset_ledline(){
	int ledline = 0;
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_LINE_o) = ledline;
}


void fill_ledline(){
	int ledline = UINT32_MAX;
	*(volatile uint32_t*)(MEM_BASE + SPILED_REG_LED_LINE_o) = ledline;
}


void led_effect1(){
	int ledline = 0;
	for (int i = 31; i >= 0; i--){
		set_ledline_on(&ledline, i);
		usleep(2000);
	}
}


void led_effect2(){
	int ledline = UINT32_MAX;
	for (int i = 31; i >= 0; i--){
		set_ledline_off(&ledline, i);
		usleep(2000);
	}
}


void led_effect_game_over(){
	int ledline = 0;
	int sleep_usec = 3000;

	for (int j = 0; j < 4; j++){
		for (int i = 31; i >= 0; i--){
			set_ledline_on(&ledline, i);
			usleep(sleep_usec);
		}

		for (int i = 31; i >= 0; i--){
			set_ledline_off(&ledline, i);
			usleep(sleep_usec);
		}

		for (int i = 0; i <= 31; i++){
			set_ledline_on(&ledline, i);
			usleep(sleep_usec);
		}

		for (int i = 0; i <= 31; i++){
			set_ledline_off(&ledline, i);
			usleep(sleep_usec);
		}
	}

	for (int i = 31; i >= 0; i--){
		set_ledline_on(&ledline, i);
		usleep(sleep_usec);
	}

	//its a random number but it looks the best:)
	usleep(10000);
}

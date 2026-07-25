#include "firmware.h"
#include <assert.h>
#include <math.h>
static float pwm;static int feeds;
void board_pwm(float duty){pwm=duty;}void board_watchdog_feed(void){feeds++;}
int main(void){Motor m;motor_init(&m,.01f,.1f,0);m.target=1000;for(int i=0;i<100;i++)motor_tick(&m,0,(uint32_t)i*1000);assert(pwm==1&&m.integral==0);motor_tick(&m,NAN,100000);assert(m.fault&&pwm==0);motor_init(&m,.01f,.1f,0);motor_tick(&m,500,1000);motor_tick(&m,500,5000);assert(m.fault&&pwm==0);assert(feeds>0);}

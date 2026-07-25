#pragma once
#include <stdint.h>
typedef struct{float kp,ki,kd,integral,previous,target,output,history[8],sum;unsigned index,count;uint32_t last_us;int started,fault;}Motor;
void motor_init(Motor*m,float kp,float ki,float kd);float motor_tick(Motor*m,float sensor,uint32_t now_us);
void board_pwm(float duty);void board_watchdog_feed(void);

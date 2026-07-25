#include "firmware.h"
#include <string.h>
#include <math.h>
static float clamp(float x,float lo,float hi){return x<lo?lo:x>hi?hi:x;}
void motor_init(Motor*m,float kp,float ki,float kd){memset(m,0,sizeof(*m));m->kp=kp;m->ki=ki;m->kd=kd;}
float motor_tick(Motor*m,float sensor,uint32_t now){
 if(m->fault||!isfinite(sensor)||sensor<0||sensor>5000||(m->started&&(uint32_t)(now-m->last_us)>2000)){m->fault=1;m->output=0;board_pwm(0);return 0;}
 float dt=m->started?(float)(uint32_t)(now-m->last_us)/1000000.0f:.001f;
 if(dt<=0){m->fault=1;board_pwm(0);return 0;}
 m->last_us=now;m->started=1;m->sum-=m->history[m->index];m->history[m->index]=sensor;m->sum+=sensor;m->index=(m->index+1)%8;if(m->count<8)m->count++;
 float error=m->target-m->sum/m->count,derivative=(error-m->previous)/dt;
 float candidate=m->integral+error*dt,raw=m->kp*error+m->ki*candidate+m->kd*derivative;
 if((raw>=0&&raw<=1)||(raw>1&&error<0)||(raw<0&&error>0))m->integral=candidate;
 m->previous=error;m->output=clamp(m->kp*error+m->ki*m->integral+m->kd*derivative,0,1);board_pwm(m->output);board_watchdog_feed();return m->output;
}

# Motor and Sensor Control Firmware

Timer-driven 1 kHz control core with moving-average sensor filtering, PID control, conditional-integration anti-windup, PWM saturation, deadline detection, sensor fault cutoff, and watchdog adapter hooks.

## Run

Build host regression: `cc -std=c11 -Wall -Wextra test.c firmware.c -lm -o motor_test && ./motor_test`. A board adapter calls motor_tick every millisecond and maps PWM/watchdog callbacks to hardware.

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "Arduino.h"
#include "src/grbl/hal.h"
#include "clearcore.h"

#define console Serial0
#define BAUD_RATE 115200

void execute_realtime(sys_state_t state);
void settings_changed (settings_t *settings);
bool driver_setup(settings_t *settings);

static void limitsEnable (bool on, bool homing);
inline static limit_signals_t limitsGetState();
static void LIMIT_IRQHandler (void);                                                                                                


uint_fast16_t spindleGetPWM (float rpm);
void spindleUpdateRPM (float rpm);
void spindle_set_speed (uint_fast16_t pwm_value);
void stepperGoIdle (bool clear_signals);
void driver_delay_ms (uint32_t ms, void (*callback)(void));
control_signals_t systemGetState (void);
void spindleSetState (spindle_state_t state, float rpm);
void coolantSetState (coolant_state_t mode);



#define RX_BUFFER_SIZE 1024



bool nvsRead(uint8_t *dest);
bool nvsWrite(uint8_t *source);
bool nvsInit(void);

static void bitsSetAtomic (volatile uint_fast16_t *ptr, uint_fast16_t bits);
static uint_fast16_t bitsClearAtomic (volatile uint_fast16_t *ptr, uint_fast16_t bits);
static uint_fast16_t valueSetAtomic (volatile uint_fast16_t *ptr, uint_fast16_t value);






// guessing same53 is similar to d21
#define STEP_TIMER          TC3
#define STEP_TIMER_IRQn     TC3_IRQn

#define STEPPER_TIMER       TC4 // 32bit - TC4 & TC5 combined!
#define STEPPER_TIMER_IRQn  TC4_IRQn

#define DEBOUNCE_TIMER      TCC1
#define DEBOUNCE_TIMER_IRQn TCC1_IRQn





#endif


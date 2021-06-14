#include "Arduino.h"
#include "driver.h"
#include "serial.h"
#include "file.h"

#ifdef __cplusplus
extern "C" {
#endif

static axes_signals_t limit_ies;

bool driver_init() {
    hal.info =		    "SAME53";
    hal.driver_version =    __DATE__;
    hal.driver_options =    OPTIONS;
    hal.board =		    BOARD_NAME;

    serialInit();
    hal.stream.read = serialGetC;
    hal.stream.get_rx_buffer_available = serialRxFree;
    hal.stream.reset_read_buffer = serialRxFlush;
    hal.stream.cancel_read_buffer = serialRxCancel;
    hal.stream.suspend_read = serialSuspendInput;
    hal.stream.write = serialWriteS;
    hal.stream.write_all = serialWriteS;
    hal.stream.write_char = serialPutC;

    hal.driver_cap.variable_spindle = Off;
    hal.driver_cap.mist_control = On;
    hal.driver_cap.software_debounce = On;
    hal.driver_cap.step_pulse_delay = On;                                                                             
    hal.driver_cap.amass_level = 3;
    hal.driver_cap.control_pull_up = On;
    hal.driver_cap.limits_pull_up = On;
    hal.driver_cap.probe_pull_up = On;

    hal.driver_cap.amass_level = 3;                                                                                   
    hal.settings_changed = settings_changed;

    hal.driver_setup = driver_setup;

    hal.limits.enable = limitsEnable;
    hal.limits.get_state = limitsGetState;

    hal.spindle.set_state = spindleSetState;

    hal.stepper.go_idle = stepperGoIdle;

    hal.spindle.get_pwm = spindleGetPWM;
    hal.spindle.update_pwm = spindle_set_speed;

    hal.delay_ms = driver_delay_ms; 

    hal.control.get_state = systemGetState;
    hal.coolant.set_state = coolantSetState;

    grbl.on_execute_realtime = execute_realtime;

    sdInit();
    hal.nvs.type		= NVS_Flash; // NVS_Flash matches closest to SD card
    hal.nvs.memcpy_from_flash	= sdSettingsRead;
    hal.nvs.memcpy_to_flash	= sdSettingsWrite;
    hal.nvs.get_byte		= sdSettingsGetByte;
    hal.nvs.put_byte		= sdSettingsPutByte;

    return 1;
}

static void limitsEnable (bool on, bool homing) {
    on = on && settings.limits.flags.hard_enabled;
    if(on) {
        attachInterrupt(X_LIMIT_PIN, LIMIT_IRQHandler, limit_ies.x ? FALLING : RISING);
	attachInterrupt(Y_LIMIT_PIN, LIMIT_IRQHandler, limit_ies.y ? FALLING : RISING);
	attachInterrupt(Z_LIMIT_PIN, LIMIT_IRQHandler, limit_ies.z ? FALLING : RISING);
    } else {
        detachInterrupt(X_LIMIT_PIN);
        detachInterrupt(Y_LIMIT_PIN);
        detachInterrupt(Z_LIMIT_PIN);
    }
}

void settings_changed (settings_t *settings){
}


void execute_realtime(sys_state_t state) {
}

bool driver_setup(settings_t *settings) {
    return 1;
}

uint_fast16_t spindleGetPWM (float rpm) {
    // return spindle_compute_pwm_value(&spindle_pwm, rpm, false);
    return 0;
}

void spindleUpdateRPM (float rpm) {
    // spindle_set_speed(spindle_compute_pwm_value(&spindle_pwm, rpm, false));
}

void spindle_set_speed (uint_fast16_t pwm_value) {
}

inline static limit_signals_t limitsGetState() {
}

static void LIMIT_IRQHandler(void) {
    if(hal.driver_cap.software_debounce) {
        DEBOUNCE_TIMER->CTRLBSET.bit.CMD = TCC_CTRLBCLR_CMD_RETRIGGER_Val;
        while(DEBOUNCE_TIMER->SYNCBUSY.bit.CTRLB);
    } else
        hal.limits.interrupt_callback(limitsGetState());
}



void stepperGoIdle (bool clear_signals) {
}

void driver_delay_ms (uint32_t ms, void (*callback)(void)){
}

control_signals_t systemGetState (void) {
    control_signals_t signals;

    signals.value = settings.control_invert.mask;
    signals.reset = 0; // pinIn(RESET_PIN);
    signals.feed_hold = 1;// pinIn(FEED_HOLD_PIN);
    signals.cycle_start = 0; // pinIn(CYCLE_START_PIN);

#ifdef ENABLE_SAFETY_DOOR_INPUT_PIN
    signals.safety_door_ajar = pinIn(SAFETY_DOOR_PIN);
#endif

    if(settings.control_invert.mask)
        signals.value ^= settings.control_invert.mask;

    return signals;
}

void spindleSetState (spindle_state_t state, float rpm) {
}

void coolantSetState (coolant_state_t mode) {
}

#ifdef __cplusplus
}
#endif

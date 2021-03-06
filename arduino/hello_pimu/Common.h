/*
  -------------------------------------------------------------
  Hello Robot - Hello Pimu
  
  All materials released under the GNU General Public License v3.0 (GNU GPLv3).
  
  https://www.gnu.org/licenses/gpl-3.0.html

  Copyright (c) 2020 by Hello Robot Inc. All rights reserved.
  --------------------------------------------------------------
*/

#ifndef __COMMON_H__
#define __COMMON_H__

#include "Arduino.h"

/////////////////////////////////////////////////////////////////
//Version History
// Pimu.V0.1: Initial production release for RE1
#define FIRMWARE_VERSION "Pimu.v0.0.1p0"
#define BOARD_VERSION "Pimu.Guthrie.V1"

/////////////////////////////////////////////////////////////////
#define BEEP_ID_OFF 0
#define BEEP_ID_SINGLE_SHORT 1
#define BEEP_ID_SINGLE_LONG 2
#define BEEP_ID_DOUBLE_SHORT 3
#define BEEP_ID_DOUBLE_LONG 4

/////////////////////////////////////////////////////////////////
#define RPC_SET_PIMU_CONFIG 1
#define RPC_REPLY_PIMU_CONFIG 2
#define RPC_GET_PIMU_STATUS 3
#define RPC_REPLY_PIMU_STATUS 4
#define RPC_SET_PIMU_TRIGGER 5
#define RPC_REPLY_PIMU_TRIGGER 6
#define RPC_GET_PIMU_BOARD_INFO 7
#define RPC_REPLY_PIMU_BOARD_INFO 8
#define RPC_SET_MOTOR_SYNC 9
#define RPC_REPLY_MOTOR_SYNC 10
/////////////////////////////////////////////////////////////////
//From hello_pimu/variants.h
#define ANA_V_BATT A0
#define ANA_CLIFF_0 A1
#define ANA_CLIFF_1 A2
#define ANA_CLIFF_2 A3
#define ANA_CLIFF_3 A4
#define ANA_TEMP A5
#define ANA_CURRENT A6

#define RUNSTOP_SW D0
#define LED D3
#define RUNSTOP_LED D5
#define RUNSTOP_M0 D7
#define RUNSTOP_M1 D8
#define RUNSTOP_M2 D9
#define RUNSTOP_M3 D10
#define FAN_FET D2
#define BUZZER D1
#define IMU_RESET D6

/////////////////////////////////////////////////////////////////
#define NUM_CLIFF 4

#define STATE_AT_CLIFF_0 1
#define STATE_AT_CLIFF_1 2
#define STATE_AT_CLIFF_2 4
#define STATE_AT_CLIFF_3 8
#define STATE_RUNSTOP_EVENT 16
#define STATE_CLIFF_EVENT 32
#define STATE_FAN_ON 64
#define STATE_BUZZER_ON 128
#define STATE_LOW_VOLTAGE_ALERT 256
#define STATE_OVER_TILT_ALERT 512
#define STATE_HIGH_CURRENT_ALERT 1024

#define TRIGGER_BOARD_RESET  1
#define TRIGGER_RUNSTOP_RESET  2
#define TRIGGER_CLIFF_EVENT_RESET 4
#define TRIGGER_BUZZER_ON  8
#define TRIGGER_BUZZER_OFF  16
#define TRIGGER_FAN_ON  32
#define TRIGGER_FAN_OFF  64
#define TRIGGER_IMU_RESET 128
#define TRIGGER_RUNSTOP_ON 256
#define TRIGGER_BEEP 512

/////////////////////////////////////////////////////////////////

//Note, to serialize to Linux must pack structs given use of sizeof()
//See https://arduino.stackexchange.com/questions/9899/serial-structure-data-transfer-between-an-arduino-and-a-linux-pc

struct __attribute__ ((packed)) IMU_Status{
  
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float mx;
  float my;
  float mz;
  float roll; //-180 to 180, rolls over
  float pitch; //-90 to  90, rolls over at 180
  float heading; //0-360.0, rolls over
  float qw;
  float qx;
  float qy;
  float qz;
  float bump;
  uint32_t timestamp;
};

/////////////////////////////////////////////////////////////////

struct __attribute__ ((packed)) Pimu_Config{
  float cliff_zero[NUM_CLIFF];
  float cliff_thresh;
  float cliff_LPF; //Hz rolloff
  float voltage_LPF; 
  float current_LPF;
  float temp_LPF;
  uint8_t stop_at_cliff;
  uint8_t stop_at_runstop;
  uint8_t stop_at_tilt;
  uint8_t stop_at_low_voltage;
  uint8_t stop_at_high_current;
  float mag_offsets[3];
  float mag_softiron_matrix[9];
  float gyro_zero_offsets[3];
  float rate_gyro_vector_scale;
  float gravity_vector_scale;
  float accel_LPF;
  float bump_thresh;
  float low_voltage_alert;
  float high_current_alert;
  float over_tilt_alert;
};

struct __attribute__ ((packed)) Pimu_Status{
  IMU_Status imu;
  float voltage;
  float current;
  float temp;
  float cliff_range[NUM_CLIFF];
  uint32_t state;      
  uint32_t timestamp; //us
  uint16_t bump_event_cnt;
  float debug;
};

struct __attribute__ ((packed)) Pimu_Trigger{
  uint32_t data;
};

struct __attribute__ ((packed)) Pimu_Board_Info{
  char board_version[20];
  char firmware_version[20];
};

/////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////

#endif

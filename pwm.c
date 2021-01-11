/*
 * pwm.c:
 *	This tests the hardware PWM channel.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "pitches.h"

#define servopin 23
#define buzzpin 23
#define pwmpin 23

int pwm_led_test( void )
{
    int i;
    int bright ;

    wiringPiSetup();
    pinMode( pwmpin, PWM_OUTPUT );
    pwmSetMode( PWM_MODE_MS );
    pwmSetClock( 500 );
    pwmSetRange( 1024 );
    pwmWrite( pwmpin, 0 );

    for ( i=0; i<10; i++ )
    {
        for ( bright = 0; bright < 1024; bright=bright+4 )
        {
            pwmWrite( pwmpin, bright );
            delay( 5 );
        }

        for ( bright = 1023; bright >= 0; bright=bright-4 )
        {
            pwmWrite( pwmpin, bright );
            delay( 5 );
        }
    }

    pwmWrite( pwmpin, 0 );
    return 0;
}

/*
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
*/
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
};

void tone( int melody, int duration ) {
    int period;

    if (melody == 0) {
       usleep( duration );
       usleep( duration / 5 );
    } else {
       period = 200000 / melody;    // 100 MHz / 500 = 200 KHz
       pwmSetRange( period );
       pwmWrite( buzzpin, period / 2 );
       usleep( duration );
       pwmWrite( buzzpin, 0 );
       usleep( duration / 5 );
    }
}

int tongsong(void)
{
    int i;
    int noteDuration;

    wiringPiSetup();
    pinMode( buzzpin, PWM_OUTPUT );
    pwmSetMode( PWM_MODE_MS );
    pwmSetClock( 500 );
    pwmSetRange( 4000 );
    pwmWrite( buzzpin, 0 );

    for (i = 0; i < 48; i++) {
       noteDuration = 1000000 / noteDurations[i];
       tone( melody[i], noteDuration );
    }

    pwmWrite( buzzpin, 0 );
    return 0;
}

int servo( void )
{
    int i;

    wiringPiSetup();
    pinMode( servopin, PWM_OUTPUT );
    pwmSetMode( PWM_MODE_MS );
    pwmSetClock( 500 );          // 100 MHz / 500 / 4000 = 50 Hz
    pwmSetRange( 4000 );
    pwmWrite( servopin, 225 );   // min 105 = 0 degree, max 345 = 180 degree
    printf("90 degree\n");
    delay( 1000 );

    for ( i=0; i<3; i++ )
    {
        pwmWrite( servopin, 105);
        printf("0 degree\n");
        delay( 1000 );
        pwmWrite( servopin, 225);
        printf("90 degree\n");
        delay( 1000 );
        pwmWrite( servopin, 345);
        printf("180 degree\n");
        delay( 1000 );
        pwmWrite( servopin, 225);
        printf("90 degree\n");
        delay( 1000 );
    }

    pwmWrite( servopin, 0 );
    return 0;
}

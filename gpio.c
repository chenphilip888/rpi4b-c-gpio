/*
 * blink.c:
 *	Standard "blink" program in wiringPi. Blinks an LED connected
 *	to the first GPIO pin.
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

#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is ASSU_PI_GPIO 164.

#define	LED	5
#define SWITCH  4

int led_test( void )
{
  int i;

  printf ("Raspberry pi blink led test\n") ;

  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;

  for (i=0; i<5; i++)
  {
    digitalWrite (LED, HIGH) ;	// On
    delay (500) ;		// mS
    digitalWrite (LED, LOW) ;	// Off
    delay (500) ;
  }
  return 0 ;
}

int button_test( void )
{
  int i;
  int old_state;
  int current_state;

  printf ("Raspberry pi button led test.\nPush button 10 times\n") ;

  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  pinMode (SWITCH, INPUT) ;

  old_state = 0;
  for (i=0; i<10; )
  {
    current_state = digitalRead (SWITCH) ;
    if ( old_state == 0 && current_state == 1 ) {
        digitalWrite (LED, HIGH) ;	// On
	old_state = current_state;
    } else if ( old_state == 1 && current_state == 0 ) {
        digitalWrite (LED, LOW) ;	// Off
	old_state = current_state;
	i++;
    }
    delay (50) ;  // 50 ms
  }
  return 0 ;
}

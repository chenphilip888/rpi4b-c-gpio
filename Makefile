gpio_test: gpio_test.c uart.c gpio.c pwm.c i2c.c spi.c
	gcc -g $^ -lwiringPi -o $@

.PHONY: gpio_test

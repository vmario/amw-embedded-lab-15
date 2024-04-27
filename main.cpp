#include "lcdDisplay.hpp"
#include "adc.hpp"

#include <avr/interrupt.h>

#include <stdio.h>

constexpr uint8_t DISPLAY_LENGTH{16}; ///< Szerokość wyświetlacza.

/**
 * Wykonuje pomiar klawiatury i wyświetla go.
 */
void printMeasurement()
{
	char buf[DISPLAY_LENGTH + 1];

	uint16_t measurement{adc.measure()};
	snprintf(buf, sizeof(buf), "%4u", measurement);
	lcdDisplay.goTo(0, 4);
	lcdDisplay.write(buf);

	double temperature = 1.1 * measurement / 1024 * 100;
	snprintf(buf, sizeof(buf), "%5.2f", temperature);
	lcdDisplay.goTo(1, 5);
	lcdDisplay.write(buf);
}

/**
 * Funkcja główna.
 */
int main()
{
	constexpr uint8_t DEGREE[] = {
	    0b00000010,
	    0b00000101,
	    0b00000010,
	    0b00000000,
	    0b00000000,
	    0b00000000,
	    0b00000000,
	    0b00000000,
	};

	lcdDisplay.initialize();
	lcdDisplay.addSymbol(DEGREE, 0);
	adc.initialize();
	sei();

	lcdDisplay.goTo(0, 0);
	lcdDisplay.write("ADC:");

	lcdDisplay.goTo(1, 0);
	lcdDisplay.write("TEMP:      C");
	lcdDisplay.goTo(1, 10);
	lcdDisplay.write('\x00');

	while (true) {
		printMeasurement();
	}
}

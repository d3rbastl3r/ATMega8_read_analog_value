/**
 * A minimal example to use the ADC to read analog values
 * The precision in the example is 8 bit. If more precision is required the ADCL must be read first, then ADCH.
 * The AVCC should be connected to VCC and a 100nF capacitor between AVCC and GND is required.
 *
 * ## Prescaling and Conversion Timing (Page 191 on datasheet)
 * "By default, the successive approximation circuitry requires an input clock frequency between
 * 50kHz and 200kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the
 * input clock frequency to the ADC can be higher than 200kHz to get a higher sample rate."
 *
 * @author Igor Martens
 * @since 06.10.2018
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void initADC() {
    ADMUX |=
        // left shift result
        (1 << ADLAR) |

        // AREF, Internal V ref turned off
        (0 << REFS1) |
        (1 << REFS0) |

        // use ADC0 for input (PC0), MUX3..0 = 0000
        (0 << MUX3)  |
        (0 << MUX2)  |
        (0 << MUX1)  |
        (0 << MUX0);

    ADCSRA =
        // Enable ADC
        (1 << ADEN)  |

        // no prescaler is required, we use only 8bit resolution
        (0 << ADPS2) |
        (0 << ADPS1) |
        (0 << ADPS0);
}

void setup() {
    initADC();
}

int main(void) {
    setup();

    while(1) {
        ADCSRA |= (1 << ADSC);         // start ADC measurement
        while (ADCSRA & (1 << ADSC));  // wait till conversion complete

        uint8_t val = ADCH;            // read value from ADC
        if (val > 128) {
            // Do something
        }
    }

    return 0;
}

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>


int led_state1 = 0;
int led_state2 = 0;
int led_state3 = 0;

bool flag1 = false;
bool flag2 = false;

void interrupt_init() 
{
    GIMSK |= (1 << PCIE_B1);
    GIMSK |= (1 << PCIE_B2);
    PCMSK_B1 |= (1 << B1);
    PCMSK_B2 |= (1 << B2);
}

#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
ISR(PCINT1_vect, ISR_ALIASOF(PCINT0_vect));
ISR(PCINT0_vect) 
{
    _delay_ms(50);

    if (!(PIN_B1 & (1 << B1))) 
    { 
        if (!flag1) 
        {
            led_state1 = !led_state1;
            flag1 = true;
        }
        _delay_ms(10);
    } 
    else 
    {
        flag1 = false;
    }
    
    if (!(PIN_B2 & (1 << B2))) 
    { 
        if (!flag2) 
        {
            led_state2 = !led_state2;
            flag2 = true;
        }
        _delay_ms(10);
    } 
    else 
    {
        flag2 = false;
    }
    
    led_state3 = led_state1 && led_state2;
}
#else
ISR(PCINT0_vect) 
{
    _delay_ms(50);

    if (!(PIN_B1 & (1 << B1))) 
    { 
        if (!flag1) 
        {
            led_state1 = !led_state1;
            flag1 = true;
        }
        _delay_ms(10);
    } 
    else 
    {
        flag1 = false;
    }
    
    if (!(PIN_B2 & (1 << B2))) 
    { 
        if (!flag2) 
        {
            led_state2 = !led_state2;
            flag2 = true;
        }
        _delay_ms(10);
    } 
    else 
    {
        flag2 = false;
    }
    
    led_state3 = led_state1 && led_state2;
}
#endif

int main(void) 
{
    DDR_L1 |= (1 << LED1);
    DDR_L2 |= (1 << LED2);
    DDR_L3 |= (1 << LED3); // Set LED pins as outputs
    DDR_B1 &= ~(1 << B1); // Set button pins as inputs
    DDR_B2 &= ~(1 << B2);

    PORT_B1 |= (1 << B1); // Enable internal pull-up resistors on button pins
    PORT_B2 |= (1 << B2); // Enable internal pull-up resistors on button pins

    interrupt_init();

    sei(); // Enable global interrupts

    while (1) {
        // Устанавливаем состояния светодиодов
        if (led_state1) {
            PORT_L1 |= (1 << LED1); // Включаем светодиод 1
        } else {
            PORT_L1 &= ~(1 << LED1); // Выключаем светодиод 1
        }
        if (led_state2) {
            PORT_L2 |= (1 << LED2); // Включаем светодиод 2
        } else {
            PORT_L2 &= ~(1 << LED2); // Выключаем светодиод 2
        }
        if (led_state3) {
            PORT_L3 |= (1 << LED3); // Включаем светодиод 3
        } else {
            PORT_L3 &= ~(1 << LED3); // Выключаем светодиод 3
        }
    }

    return 0;
}

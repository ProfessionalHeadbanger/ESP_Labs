#define F_CPU 1000000UL // Устанавливаем частоту микроконтроллера (1 МГц)
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

// Глобальные переменные для хранения состояний светодиодов
volatile int led_state1 = 0;
volatile int led_state2 = 0;
volatile int led_state3 = 0;

volatile bool flag1 = false;
volatile bool flag2 = false;
volatile bool flag3 = false;

// Функция для инициализации внешнего прерывания INT0
void interrupt_init() 
{
    GIMSK |= (1 << PCIE0); // Разрешить прерывания по изменению состояния на порту A
    PCMSK0 |= (1 << PCINT6) | (1 << PCINT7); // Разрешить прерывания на пинах PA6 и PA7
}

// Обработчик внешнего прерывания на PA6 и PA7
ISR(PCINT0_vect) 
{
    _delay_ms(50); // Ждем, чтобы избежать дребезга контактов
    // Проверяем состояние кнопок и устанавливаем соответствующие значения переменных состояния светодиодов
    if (!(PINA & (1 << PA7))) // Если кнопка для светодиода 1 нажата
    { 
        if (!flag1) 
        {
            led_state1 = !led_state1;
            flag1 = true;
        }
        _delay_ms(10); // Ждем, чтобы избежать дребезга контактов
    } 
    else 
    {
        flag1 = false;
    }
    if (!(PINA & (1 << PA6))) // Если кнопка для светодиода 2 нажата
    { 
        if (!flag2) 
        {
            led_state2 = !led_state2;
            flag2 = true;
        }
        _delay_ms(10); // Ждем, чтобы избежать дребезга контактов
    } 
    else 
    {
        flag2 = false;
    }
    // Светодиод 3 горит только если горят 1 и 2 (логическое И)
    led_state3 = led_state1 && led_state2;
}

int main(void) {
    // Настройка пинов
    DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3); // PB1, PB2, PB3 на выходы (светодиоды)
    DDRA &= ~((1 << PA6) | (1 << PA7)); // PA6 и PA7 на входы (кнопки)

    PORTA |= (1 << PA6) | (1 << PA7); // Подключение внутренних подтягивающих резисторов к PA6 и PA7
    PORTB |= (1 << PB0); // Подключаем подтягивающий резистор к PB0 (переключатель)

    // Инициализация прерывания
    interrupt_init();

    // Разрешаем прерывания глобально
    sei();

    while (1) {
        // Устанавливаем состояния светодиодов
        if (led_state1) {
            PORTB |= (1 << PB1); // Включаем светодиод 1
        } else {
            PORTB &= ~(1 << PB1); // Выключаем светодиод 1
        }
        if (led_state2) {
            PORTB |= (1 << PB2); // Включаем светодиод 2
        } else {
            PORTB &= ~(1 << PB2); // Выключаем светодиод 2
        }
        if (led_state3) {
            PORTB |= (1 << PB3); // Включаем светодиод 3
        } else {
            PORTB &= ~(1 << PB3); // Выключаем светодиод 3
        }
    }

    return 0;
}

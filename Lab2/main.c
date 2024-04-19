
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

// Глобальные переменные для хранения состояний светодиодов
int led_state1 = 0;
int led_state2 = 0;
int led_state3 = 0;

bool flag1 = false;
bool flag2 = false;

// Функция для инициализации внешнего прерывания INT0
void interrupt_init() 
{
    GIMSK |= (1 << PCIE_B1);
    GIMSK |= (1 << PCIE_B2);
    PCMSK_B1 |= (1 << BUTTON1);
    PCMSK_B2 |= (1 << BUTTON2);
}

// Обработчик внешнего прерывания на PA6 и PA7
ISR(PCINT0_vect) 
{
    _delay_ms(50); // Ждем, чтобы избежать дребезга контактов
    // Проверяем состояние кнопок и устанавливаем соответствующие значения переменных состояния светодиодов
    if (!(PIN_B1 & (1 << BUTTON1))) // Если кнопка для светодиода 1 нажата
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
    if (!(PIN_B2 & (1 << BUTTON2))) // Если кнопка для светодиода 2 нажата
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
    // Светодиоды на выход
    DDR_L1 |= (1 << LED1);
    DDR_L2 |= (1 << LED2);
    DDR_L3 |= (1 << LED3);
    // Кнопки на вход
    DDR_B1 &= ~(1 << BUTTON1);
    DDR_B2 &= ~(1 << BUTTON2);
    // Подтягивающие резисторы на кнопки
    PORT_B1 |= (1 << BUTTON1);
    PORT_B2 |= (1 << BUTTON2);

    // Инициализация прерывания
    interrupt_init();

    // Разрешаем прерывания глобально
    sei();

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

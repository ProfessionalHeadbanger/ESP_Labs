include config.mk

F_CPU=16000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c

ifeq ($(findstring B, $(LED1)), B)
	DDR_L1=DDRB
	PORT_L1=PORTB
	PIN_L1=PINB
else
	DDR_L1=DDRA
	PORT_L1=PORTA
	PIN_L1=PINA
endif

ifeq ($(findstring B, $(LED2)), B)
	DDR_L2=DDRB
	PORT_L2=PORTB
	PIN_L2=PINB
else
	DDR_L2=DDRA
	PORT_L2=PORTA
	PIN_L2=PINA
endif

ifeq ($(findstring B, $(LED3)), B)
	DDR_L3=DDRB
	PORT_L3=PORTB
	PIN_L3=PINB
else
	DDR_L3=DDRA
	PORT_L3=PORTA
	PIN_L3=PINA
endif


ifeq ($(MCU), attiny25)
	DDR_B1=DDRB
	PORT_B1=PORTB
	PIN_B1=PINB
	PCIE_B1=PCIE
	PCMSK_B1=PCMSK
else ifeq ($(MCU), attiny45)
	DDR_B1=DDRB
	PORT_B1=PORTB
	PIN_B1=PINB
	PCIE_B1=PCIE
	PCMSK_B1=PCMSK
else ifeq ($(MCU), attiny85)
	DDR_B1=DDRB
	PORT_B1=PORTB
	PIN_B1=PINB
	PCIE_B1=PCIE
	PCMSK_B1=PCMSK
else ifeq ($(MCU), attiny13)
	DDR_B1=DDRB
	PORT_B1=PORTB
	PIN_B1=PINB
	PCIE_B1=PCIE
	PCMSK_B1=PCMSK
else ifeq ($(MCU), attiny24)
    ifeq ($(findstring B, $(B1)), B)
    	DDR_B1=DDRB
    	PORT_B1=PORTB
    	PIN_B1=PINB
    	PCIE_B1=PCIE1
    	PCMSK_B1=PCMSK1
    else 
    	DDR_B1=DDRA
    	PORT_B1=PORTA
    	PIN_B1=PINA
    	PCIE_B1=PCIE0
    	PCMSK_B1=PCMSK0
	endif
else ifeq ($(MCU), attiny44)
	ifeq ($(findstring B, $(B1)), B)
    	DDR_B1=DDRB
    	PORT_B1=PORTB
    	PIN_B1=PINB
    	PCIE_B1=PCIE1
    	PCMSK_B1=PCMSK1
    else 
    	DDR_B1=DDRA
    	PORT_B1=PORTA
    	PIN_B1=PINA
    	PCIE_B1=PCIE0
    	PCMSK_B1=PCMSK0
	endif
else ifeq ($(MCU), attiny84)
	ifeq ($(findstring B, $(B1)), B)
    	DDR_B1=DDRB
    	PORT_B1=PORTB
    	PIN_B1=PINB
    	PCIE_B1=PCIE1
    	PCMSK_B1=PCMSK1
    else 
    	DDR_B1=DDRA
    	PORT_B1=PORTA
    	PIN_B1=PINA
    	PCIE_B1=PCIE0
    	PCMSK_B1=PCMSK0
	endif
endif

ifeq ($(MCU), attiny25)
	DDR_B2=DDRB
	PORT_B2=PORTB
	PIN_B2=PINB
	PCIE_B2=PCIE
	PCMSK_B2=PCMSK
else ifeq ($(MCU), attiny45)
	DDR_B2=DDRB
	PORT_B2=PORTB
	PIN_B2=PINB
	PCIE_B2=PCIE
	PCMSK_B2=PCMSK
else ifeq ($(MCU), attiny85)
	DDR_B2=DDRB
	PORT_B2=PORTB
	PIN_B2=PINB
	PCIE_B2=PCIE
	PCMSK_B2=PCMSK
else ifeq ($(MCU), attiny13)
	DDR_B2=DDRB
	PORT_B2=PORTB
	PIN_B2=PINB
	PCIE_B2=PCIE
	PCMSK_B2=PCMSK
else ifeq ($(MCU), attiny24)
    ifeq ($(findstring B, $(B2)), B)
    	DDR_B2=DDRB
    	PORT_B2=PORTB
    	PIN_B2=PINB
    	PCIE_B2=PCIE1
    	PCMSK_B2=PCMSK1
    else 
    	DDR_B2=DDRA
    	PORT_B2=PORTA
    	PIN_B2=PINA
    	PCIE_B2=PCIE0
    	PCMSK_B2=PCMSK0
	endif
else ifeq ($(MCU), attiny44)
	ifeq ($(findstring B, $(B2)), B)
    	DDR_B2=DDRB
    	PORT_B2=PORTB
    	PIN_B2=PINB
    	PCIE_B2=PCIE1
    	PCMSK_B2=PCMSK1
    else 
    	DDR_B2=DDRA
    	PORT_B2=PORTA
    	PIN_B2=PINA
    	PCIE_B2=PCIE0
    	PCMSK_B2=PCMSK0
	endif
else ifeq ($(MCU), attiny84)
	ifeq ($(findstring B, $(B2)), B)
    	DDR_B2=DDRB
    	PORT_B2=PORTB
    	PIN_B2=PINB
    	PCIE_B2=PCIE1
    	PCMSK_B2=PCMSK1
    else 
    	DDR_B2=DDRA
    	PORT_B2=PORTA
    	PIN_B2=PINA
    	PCIE_B2=PCIE0
    	PCMSK_B2=PCMSK0
	endif
endif


all:
	${CC} ${CFLAGS} -DMCU=${MCU} \
	-DLED1=${LED1} -DLED2=${LED2} -DLED3=${LED3} \
	-DB1=${B1} -DB2=${B2} \
	-DDDR_L1=${DDR_L1} -DPORT_L1=${PORT_L1} -DPIN_L1=${PIN_L1} \
	-DDDR_L2=${DDR_L2} -DPORT_L2=${PORT_L2} -DPIN_L2=${PIN_L2} \
	-DDDR_L3=${DDR_L3} -DPORT_L3=${PORT_L3} -DPIN_L3=${PIN_L3} \
	-DDDR_B1=${DDR_B1} -DPORT_B1=${PORT_B1} -DPIN_B1=${PIN_B1} \
	-DDDR_B2=${DDR_B2} -DPORT_B2=${PORT_B2} -DPIN_B2=${PIN_B2} \
	-DPCIE_B1=${PCIE_B1} -DPCIE_B2=${PCIE_B2} \
	-DPCMSK_B1=${PCMSK_B1} -DPCMSK_B2=${PCMSK_B2} \
	-o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

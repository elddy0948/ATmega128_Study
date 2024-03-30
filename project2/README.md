# Monitoring program

## Contents

1. [Hardware](#hardware)
2. [External interrupt](#external-interrupt)
3. [UART](#uart)
4. [Timer](#timer)
5. [ADC](#adc)
6. [Seven segments](#seven-segments)

## Hardware

- 8bit AVR core (ATmega128)


## External interrupt

### Interrupt Service Routine

4개의 Switch를 사용한 External interrupt를 구현했습니다.

```C
ISR(INT4_vect)
{
	cli();
	EINT4_FLAG_BIT = 1;
	sei();
}

ISR(INT5_vect)
{
	cli();
	EINT5_FLAG_BIT = 1;
	sei();
}

ISR(INT6_vect)
{
	cli();
	EINT6_FLAG_BIT = 1;
	sei();
}

ISR(INT7_vect)
{
	cli();
	EINT7_FLAG_BIT = 1;
	sei();
}
```

### Interrupt initialize

```C
void EINT_enable_all(void)
{
	EINT4_init();
	EINT5_init();
	EINT6_init();
	EINT7_init();
}
void EINT4_init(void) {
	EIMSK |= (1 << INT4);
	EICRB |= (1 << ISC41) | (1 << ISC40);
}

// ... EINT5 ~ 7 ...
```

## UART

UART를 사용하여 PC와 통신하며 데이터를 주고 받았습니다.

### UART Interrupt Service Routine

```C
ISR(USART0_RX_vect)
{
	cli();

	UART0_RX_FLAG_BIT = 1;
	data = UDR0;
	switch(data)
	{
		case '4':
		EINT4_ENABLE_FLAG_BIT = 1;
		break;
		case '5':
		EINT5_ENABLE_FLAG_BIT = 1;
		break;
		case '6':
		EINT6_ENABLE_FLAG_BIT = 1;
		break;
		case '7':
		EINT7_ENABLE_FLAG_BIT = 1;
		break;
		default:
		break;
	}

	sei();
}
```

### UART Initialize

```C
void UART0_init()
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

	UBRR0H = BAUD_RATE_H;
	UBRR0L = BAUD_RATE_L;
}
```

## Timer

총 3개의 타이머를 사용하였고, Overflow timer 2개, Compare timer 1개를 사용했습니다.

### Timer Interrupt Service Routine

```C
ISR(TIMER0_OVF_vect)
{
	cli();
	timer0_count++;
	if(timer0_count >= BASE_COUNT)
	{
		TIMER0_OVF_FLAG_BIT = 1;
		timer0_count = 0;
	}
	TCNT0 = TCNT0_BASE;

	sei();
}

ISR(TIMER2_OVF_vect)
{
	cli();

	timer2_count++;
	if(timer2_count >= 200)
	{
		TIMER2_OVF_FLAG_BIT = 1;
		timer2_count = 0;
	}
	TCNT2 = TCNT2_BASE;

	sei();
}

ISR(TIMER1_COMPA_vect)
{
	cli();
	timer1_count++;
	if(timer1_count >= 10)
	{
		TIMER1_COMPA_FLAG_BIT = 1;
		timer1_count = 0;
	}
	TCNT1 = 0;
	sei();
}
```

### Timer Initialize

```C
void TIMER0_ovf_init(uint16_t cnt)
{
	timer0_count = 0;

	BASE_COUNT = cnt;
	TIMSK |= (1 << TOIE0);
	TCNT0 = TCNT0_BASE;
	TCCR0 |= (1 << CS02) | (1 << CS01);
}

void TIMER1_compa_init(void)
{
	timer1_count = 0;
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << WGM12);
	OCR1AH = OCR1_H;
	OCR1AL = OCR1_L;
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

// TIMER2 initialize ...
```

## ADC

ADC를 활용하여 온도 측정을 진행했습니다.

### ADC Interrupt Service Routine

```C
ISR(ADC_vect)
{
	cli();
	adc_value = (int)ADCL + ((int)ADCH << 8);
	if(adc_flag == TEMP_FLAG)
		adc_flag = ADC_TEMP_COMPLETE_FLAG;
	else if(adc_flag == VCC_FLAG)
		adc_flag = ADC_VCC_COMPLETE_FLAG;
	sei();
}
```

### ADC Initialize

```C
void ADC_init(uint8_t flag, uint8_t target, uint8_t adfr)
{
	adc_flag = flag;

	ADMUX |= target;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADIE);
	ADCSRA |= adfr;
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADSC);
}
```

## Seven segments

Seven segments를 활용해 온도값, 생일 등을 display했습니다.

### Segments initalize

```C
void SEG_init(void)
{
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRG = 0x0F;

	PORTB = 0x00;
	PORTD = 0x00;
	PORTG = 0x0F;
}
```


### Display 4byte

```C
void SEG_display_4byte(uint32_t val)
{
	PORTG = 0x08;
	PORTD = ((val & 0x0000000F) << 4) | (PORTD & 0x0F);
	PORTB = (val & 0x000000F0) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x04;
	PORTD = ((val & 0x00000F00) >> 4) | (PORTD & 0x0F);
	PORTB = ((val & 0x0000F000) >> 8) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x02;
	PORTD = ((val & 0x000F0000) >> 12) | (PORTD & 0x0F);
	PORTB = ((val & 0x00F00000) >>16) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x01;
	PORTD = ((val & 0x0F000000) >> 20) | (PORTD & 0x0F);
	PORTB = ((val & 0xF0000000) >> 24) | (PORTB & 0x0F);
	_delay_ms(2);
}
```

### Display digit

```C
void SEG_display_digit(int pos, int val)
{
	PORTG = (1 << (4 - pos));
	PORTD = ((seg_pat[val] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[val] & 0x70) | (PORTB & 0x0F);
}
```

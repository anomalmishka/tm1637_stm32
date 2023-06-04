#include "tm1637_stm32_hal.h"
#include "string.h"

#define CLK_PORT GPIOB
#define DIO_PORT GPIOB
#define CLK_PIN GPIO_PIN_6
#define DIO_PIN GPIO_PIN_7

void _tm1637Start(void);
void _tm1637Stop(void);
void _tm1637ReadResult(void);
void _tm1637WriteByte(uint8_t b);
void _tm1637DelayUsec(uint8_t i);
void _tm1637ClkHigh(void);
void _tm1637ClkLow(void);
void _tm1637DioHigh(void);
void _tm1637DioLow(void);
void tm1637Init(void);
void tm1637Display_4_Symbols(uint8_t data[], uint8_t dot);
void tm1637Display_String(char string[]);
void tm1637SetBrightness(uint8_t brightness);

void tm1637Init(void)
{
    tm1637SetBrightness(8);
}


void tm1637SetBrightness(uint8_t brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    _tm1637Start();
    _tm1637WriteByte(0x87 + brightness);
    _tm1637ReadResult();
    _tm1637Stop();
}

void _tm1637Start(void)
{
    _tm1637ClkHigh();
    _tm1637DioHigh();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
}

uint8_t tm1637SegmentSwitch(char symbol)
{
	uint8_t data = 0;
	//   a
	// f   b
	//   g
	// e   c
	//   d  dot
	//
	// data = dot,g,f,e,d,c,b,a
	switch(symbol){
	case '0':
        data = 0x3f;
        break;
    case '1':
        data = 0x06;
        break;
	case '2':
        data = 0x5b;
        break;
    case '3':
        data = 0x4f;
        break;
	case '4':
        data = 0x66;
        break;
    case '5':
        data = 0x6d;
        break;
	case '6':
        data = 0x7d;
        break;
    case '7':
        data = 0x07;
        break;
	case '8':
        data = 0x7f;
        break;
    case '9':
        data = 0x6f;
        break;
	case 'a':
        data = 0x77;
        break;
	case 'A':
        data = 0x77;
        break;
    case 'b':
        data = 0x7c;
        break;
    case 'B':
        data = 0x7c;
        break;
	case 'c':
        data = 0x58;
        break;
	case 'C':
        data = 0x39;
        break;
    case 'd':
        data = 0x5e;
        break;
    case 'D':
        data = 0x3f;
        break;
	case 'e':
        data = 0x79;
        break;
	case 'E':
        data = 0x79;
        break;
    case 'f':
        data = 0x71;
        break;
    case 'F':
        data = 0x71;
        break;
	case 'g':
        data = 0x3d;
        break;
	case 'G':
        data = 0x3d;
        break;
    case 'h':
        data = 0x74;
        break;
    case 'H':
        data = 0x76;
        break;
	case 'i':
        data = 0x10;
        break;
	case 'I':
        data = 0x30;
        break;
	case 'j':
        data = 0x1e;
        break;
	case 'J':
        data = 0x1e;
        break;
	case 'k':
        data = 0x76;
        break;
	case 'K':
        data = 0x76;
        break;
    case 'l':
        data = 0x38;
        break;
    case 'L':
        data = 0x38;
        break;
    case 'm':
        data = 0x54;
        break;
    case 'M':
        data = 0x37;
        break;
	case 'n':
        data = 0x54;
        break;
	case 'N':
        data = 0x37;
        break;
    case 'o':
        data = 0x5c;
        break;
    case 'O':
        data = 0x3f;
        break;
	case 'p':
        data = 0x73;
        break;
	case 'P':
        data = 0x73;
        break;
	case 'q':
        data = 0x67;
        break;
    case 'Q':
        data = 0x67;
        break;
    case 'r':
        data = 0x50;
        break;
    case 'R':
        data = 0x50;
        break;
	case 's':
        data = 0x6d;
        break;
	case 'S':
        data = 0x6d;
        break;
    case 't':
        data = 0x78;
        break;
    case 'T':
        data = 0x78;
        break;
	case 'u':
        data = 0x1c;
        break;
	case 'U':
        data = 0x3e;
        break;
    case 'v':
        data = 0x1c;
        break;
    case 'V':
        data = 0x3e;
        break;
    case 'w':
        data = 0x1c;
        break;
    case 'W':
        data = 0x3e;
        break;
    case 'x':
        data = 0x76;
        break;
    case 'X':
        data = 0x76;
        break;
    case 'y':
        data = 0x6e;
        break;
    case 'Y':
        data = 0x6e;
        break;
    case 'z':
        data = 0x48;
        break;
    case 'Z':
        data = 0x5b;
        break;
    case ' ':
        data = 0x00;
        break;
    case '-':
        data = 0x40;
        break;
    case '.':
        data = 0x80;
        break;
    case ',':
        data = 0x80;
        break;
    case '_':
        data = 0x08;
        break;
    default:
        data = 0x00;
        break;
	}
	return data;
}


void tm1637Display_4_Symbols(uint8_t data[], uint8_t dot)
{
	uint8_t symbArr[4] = {0};
    _tm1637Start();
    _tm1637WriteByte(0x40); //Data command setting
    _tm1637ReadResult();
    _tm1637Stop();

    _tm1637Start();
    _tm1637WriteByte(0xc0); //Address command settings
    _tm1637ReadResult();

    for (uint8_t i = 0; i < 4; i++)
	{
    	symbArr[i] = tm1637SegmentSwitch(data[i]);
        if (i == 0 && dot == 8)
		{
        	symbArr[i] |= 1 << 7;
        }
        if (i == 1 && dot == 4)
		{
        	symbArr[i] |= 1 << 7;
        }
        if (i == 2 && dot == 2)
		{
        	symbArr[i] |= 1 << 7;
        }
        if (i == 3 && dot == 1)
		{
        	symbArr[i] |= 1 << 7;
        }
        _tm1637WriteByte(symbArr[i]); // Send data
        _tm1637ReadResult();
    }
    _tm1637Stop();
}

void tm1637Display_String(char string[])
{
	char space = ' ';
	uint8_t sizeof_string = strlen(string);
	uint8_t symbArr[4] = {0};
//	if(sizeof_string % 2 != 0)
//	{
//		string+=space;
//	}
    _tm1637Start();
    _tm1637WriteByte(0x40); //Data command setting
    _tm1637ReadResult();
    _tm1637Stop();
    _tm1637Start();
    _tm1637WriteByte(0xc0); //Address command settings
    _tm1637ReadResult();
    for (uint8_t i = 0; i < sizeof_string; i++)
	{
        for (uint8_t y = 0; y < 4; y++)
    	{
        	symbArr[y] = tm1637SegmentSwitch(string[y + i]);
            _tm1637WriteByte(symbArr[y]); // Send data
            _tm1637ReadResult();
    	}
        _tm1637Stop();
       	HAL_Delay(500);
       	_tm1637Start();
       	_tm1637WriteByte(0x40); //Data command setting
       	_tm1637ReadResult();
       	_tm1637Stop();
       	_tm1637Start();
       	_tm1637WriteByte(0xc0); //Address command settings
        _tm1637ReadResult();
    }
    _tm1637Stop();
}

void _tm1637Stop(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
    _tm1637DelayUsec(2);
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637DioHigh();
}

void _tm1637ReadResult(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(5);
    // while (dio); // We're cheating here and not actually reading back the response.
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637ClkLow();
}

void _tm1637WriteByte(uint8_t b)
{
	/*
	for example b = 0b1001 (9d):
		1 step - 0b00001001 & 0b00000001 = 1 => write 1 and right shift
		2 step - 0b00000100 & 0b00000001 = 0 => write 0 and right shift
		3 step - 0b00000010 & 0b00000001 = 0 => write 0 and right shift
		4 step - 0b00000001 & 0b00000001 = 1 => write 1 and right shift
	 */

    for (uint8_t i = 0; i < 8; ++i) // a byte cycle
	{
        _tm1637ClkLow();

        if (b & 0x01) 				// if bit is 1
            _tm1637DioHigh();		// write 1
        else
			_tm1637DioLow();		// else write 0

        _tm1637DelayUsec(3);

        b >>= 1;					// right bit shift for 1

        _tm1637ClkHigh();
        _tm1637DelayUsec(3);
    }
}

void _tm1637DelayUsec(uint8_t i)
{
    for (; i>0; i--)
	{
    	for(uint8_t y = 72; y>0;y--)
    	{
    		__NOP();
    	}
    }
}

void _tm1637ClkHigh(void)
{
    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_SET);
}

void _tm1637ClkLow(void)
{
    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_RESET);
}

void _tm1637DioHigh(void)
{
    HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_SET);
}

void _tm1637DioLow(void)
{
    HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_RESET);
}

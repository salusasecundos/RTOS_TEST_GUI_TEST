#include "functions.h"

//void uint16tostr(char buf[], uint32_t d, uint8_t base);
/*
 * function transform input number uint32_t d (less than 999)
 * and fills buffer by the ASCII character codes of each digit
 * input
 * char buf[] buffer to send to the LCD, sets the number of symbols in the string
 * uint32_t d - input number for showing on LCD (less than 999)
 * uint8_t base - base constant
 */


void uint16tostr(char buf[], uint32_t d, uint8_t base)
{
    uint32_t div = 1;
    uint8_t index = 0;
    while (d/div >= base) div *= base;				//746 / (div) >= 10 -> div = div * 10
    while (div != 0)
    {
            uint32_t num = d/div;					//
            d = d%div;
            div /= base;
            if (num > 9)
                    buf[index] = (num-10) + 65;
            else
                    buf[index] = num + 48;
            index++;
    }
    buf[index] = 0;	// end of string
}


//uint16tostr(NMB, (BMP180_kpa_to_mmhg(rp)), 10);
/*
 * 746 / 1 >= 10 yes -> div = 1 * 10 -> div = 10
 * 746 / 10 >=10 yes -> div = 10*10  -> div = 100
 * 746 / 100 >=10 no -> div = 100 base = 10
 *
 * пока div(100) !=0
 * num = 746/100 -> num = 7
 * d(746) = 746 % 100 -> d = 46
 * div(100) = div(100) / base(10) -> div = 10
 * если num(7) > 9 no buf[index(0)] = num(7) + 48; ASCII table 0x55 -> 7
 * index(0) = index(0) + 1 -> index = 1
 *
 * пока div(10) !=0
 * num(7) = d(46)/div(10) -> num = 4
 * d(46) = d(46) % div(10) -> d = 6
 * div(10) = div(10) / base(10) -> div = 1
 * если num(4) > 9 no buf[1] = num(4) + 48; ASCII table 0x52 -> 4
 * index(1) = index(1) + 1 -> index = 2
 *
 * пока div(1) !=0
 * num(4) = d(6)/div(1) -> num = 6
 * d(6) = d(6) % div(10) -> d = 6
 * div(1) = div(1) / base(10) -> div = 0
 * если num(6) > 9 no buf[2] = num(6) + 48; ASCII table 0x54 -> 6
 * index(2) = index(2) + 1 -> index = 3
 *
 * пока div(0) !=0 div = 0 -> exit
 *
 * buf[3] = 0;	// end of string
 *
 *
 *12-10 = 2 + 65 = 67 ASCII table 0x67 -> C
 *все что более 999 будет представлено в HEX коде
 *
 *7 469 209/1			(7 469 209)	>= 10 yes -> div = 1*10 -> div = 10
 *7 469 209/10			(7 469 20)	>= 10 yes -> div = 10*10 -> div = 100
 *7 469 209/100			(74 692)	>= 10 yes -> div = 100*10 -> div = 1000
 *7 469 209/1 000		(7 469)		>= 10 yes -> div = 1 000*10 -> div = 10 000
 *7 469 209/10 000		(746)		>= 10 yes -> div = 10 000*10 -> div = 100 000
 *7 469 209/100 000		(74)		>= 10 yes -> div = 100 000*10 -> div = 1 000 000
 *7 469 209/1000 000	(7)			>= 10 no
 *
 *
 *
 */

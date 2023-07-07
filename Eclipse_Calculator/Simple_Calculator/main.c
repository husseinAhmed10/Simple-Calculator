/*
 * main.c
 *
 *  Created on: Apr 28, 2023
 *      Author: T.S
 */

#include "lcd.h"
#include <util/delay.h> /* To use the delay functions */
#include "keypad.h"

uint8 num1 = 0, num2 = 0, oper, res = 0;

uint8 first_num = 1, second_num = 0;

uint8 simple_calc(uint8 par1, uint8 par2, uint8 oper) {

	switch (oper) {
	case '+':
		return (par1 + par2);

	case '-':
		return (par1 - par2);

	case '*':
		return (par1 * par2);

	case '%':
		if (par2 == 0)
			return 0;
		else
			return (par1 / par2);

	default:
		return par1;
	}
}

void calc_init() {

	LCD_clearScreen();
	LCD_displayString("Welcome Simple");
	LCD_displayStringRowColumn(1, 0, "Calculator +-*/");
	LCD_displayStringRowColumn(2, 0, "-->Created by HA");
	LCD_moveCursor(3, 0);
	num1 = 0;
	num2 = 0;
	oper = 0;
	res = 0;
	first_num = 1;
	second_num = 0;

}

int main(void) {

	LCD_init();

	calc_init();

	uint8 num, no_equal = 0, initial=1;

	while (1) {

		if (no_equal == 0) {
			num = KEYPAD_getPressedKey();
			_delay_ms(500);

			if ((num <= 9) && (num >= 0)) {

				if (first_num == 1) {

//					if(initial==1){
//						num1 = (num - '0');
//						LCD_intgerToString(num);
//						LCD_intgerToString(num1);
//						initial=0;
//						continue;
//					}

					/*we keep taking the entered numbers and saving it into num1*/
					num1 = num1 * 10 + (num );
					LCD_intgerToString(num);
					//LCD_intgerToString(num1);
				} else if (second_num == 1) {
					/*we convert that number into int*/
					num2 = num2 * 10 + (num);
					LCD_intgerToString(num);
				}

			} else if (num == 13) {
				calc_init();
				first_num = 1;
			}

			else {
				LCD_displayCharacter(num);
				//LCD_intgerToString(num);


				if (num == '=' && no_equal == 0) {
					res = simple_calc(num1, num2, oper);
					LCD_intgerToString(res); /* display the pressed keypad switch */
					no_equal = 1;
					first_num = 0;
					second_num = 0;
				} else if (num == '+') {
					num1 = simple_calc(num1, num2, oper);
					//	LCD_intgerToString(res); /* display the pressed keypad switch */
					oper = num;
					first_num = 0;
					second_num = 1;
					num2 = 0;
				} else if (num == '-') {
					num1 = simple_calc(num1, num2, oper);
					//	LCD_intgerToString(res); /* display the pressed keypad switch */
					oper = num;
					first_num = 0;
					second_num = 1;
					num2 = 0;
				} else if (num == '*') {
					num1 = simple_calc(num1, num2, oper);
					//LCD_intgerToString(num1); /* display the pressed keypad switch */
					oper = num;
					first_num = 0;
					second_num = 1;
					num2 = 0;
				} else if (num == '%') {
					num1 = simple_calc(num1, num2, oper);
					//LCD_intgerToString(num1); /* display the pressed keypad switch */
					oper = num;
					first_num = 0;
					second_num = 1;
					num2 = 0;
				}

			}
			continue;
		}
		num = KEYPAD_getPressedKey();
		_delay_ms(500);
		if (num == 13) {
			calc_init();
			first_num = 1;
			no_equal = 0;
		}

	}

	return 0;
}

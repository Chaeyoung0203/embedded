/*
 * fnd_controller.h
 *
 *  Created on: Sep 17, 2024
 *      Author: cycy0203
 */

#ifndef SRC_FND_CONTROLLER_H_
#define SRC_FND_CONTROLLER_H_

#include "main.h" // GPIO define문을 사용하기 위함

#define HIGH 1
#define LOW 0

#define false 0
#define true 1

extern uint8_t _LED_0F[29]; // 중복 배열 선언 주의

void init_Led_Display();

void send(uint8_t X);
void send_port(uint8_t X, uint8_t port);

void digit4(int n, int replay, uint8_t showZero);
void digit4_two(int n, int replay);
void digit4_one(int n);

void digit4showZero(int n, int replay);
void digit4showZero_one(int n);

void digit2(int n, int port, int replay);
void digit2_two(int n, int port);

#endif /* SRC_FND_CONTROLLER_H_ */

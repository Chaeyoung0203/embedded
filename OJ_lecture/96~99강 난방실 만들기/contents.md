### 학습 목표

- 난방실(박스) 만들기
- 35도 이하고 릴레이 off 일때 난방실에 드라이기 on
- 40도 이상이고 릴레이 on일 때 난방실에 드라이기 off

### 온도를 가져오는 코드 만들기

```c
// ds18b20.c
// 헤더파일 추가 잊지말기
float getCurrentTemper() {
  return ds18b20[0].Temperature;
}
```

### heaterController.c and heaterController.h 작성

```c
// heaterController.c
#include "heaterController.h"


static m_state = 0;

void heaterControll(uint8_t onOFF) {
	HAL_GPIO_WritePin(PB5_RELAY_ON_OFF_GPIO_Port, PB5_RELAY_ON_OFF_Pin, onOFF);
	m_state = onOFF;
}


uint8_t getHeaterState() {
	return m_state;
}

```

```c
// heaterController.h
/*
 * heaterController.h
 *
 *  Created on: Oct 28, 2024
 *      Author: cycy0203
 */

#ifndef LIB_INC_HEATERCONTROLLER_H_
#define LIB_INC_HEATERCONTROLLER_H_

#include "main.h"

enum {
	t_OFF = 0,
	t_ON = 1,
};

uint8_t getHeaterState();
void heaterControll(uint8_t onOFF);

#endif /* LIB_INC_HEATERCONTROLLER_H_ */

```

### main.c 코드

```c
while (1)
  {
  	Ds18b20_ManualConvert();

  	if(getCurrentTemper() > 40 && getHeaterState() == t_ON)
  	{
  		heaterControll(t_OFF);
  	}
  	else if (getCurrentTemper() < 35 && getHeaterState() == t_OFF)
  	{
  		heaterControll(t_ON);
  	}
  }
```

# 온도 센서 메커니즘

- 센서에 열이 닿으면 저항 값이 변한다.
- 저항값이 변한만큼 전압값도 변한다.
- 변한 전압값의 수치를 계산해서 온도를 측정한다.
- 온도를 DAT선을 통해 가져와서 LED 8segment FND에 표현하기
- 온도센서 폴더 참고

### 기술문서: DS18B20(기술문서).pdf

### 공부 진행방법

- 이미 진행된 코드를 가지고 구현 후 데이터시트 보기

### 온도코드

참고코드

- `DS18x20_Temperature.cpp`
- `OneWire.cpp`
- `OneWire.h`

```c
#include <OneWire.h>

OneWire  ds(10);  // 10번 pin을 사용, OneWire클래스의 ds객체 생성

// 중요한 기능
ds.write()
ds.read()

/* 학습목표
OneWire클래스 구조 이해
wirte(), read() 함수 구조 이해
*/
```

### OneWire 클래스 생성자 함수

```cpp
#include "OneWire.h"

OneWire::OneWire(uint8_t pin)
{
	pinMode(pin, INPUT); // pin Mode를 Input으로 setting
	// 매개변수 **번 pin으로부터 bitMast, baseReg값 저장
  bitmask = PIN_TO_BITMASK(pin);
  baseReg = PIN_TO_BASEREG(pin);
#if ONEWIRE_SEARCH
	reset_search();
#endif
}
```

### OneWire:read() 함수

```cpp
uint8_t OneWire::read() {
    uint8_t bitMask;
    uint8_t r = 0;
    // bitMask type을 통해 bitMask << 연산의 횟수를 파악할 수 있다.
    // bitMask가 0이 될때까지 << 연산을 반복
    for (bitMask = 0x01; bitMask; bitMask <<= 1)
    {
	  if ( OneWire::read_bit()) r |= bitMask; // bit를 한개씩 읽고있음
    }
    return r;
}
```

- 코드 진행과정에 따른 데이터 값
  | r (결과 값) | bitMask | read_bit() |
  | ----------- | --------- | ---------- |
  | 0000,0001 | 0000,0001 | true |
  | 0000,0001 | 0000,0010 | false |
  | 0000,0101 | 0000,0100 | true |
  | 0000,1101 | 0000,1000 | true |
  | 0001,1101 | 0001,0000 | true |
  | 0011,1101 | 0010,0000 | true |
  | 0011,1101 | 0100,0000 | false |
  | 1011,1101 | 1000,0000 | true |
- 이런식으로 다른사람의 분석 코드를 활용하면 데이터시트를 분석하여 구현한 코드보다 훨씬더 빠르게 프로젝트를 진행할 수 있다.

- **bitMask란?**: 이진수 비트를 사용해 데이터의 특정 상태를 효율적으로 확인하거나 조작하는 방법

#### OneWire::read_bit(void) 함수

```cpp
// 1bit를 읽는 함수

uint8_t OneWire::read_bit(void)
{
	IO_REG_TYPE mask=bitmask;
	volatile IO_REG_TYPE *reg IO_REG_ASM = baseReg;
	uint8_t r; // read bit 값 저장

	noInterrupts();
	DIRECT_MODE_OUTPUT(reg, mask); // Input mode ==> Output mode
	DIRECT_WRITE_LOW(reg, mask); // 해당 선의 state를 low로 변경
	delayMicroseconds(3); // 3micro초 기달리고
	DIRECT_MODE_INPUT(reg, mask);	// let pin float, pull up will raise
	// 다시 input mode(데이터 읽을 준비)
  delayMicroseconds(10); // 10micro초 기달리기
	r = DIRECT_READ(reg, mask); // bit값을 읽어서 r에 저장(1 or 0)
	interrupts();
	delayMicroseconds(53);
	return r;
}
```

- 1-wire, 1개의 wire선으로 read 및 write 모두 수행

### 결론

- 회로도를 보고

#### 1. 온도센서 칩 wire결선하기

#### 2. stm32칩과 빵판 온도센서 회로 구성하기

#### 3. oneWire 클래스와 read, write, read_bit함수에 대한 표면적인 이해(코드로서)

### 온도 센서 메커니즘

- 센서에 열이 닿으면 저항 값이 변한다.
- 저항값이 변한만큼 전압값도 변한다.
- 변한 전압값의 수치를 계산해서 온도를 측정한다.
- 온도를 DAT선을 통해 가져와서 LED 8segment FND에 표현하기
- 온도센서 폴더 참고

#### 기술문서: DS18B20(기술문서).pdf

#### 진행방법: 이미 진행된 코드를 가지고 구현 후 데이터시트 보기

#### bitmask란?: 이진수 표현을 자료 구조로 쓰는 기법

#### DS18B20의 테스트코드 >> example >> DS18x20_Temperature.pde 코드보기

- **C++ 문법**

```c
#include <OneWire.h>

OneWire  ds(10);  // 10번 pin을 사용, OneWire클래스의 ds객체 생성

// 중요한 함수들
ds.write()
ds.read()
```

- **OneWire 클래스를 참고하여 write(), read() 함수에 매커니즘을 이해해야한다.**

### OneWire.cpp

```c++
OneWire::OneWire(uint8_t pin)
{
	pinMode(pin, INPUT);
	bitmask = PIN_TO_BITMASK(pin);
	baseReg = PIN_TO_BASEREG(pin);
#if ONEWIRE_SEARCH
	reset_search();
#endif
}
```

- input mode로 시작
- bitmask, baseReg 설정
  - **비트마스크(BitMask)란?**: 정수의 이진수 표현을 자료구조로 쓰는 기법

```c++
uint8_t OneWire::read_bit(void)
{
	IO_REG_TYPE mask=bitmask;
	volatile IO_REG_TYPE *reg IO_REG_ASM = baseReg;
	uint8_t r;

	noInterrupts();
	DIRECT_MODE_OUTPUT(reg, mask);
	DIRECT_WRITE_LOW(reg, mask); // GPIO low level
	delayMicroseconds(3); // 3 micro 쉬기
	DIRECT_MODE_INPUT(reg, mask);	// let pin float, pull up will raise, Input mode로 다시 변경
	delayMicroseconds(10); // 10 micro 쉬고
	r = DIRECT_READ(reg, mask); // 1개 bit읽고 return
	interrupts();
	delayMicroseconds(53);
	return r;
}
```

- mode를 input mode에서 output mode로 변경
- GPIO low level
- 3 micro초 쉬기
- input mode로 다시 변경하기
- 10 micro초 다시 쉬고
- 다시 1개 bit읽고 return

```c++
uint8_t OneWire::read() {
    uint8_t bitMask;
    uint8_t r = 0;

  for (bitMask = 0x01; bitMask; bitMask <<= 1)
  {
	  if ( OneWire::read_bit()) r |= bitMask;
  }

  return r;
}
```

- for 문을 9번 돌면 조건에서 탈출 **즉 8번동안 bitMask를 읽음**

  - bitMask = 0000,0001 if true => r = 0000, 0001
  - bitMask = 0000,0010 if true => r = 0000, 0011
  - bitMask = 0000,0100 if true => r = 0000, 0111
  - bitMask = 0000,1000 if true => r = 0000, 1111
  - bitMask = 0001,0000 if true => r = 0001, 1111
  - bitMask = 0010,0000 if true => r = 0011, 1111
  - bitMask = 0100,0000 if true => r = 0111, 1111
  - bitMask = 1000,0000 if false => r = 0111, 1111

- 9번째에 bitMask = 0000,0000이 되면서 for문이 끊긴다.

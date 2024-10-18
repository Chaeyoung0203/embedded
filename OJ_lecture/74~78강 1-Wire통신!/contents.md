# 새로운 Protocal 통신을 배우는 방법

## 1. 보편적인 통신 프로토콜인지 검색한다.

- 만약 그렇다면....

## 2. 내가사용하는 main chip(ex.stm32)에 적용되는 통신 라이브러리 source를 찾는다.

- 1-wire TM Library source코드를 찾았지만 우리는 HAL Library로 변환할 것이다.
- [convert TM Lib to HAL ](https://github.com/nimaltd/ds18b20)

# 1-wire 통신이란?

- Max 1개의 선으로 통신가능
- Input/Output mode를 번갈아가며 사용
- 신호선으로 전원까지 공급가능

## 1-wire library porting하기

![alt text](image.png)
![alt text](image-2.png)
![alt text](image-1.png)

- 캡쳐를 참고해서 파일 mv
- 디버깅하면서 error 수정(**스스로 해보는게 중요**)
- IOC mode에서 GPIO, timer setting
  - interrupt on
  - 8MHz => 72MHz로 setting (외부 CLK 사용 crystal/Ceramic Resonator)
  - [convert TM Lib to HAL ](https://github.com/nimaltd/ds18b20) 참고하여 timer 옵션 설정
  - count 23:00부터 참고

### Timer 옵션 개념정리

#### 타이머 옵션 개념

- 클럭 주파수, Prescaler, Counter Period가 서로 상호작용하여 원하는 시간마다 인터럽트를 발생시키는 것을 목표
  ![alt text](image-16.png)

#### 1. Prescaler

- 클럭 신호를 나누는 역할
- Prescaler가 `10000-1`로 설정되었다면 10000개의 clk 신호마다 타이머 Counter값이 1개 증가
- 원래 클럭 주파수가 8MHz일 때 Prescaler값인 1만으로 나누면 타이머의 주파수가 800Hz가 된다.
- 즉, Prescaler = (10000-1)의 의미는 >>> 8MHz를 800Hz로 줄이는 역할
  - 타이머 카운터는 800Hz로 동작한다.
  - Prescaler에 의해 1초에 8MHz가 아닌 800Hz가 됨

#### 2. Counter Period

- 카운터가 몇 번 증가해야 인터럽트가 발생할지를 정의

if) Counter Period = (800-1) 이라면

- 타이머 카운터는 0~799까지를 한주기로 Interrupt가 발생한다.

#### 예시1 ) 800MHz를 1초마다 Interrupt를 발생시키려면???

1. Prescaler에 의해 클럭이 800Hz로 줄어들게된다.
2. Counter Period = (800-1)

- 800번의 타이머 카운트를 의미
- 1s/800Hz 동안 카운터가 800번 증가
- **즉, 800Hz 주파수에서 800번동안 timer count가 증가하면 1초가 지나고 Interrupt가 발생된다.**

#### 예시2 ) 타이머로 2초마다 LED를 깜빡이게 하려면?

- **클럭 주파수**: MCU의 클럭은 16MHz입니다.

  - 즉, 1초에 16,000,000번 클럭이 발생합니다.

- **프리스케일러(Prescaler)**
  - 프리스케일러 = (16000-1) 으로 설정하면
  - 16MHz 클럭이 1kHz(즉, 1000Hz)로 줄어듭니다.
  - 이제 타이머의 카운터가 **1ms(0.001초)** 마다 1씩 증가합니다.
- **카운터 주기 설정 (Counter Period)**
- 2초마다 타이머가 인터럽트를 발생시키게 하고 싶을 때
- 현재 타이머는 1ms마다 카운터가 1씩 증가
- 따라서, 2초 동안 1ms마다 증가하려면, 타이머는 2000번 카운터를 증가해야 합니다.
- **카운터 주기(Counter Period)** 를 2000으로 설정하면, 1ms마다 카운터가 증가하여
- 2초에 한 번 카운터값이 2000에 도달하고, 그때 인터럽트가 발생합니다.

**결론**

- **Prescaler = (16000-1)** => 클럭 주파수를 16MHz에서 1kHz로 줄임(1ms마다 타이머가 한 번씩 카운터 1씩 증가).

- **Counter Period = 2000**) 카운터가 2000에 도달할 때 인터럽트 발생(2초에 한 번).

#### 예시3 ) 0.5초마다 LED 깜빡이기

- **클럭 주파수 16MHz**
- **Prescaler** = (16000-1)으로 설정 ==> 1kHz로 줄임 ==> 1ms마다 counter값 1씩 증가
- **Counter Period = 500** ==> 0.5초마다 LED를 깜빡이는 Interrupt를 발생시키기위하여 값을 500으로 설정

### DS18b20_Init 함수 call해서 온도정보 가져오기

- 해당 파일에서 온도정보를 가져오는 함수를 call해서 온도정보 가져오기

### 왜? counter period값을 0xFFFF로 설정하라 했을까?

```c
void ONEWIRE_DELAY(uint16_t time_us)
{
	_DS18B20_TIMER.Instance->CNT = 0;
	while(_DS18B20_TIMER.Instance->CNT <= time_us);
}
```

- 위 코드에서 \_DS18B20_TIMER.Instance->CNT값은 counter period 옵션에서 설정한 값내로 주기가 반복된다.
- if counter period값이 10이고 time_us 값이 10이상이면 Onewire Delay값이 **무한 loop**에 빠지게된다.
- 따라서 DS18b20_Init() 함수를 벗어날 수 없게된다.

## 혼자서 FND에 온도정보 표시해보자

- 아마 정상적으로 표현되지는 않을것이다.
- 오늘은 여기까지

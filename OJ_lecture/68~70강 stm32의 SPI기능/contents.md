# STM32에서 제공하는 SPI기능

- 이전 강의에서는 GPIO로 SPI 기능을 구현했었다...
- 지금부터 GPIO옵션을 SPI로 변경하자

## 프로젝트를 복사한다.
- 저장해둔 강의 참고

## IOC모드에서 그림과 같이 옵션을 변경한다.

![alt text](image.png)

### 그림과 같이 parameters setting에 옵션 설정

![alt text](image-1.png)

## 수정 코딩

### fnd_controller.c (.h도 수정 필요)

```c
static SPI_HandleTypeDef * mhspi;

void init_fnd(SPI_HandleTypeDef * hspi)
{
  mhspi = hspi;
  _LED_0F[0] = 0xC0; //0
  _LED_0F[1] = 0xF9; //1
  _LED_0F[2] = 0xA4; //2
  _LED_0F[3] = 0xB0; //3
  _LED_0F[4] = 0x99; //4
  _LED_0F[5] = 0x92; //5
  _LED_0F[6] = 0x82; //6
  _LED_0F[7] = 0xF8; //7
  _LED_0F[8] = 0x80; //8
  _LED_0F[9] = 0x90; //9
  _LED_0F[10] = 0x88; //A
  _LED_0F[11] = 0x83; //b
  _LED_0F[12] = 0xC6; //C
  _LED_0F[13] = 0xA1; //d
  _LED_0F[14] = 0x86; //E
  _LED_0F[15] = 0x8E; //F
  _LED_0F[16] = 0xC2; //G
  _LED_0F[17] = 0x89; //H
  _LED_0F[18] = 0xF9; //I
  _LED_0F[19] = 0xF1; //J
  _LED_0F[20] = 0xC3; //L
  _LED_0F[21] = 0xA9; //n
  _LED_0F[22] = 0xC0; //O
  _LED_0F[23] = 0x8C; //P
  _LED_0F[24] = 0x98; //q
  _LED_0F[25] = 0x92; //S
  _LED_0F[26] = 0xC1; //U
  _LED_0F[27] = 0x91; //Y
  _LED_0F[28] = 0xFE; //hight
}
```
### GPIO로 구현한 SPI통신을 IDE에서 제공해준 SPI통신 설정으로 구현하기

- STMIDE에서 SPI옵션 설정을 적용하려면 SPI통신을 GPIO로 구현한 send함수만 변경해주면 된다.

```c
void send(uint8_t X)
{
    HAL_SPI_Transmit(mhspi, &X, 1, 100);
}
```
- 위 코드는 아래 코드와 같은 역할이다.
- 매우 간단하게 코드 작성

```c
void send(uint_t X)
{
  for (int i = 8; i >= 1; i--)
	{
	  if (X & 0x80)
	  {
	    HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, HIGH);
	  }
	  else
	  {
	  	HAL_GPIO_WritePin(FND_DIO_GPIO_Port, FND_DIO_Pin, LOW);
	  }
	  X <<= 1;
	  HAL_GPIO_WritePin(FND_SCLK_GPIO_Port, FND_SCLK_Pin, LOW);
	  HAL_GPIO_WritePin(FND_SCLK_GPIO_Port, FND_SCLK_Pin, HIGH);
	}
}
```

### main.c

- spi handler 변수를 포인로 가져온다.
- while문에서 기능 구현

### 의문점

- 질문? CPHA가 왜 1edge에서 돌아갈까?
- 답변

![alt text](image-2.png)
- 데이터시트에 따르면 2edge에서 동작하는게 맞다.
- GPIO에서는 클럭 주기가 1edge이든 2edge이든 상관없었었다. 그래서 1edge라고 강의에서 얘기한것
- SPI옵션 설정에서는 데이터시트데로....

### SPI옵션처럼 변경된 빵판회로로 구성하고 오실로스코프로 SCLK, DIO 찍어보기
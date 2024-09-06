## Hal드라이브 없이 GPIO를 제어해보자
- 그러기 위해서는 일단 분석부터 해야겠지?
### 분석 TIP
1. 다른 사람의 소스를 본다.
2. 분석해서 구현한다.
3. 데이터시트를 보며 이해한다.

### MX_GPIO_Init() 분석
일단 ouput mode만 분석해보자
```c
MX_GPIO_Init();
...

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIO_LED_GPIO_Port, GPIO_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : GPIO_LED_Pin */
  GPIO_InitStruct.Pin = GPIO_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIO_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : GPIO_SWITCH_Pin */
  GPIO_InitStruct.Pin = GPIO_SWITCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIO_SWITCH_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}
```

### __HAL_RCC_GPIOC_CLK_ENABLE();
- 회로도를 보면 led를 제어하기 위해서는 13번핀을 제어해야한다.
- `PIN13`을 제어하기 위해서는 일단 해당 핀이 속한 포트그룹 GPIOC의 Clock을 활성화해야한다.
- 위 코드는 아래와같이 define되어있다.
```c
#define __HAL_RCC_GPIOC_CLK_ENABLE()   
do {
      __IO uint32_t tmpreg; \
      SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);\
      /* Delay after an RCC peripheral clock enabling */\
      tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);\
      UNUSED(tmpreg); \ // tepreg는 결국 아무것도 안하는 코드
    } while(0U)
```
#### UNUSED()
- 현재는 아무것도 안하지만
- 원래는 디버깅 메세지를 출력하기 위한 것
#### SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);
- 레퍼런스 112p~114p 참조
- IO port C clock enable
- GPIOC 포트의 Clock을 활성화한다.
```c
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

RCC->APB2ENR |= RCC_APB2ENR_IOPCEN
*(0x40021018) |= 1 << 4
```
- **RCC**란? Reset Clock Control

### 분석을 바탕으로 HAL드라이브 없이 코딩해보기
#### 목적: GPIOC 클럭을 활성화한다.
- `SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);` 이것을 직접 코딩하는것과 같은 결과가 나올것이다.

#### 변환 결과
- 아래와 같이 작성하면 GPIOC clock이 enable된다.
```c
volatile int * reg = 0x0x40021018
*reg |= 1 << 4;
```


[클럭과 버스에 대한 설명](./clock_and_bus.md)

[clock_tree 공부하기](./clock_tree.md)
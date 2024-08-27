# HAL 드라이버 코드 분석하기

## Hal_Init()의 **\_\_HAL_FLASH_PREFETCH_BUFFER_ENABLE()** 분석하기

```c
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()
(FLASH->ACR |= FLASH_ACR_PRFTBE)
```

### TIP

- **코드 회색 테두리를 통해 코드의 활성화/비활성화 여부를 알 수 있다.**
- **breakPoint를 통해 code flow가 올바른지 파악할 수 있다.**

## FLASH = (FLASH_TypeDef \*)FLASH_R_BASE

### FLASH_TypeDef

```c
typedef struct
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t AR;
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;
  __IO uint32_t WRPR;
} FLASH_TypeDef;
```

#### \_\_IO란?

```c
#define     __IO    volatile       /*!< Defines 'read / write' permissions */
```

- 컴파일러 최적화를 막는 역할을 한다.
- 레지스터에 저장을 하지 않게 하는 역할

### FLASH_R_BASE

```c
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x00002000UL)
```

```c
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)
```

```c
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */
```

#### 즉, FLASH_R_BASE 값은 `0x4002,2000`

#### 구조체 변수의 주솟값과 구조체의 첫 번째 멤버변수 주솟값은 같다는 특징이 있다 따라서...

### &(FLASH->ACR)의 값은 `0x4002,2000`

## FLASH_ACR_PRFTBE

```c
#define FLASH_ACR_PRFTBE_Msk                (0x1UL << FLASH_ACR_PRFTBE_Pos)
/*!< 0x00000010 */
// FLASH_ACR_PRFTBE_Pos의 값은 4
#define FLASH_ACR_PRFTBE                    FLASH_ACR_PRFTBE_Msk               /*!< Prefetch Buffer Enable */
```

### FLASH_ACR_PRFTBE = (1 << 4)

### 코드 해석 결과

```c
(FLASH->ACR |= FLASH_ACR_PRFTBE) == *(0x4002,2000) |= (1 << 4)
```

#### 간단하게 코드 수정

```c
volitile unsigend int * reg = 0x4002,2000;
*reg |= 16;
```

# __HAL_FLASH_PREFETCH_BUFFER_ENABLE() 분석
Hal_Init()의 **__HAL_FLASH_PREFETCH_BUFFER_ENABLE()** 분석하기
```c
HAL_StatusTypeDef HAL_Init(void)
{
  /* 분석할 함수 */
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
}
```
## 코드 분석 방법
- 소스가 어떤 환경에서 돌아가는지 이해하기
- 소스가 돌아갈 수 있는 환경을 만들기
- 디버깅 할 수 있는 상황 만들기
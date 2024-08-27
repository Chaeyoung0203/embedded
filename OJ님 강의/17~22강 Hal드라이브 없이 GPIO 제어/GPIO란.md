# 데이터 시트를 통한 GPIO 분석

## Overview

- GPIOs (general-purpose inputs/outputs)
  Each of the GPIO pins can be configured by software as output (push-pull or open-drain), as
  input (with or without pull-up or pull-down) or as peripheral **alternate function**.
- Most of the GPIO pins are shared with digital or analog alternate functions.
- All GPIOs are high current-capable.
- The I/Os alternate function configuration can be locked if needed following a specific sequence in order to avoid spurious writing to the I/Os registers.
- I/Os on APB2 with up to 18 MHz toggling speed.
  - **toggling speed**: 전기 신호의 **high state**와 **low state** **즉, on과 off사이에서 빠르게 전환되는 것을 의미**

**alternate function**:

- GPIO 핀이 일반적인 입력 또는 출력 이외의 다른 용도로 사용될 수 있는 기능
- **즉, 핀이 단순한 입력 또는 출력으로만 작동하는 것이 아니라 UART, SPI, I2C 또는 기타 하드웨어 인터페이스와 같은 주변 장치에 연결되도록 구성할 수 있다는 뜻**

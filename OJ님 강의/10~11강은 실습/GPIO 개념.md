# GPIO
- General Perpose Input Output(다용도 입출력) 
- **MCU의 main chip**이 **MCU의 주변장치**와 통신하기 위해 범용으로 사용되는 **MCU**의 `I/O 포트`	
	* **포트란?**: 다양한 **디지털 신호**를 **I/O**할 수 있는 `하드웨어 핀 그룹`
  + 개발자가 그 포트에 대해 `Input mode` or `Output mode`를 setting
  + 입출력 포트를 제어하기위해 `3개의 register`를 소유
  
	## 3개의 register
    + **PORTx**: **포트(Hardware Pin Group)** 에 대한 내용
    + **DDRx**: 포트를 이루고 있는 **Pin**에대한 내용
    + **PINx**: Pin의 상태인 `High mode` or `Low mode`에 대한 setting 설정

	## GPIO Port
	- 여러 개의 GPIO 핀을 포함하는 그룹
	- `STM32 마이크로컨트롤러`는 일반적으로 여러 개의 **GPIO 포트(Hardware Pin Gruop)** 를 갖고 있음,
	- 각 포트는 알파벳 문자로 구분 **ex) GPIOA, GPIOB, GPIOC**

		#### 역할
		- 하나의 포트는 최대 16개의 핀(Pin 0 ~ Pin 15)으로 구성
		- 포트는 핀들을 하나의 단위로 묶어서 **제어**하거나 **설정**

	### GPIO Pin
	- 개별적인 `입력` 또는 `출력` 기능을 하는 핀
	- 각 포트는 여러 개의 핀을 가지며, **번호**로 구분
		#### 역할
		- Pin은 디지털 신호의 **입력** 또는 **출력**을 담당
		- 특정 장치나 센서와 직접 연결되어 작동
		- 각 핀은 개별적으로 setting할 수 있음
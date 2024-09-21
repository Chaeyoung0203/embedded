
#include "main.h"


#include "fnd_controller.h"
int main(void)
{

  init_Led_Display();

  while (1)
  {
  	send_port(_LED_0F[0], 0b0001); // multiple definition of '_LED_0F' 주의

  	for(int i = 0; i<=99; i++)
  	{
  		digit2(i, 0b0001, 50);
  	}

  }

}

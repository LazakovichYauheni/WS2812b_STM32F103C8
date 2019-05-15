#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
#include "main.h"
#include "delay\delay.h"
#include "ws2812\ws2812.h"
#include "ws2812\led_examples.h"



int i;

//ErrorStatus HSEStartUpStatus;

void NVIC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void USART1_IRQHandler(void);
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);

int ledstr(void);
uint8_t EffectNum = 10;
int btflag=0;
int btbuf=0;
int main(void)
{


	  SystemInit();

	  ws2812_init();

	usart_rxtx();

    while(1)
    {
    	if(btflag==1)
        	{	ws2812_buff_init();
    			btflag=0;
        		while(btflag==0)
        		{
        		ledstr();
        		}
        	}

    }
}

int ledstr()
{
	uint16_t Period;
	    	    uint16_t TickNum = led_effect_start(EffectNum, &Period);


	    	    while (TickNum)
	    	    {
	    	      led_effect_tick(EffectNum);
	    	      ws2812_update();

	    	      delay_ms(Period);
	    	     if(btflag==1) return;
	    	    }

	    	    if (++EffectNum == LIGHT_EFFECTS_NUM)
	    	      EffectNum = 0;

}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  ������� ���������� ���������� USARTx.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
		i = USART_ReceiveData(USART1);
		if(i == '0'){
			btflag=1;
			EffectNum=0;



			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);		// ������������� '1' �� 8 ����
			//UARTSend("LED ON\r\n",sizeof("LED ON\r\n"));	// ������� ������� � UART
		}
		else if(i == '1'){
			btflag=1;
			EffectNum=1;


			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
			//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
		}
		else if(i == '2'){
			btflag=1;
			EffectNum=2;

					//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
					//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '3'){
			btflag=1;
			EffectNum=3;

							//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
							//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '4'){
			btflag=1;
			EffectNum=4;

							//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
							//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '5'){
			btflag=1;
			EffectNum=5;

									//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
									//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '6'){
			btflag=1;
			EffectNum=6;

									//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
									//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '7'){
			btflag=1;
			EffectNum=7;

									//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
									//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
				}
		else if(i == '8'){
					btflag=1;
					EffectNum=8;

									//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
									//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
						}
		else if(i == '9'){
			btflag=1;

			EffectNum=9;
							//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);		// ������������� '0' �� 8 ����
							//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
						}

	}
}

void usart_rxtx(void)
{
    const unsigned char welcome_str[] = " Welcome to Bluetooth!\r\n";

    /* Enable USART1 and GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the GPIOs */
    GPIO_Configuration();

    /* Configure the USART1 */
    USART_Configuration();

    /* Enable the USART1 Receive interrupt: this interrupt is generated when the
         USART1 receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* print welcome information */
    UARTSend(welcome_str, sizeof(welcome_str));
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : ���������������� GPIO.
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); //���������

  /* ������������� USART1 Tx (���� PA.09) ��� ������������ (push-pull) ��� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ������������� USART1 Rx (PA.10) ��� ���� ��� �������� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : ��������� USART1.
*******************************************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

/* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
        - USART Clock disabled
        - USART CPOL: Clock is active low
        - USART CPHA: Data is captured on the middle
        - USART LastBit: The clock pulse of the last data bit is not output to
                         the SCLK pin
  */
  USART_InitStructure.USART_BaudRate = 9600;		// �������� ��������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);

  /* �������� USART1 */
  USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  ��������� ����������.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* �������� ���������� �� USARTx */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : UARTSend
* Description    : �������� ������ ������ �� UART.
* Input          : - pucBuffer: buffers to be printed.
*                : - ulCount  : buffer's length
*******************************************************************************/
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Loop while there are more characters to send.
    //
    while(ulCount--)
    {
        USART_SendData(USART1, (uint16_t) *pucBuffer++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        {
        }
    }
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

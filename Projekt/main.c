/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Konfiguruje i zapala leda niebieskiego LED1
  * @param  None
  * @retval 0
  */
uint8_t LED1_ON(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIOF->BSRRL=GPIO_Pin_15;
	
	return 0;	
}
/**
  * @brief  Konfiguruje czestotliwosc na wyjsciu MCO1 - wymagane przez ULPI do dzialania - zakladam PLL na 120MHz wtedy MCO1-24MHz
  * @param  none
  * @retval 0
  */
uint8_t MCO1_CONF(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_MCO1Config(RCC_MCO1Source_PLLCLK,RCC_MCO1Div_5);
	return 0;
}
/**
  * @brief  Konfiguruje REFSEL dla ULPI na 24MHZ
  * @param  none
  * @retval 0
  */
uint8_t ULPI_REFSEL_SET_24MHZ(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Ustaw piny REF0 REF1 i REF2 na stan 1 co daje w sumie 24MHZ zegara taktujacego
	GPIOA->BSRRL=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	
	return 0;
}
/**
  * @brief  Konfiguruje CLKOUT dla ULPI 0 by ten przyjal zegar z REFCLK
  * @param  none
  * @retval 0
  */

uint8_t ULPI_CLOCKOUT_DRIVE_LOW(void){
  GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Ustaw pin ULPI_CK na 0 by ULPI lykalo generowany sygnal zegara
	GPIOA->BSRRH=GPIO_Pin_5;
	
	return 0;
}

/**
  * @brief  Konfiguruje pin resetu dla ULPI
  * @param  none
  * @retval 0
  */

uint8_t ULPI_RESET_CFG(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	return 0;
}

/**
  * @brief  Ustawia pin resetu ULPI
  * @param  state = 1 - Reset high 0- Reset Low
  * @retval 0
  */

uint8_t ULPI_RESET_SET(uint8_t state){
	if (state==1){
		GPIOE->BSRRL=GPIO_Pin_15;
	}
	else {
		GPIOE->BSRRH=GPIO_Pin_15;
	}
	return 0;
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40_41xxx.s/startup_stm32f427_437xx.s/
       startup_stm32f429_439xx.s/startup_stm32f401xx.s) before to branch to 
       application main. To reconfigure the default setting of SystemInit() 
       function, refer to system_stm32f4xx.c file
     */  

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
	
	
	ULPI_RESET_CFG();//Skonfiguruj pin resetu ULPI
	ULPI_RESET_SET(0); //ULPI w statnie resetu
	MCO1_CONF(); //ustaw 24MHZ dla ULPI
	ULPI_REFSEL_SET_24MHZ(); //wybierz ustawienie dla pinu
	ULPI_CLOCKOUT_DRIVE_LOW(); //wysteruj CLKOUT na 0 by ulpi przyjal po resecie zegar jak trzeba. moze nie jest to potrzebne. do testu
	ULPI_RESET_SET(1); //ULPI wyjscie z resetu i normalna operacja
	
	//GPIO_Push_Pull_All_cfg();
  /* Add your application code here */
  /* Insert 50 ms delay */
  Delay(5);
  LED1_ON();
  /* Infinite loop */
  while (1)
	{
		//GPIO_All_Set(0);
	  //Delay(100);
	  //GPIO_All_Set(1);
		//Delay(100);
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

/**
  * @brief  Konfiguruje wszystkie porty GPIO na push pull
  * @param  Nic
  * @retval Nic
  */
void GPIO_Push_Pull_All_cfg(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//Port A
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD |\
												 RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG |\
												 RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | \
																GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | \
																GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_Init(GPIOI, &GPIO_InitStructure);
	
	
	// w GPIOA PA13 i PA14 to sa SWD! NIE MOZNA ICH ODLACZYC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |  GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | \
																GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12| \
																GPIO_Pin_15; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**
  * @brief  Ustawia wszystkie porty w dany stan
  * @param  state - 0 off 1 on
  * @retval Nic
  */
void GPIO_All_Set(uint8_t state){
	if (state==0){
		GPIOA->BSRRL=GPIO_Pin_All;
		GPIOB->BSRRL=GPIO_Pin_All;
		GPIOC->BSRRL=GPIO_Pin_All;
		GPIOD->BSRRL=GPIO_Pin_All;
		GPIOE->BSRRL=GPIO_Pin_All;
		GPIOF->BSRRL=GPIO_Pin_All;
		GPIOG->BSRRL=GPIO_Pin_All;
		GPIOH->BSRRL=GPIO_Pin_All;
		GPIOI->BSRRL=GPIO_Pin_All;
	}
	else {
		GPIOA->BSRRH=GPIO_Pin_All;
		GPIOB->BSRRH=GPIO_Pin_All;
		GPIOC->BSRRH=GPIO_Pin_All;
		GPIOD->BSRRH=GPIO_Pin_All;
		GPIOE->BSRRH=GPIO_Pin_All;
		GPIOF->BSRRH=GPIO_Pin_All;
		GPIOG->BSRRH=GPIO_Pin_All;
		GPIOH->BSRRH=GPIO_Pin_All;
		GPIOI->BSRRH=GPIO_Pin_All;
		//GPIOA->BSRRH=GPIO_Pin_All;
	}
	
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

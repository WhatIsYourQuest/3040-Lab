/*====================================================*/
/* Jake Neal and Cameron Shea */
/* ELEC 3040/3050 - Lab 2, Program 1 */
/*====================================================*/
#include "STM32L1xx.h" /* Microcontroller information */
/* Define global variables */
int state; //current state of the LEDs
unsigned char led1=0; //state of LED1
unsigned char led2=0; //state of LED2
unsigned char led3=0; //state of LED3
unsigned char led4=0; //state of LED4
unsigned char led5=0; //state of LED5
unsigned char led6=0; //state of LED6
unsigned char led7=0; //state of LED7
unsigned char led8=0; //state of LED8

/*---------------------------------------------------*/
/* Initialize GPIO pins used in the program */
/* PA0 = push button */
/* PC8 = blue LED, PC9 = green LED */
/*---------------------------------------------------*/
void PinSetup () {
 /* Configure PA0 as input pin to read push button */
 RCC->AHBENR |= 0x01; /* Enable GPIOA clock (bit 0) */
 GPIOA->MODER &= ~(0x00000000); /* General purpose input mode */
 /* Configure PC8,PC9 as output pins to drive LEDs */
 RCC->AHBENR |= 0x04; /* Enable GPIOC clock (bit 2) */
 GPIOC->MODER &= ~(0x000000FF); /* Clear PC9-PC8 mode bits */
 GPIOC->MODER |= (0x00055555); /* General purpose output mode*/
	
 //EXTI SECTION

//NVIC SECTION
NVIC_EnableIRQ(6); //set bit n to enable IRQ6
NVIC_EnableIRQ(7); //set bit n to enable IRQ7
	
//CPU SECTION
__enable_irq(); //enable interrupts

}
/*----------------------------------------------------------*/
/* Delay function - do nothing for about .5 seconds */
/*----------------------------------------------------------*/
void delay () 
{
   int i,j,n;
   for (i=0; i<20; i++) { //outer loop
   for (j=0; j<8772; j++) { //inner loop
   n = j; //dummy operation for single-step test
   } //do nothing
   }
   
}
/*----------------------------------------------------------*/
/* Count - counts up or down based on value passed into function */
/*----------------------------------------------------------*/
void count (a) 
{  
   state=led1*1+led2*2+led3*4+led4*8;
   if(a==0) //incrementing
   {
      if(state==9)
      {
         state=0;
      }
      else
      {
         state++;
      }
   } 
   else //decrementing
   {
      if(state==0)
      {
         state=9;
      }
      else
      {
         state--;
      }
   }
   switch(state)
   {
      case 0:
         led1=0;
         led2=0;
         led3=0;
         led4=0;
			
			   led5=0;
         led6=0;
         led7=0;
         led8=0;
         break;
      case 1:
         led1=1;
         led2=0;
         led3=0;
         led4=0;
			
				 led5=1;
         led6=0;
         led7=0;
         led8=1;
         break;
      case 2:
         led1=0;
         led2=1;
         led3=0;
         led4=0;
			
			   led5=0;
         led6=0;
         led7=0;
         led8=1;
         break;
      case 3:
         led1=1;
         led2=1;
         led3=0;
         led4=0;
			
			   led5=1;
         led6=1;
         led7=1;
         led8=0;
         break;
      case 4:
         led1=0;
         led2=0;
         led3=1;
         led4=0;
			
			   led5=0;
         led6=1;
         led7=1;
         led8=0;
         break;
      case 5:
         led1=1;
         led2=0;
         led3=1;
         led4=0;
			
			   led5=1;
         led6=0;
         led7=1;
         led8=0;
         break;
      case 6:
         led1=0;
         led2=1;
         led3=1;
         led4=0;
			
			   led5=0;
         led6=0;
         led7=1;
         led8=0;
         break;
      case 7:
         led1=1;
         led2=1;
         led3=1;
         led4=0;
			
			   led5=1;
         led6=1;
         led7=0;
         led8=0;
         break;
      case 8:
         led1=0;
         led2=0;
         led3=0;
         led4=1;
			
			   led5=0;
         led6=1;
         led7=0;
         led8=0;
         break;
      case 9:
         led1=1;
         led2=0;
         led3=0;
         led4=1;
			
			   led5=1;
         led6=0;
         led7=0;
         led8=0;
         break;
   }
   if (led1 == 0)
   GPIOC->BSRR = 0x0001 << 16; 
   else
   GPIOC->BSRR = 0x0001;
   if (led2 == 0)
   GPIOC->BSRR = 0x0002 << 16; 
   else
   GPIOC->BSRR = 0x0002;
   if (led3 == 0)
   GPIOC->BSRR = 0x0004 << 16; 
   else
   GPIOC->BSRR = 0x0004;
   if (led4 == 0)
   GPIOC->BSRR = 0x0008 << 16; 
   else
   GPIOC->BSRR = 0x0008;
	 if (led5 == 0)
   GPIOC->BSRR = 0x0010 << 16; 
   else
   GPIOC->BSRR = 0x0010;
   if (led6 == 0)
   GPIOC->BSRR = 0x0020 << 16; 
   else
   GPIOC->BSRR = 0x0020;
   if (led7 == 0)
   GPIOC->BSRR = 0x0040 << 16; 
   else
   GPIOC->BSRR = 0x0040;
   if (led8 == 0)
   GPIOC->BSRR = 0x0080 << 16; 
   else
   GPIOC->BSRR = 0x0080;
}
/*------------------------------------------------*/
/* Main program */
/*------------------------------------------------*/
int main(void) 
{
   unsigned char sw1=0; //state of SW1
   unsigned char sw2=0; //state of SW2
   
   PinSetup(); //Configure GPIO pins
   
   //the infinite loop will begin by counting up from zero once SW1
while(1)
{
   /* Wait in loop until SW1 pressed to start*/
   while (sw1 == 0x0000) //Wait for SW1 = 1 on PE0
   {    
      sw1 = GPIOA->IDR & 0x0002; //Read GPIOA and mask all but bit 1
      sw2 = GPIOA->IDR & 0x0004; //Read GPIOA and mask all but bit 2
   }
   if(sw2 == 0x0000) //increment
   {
      count(0);
   }
   else //decrement
   {
      count(1);
   }
   delay();
   sw1 = GPIOA->IDR & 0x01; //Read GPIOA and mask all but bit 0
   sw2 = GPIOA->IDR & 0x02; //Read GPIOA and mask all but bit 1

}
}

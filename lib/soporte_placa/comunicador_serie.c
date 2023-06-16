#include "stm32f1xx.h"
#include "comunicador_serie.h"

static void USART_reset () {
    RCC->APB2RSTR = RCC_APB2RSTR_USART1RST;                     //Reinicia el puerto USART1                   
    RCC->APB2RSTR = 0;                                          
}

void USART_init (unsigned long const baudrate) {
 
    uint32_t PA9_SALIDA_50MHZ_Msk = (0b1011 << GPIO_CRH_MODE9_Pos);
    SystemCoreClockUpdate();                                            //Revisa la configuracion de clock y suelta la frecuencia del mismo  
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;          //Activa el clock tanto del puerto A como del USART1
    GPIOA->CRH = (GPIOA->CRH & ~(0xF << GPIO_CRH_MODE9_Pos)) | PA9_SALIDA_50MHZ_Msk; //Configura el pin 9 como un pin de salida rapida
    GPIOA->CRH = (GPIOA->CRH & ~(0xF << GPIO_CRH_MODE10_Pos));          //Como tiene que ser la entrada?
    USART_reset();                                               //Reseteo el USART (Por defecto 8N1)
    USART1->BRR = (SystemCoreClock+1) / baudrate;                //Establece el valor del baudrate en el puerto comunicador serie 
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;   //Habilito el USART1 (CR1->UE = 1), el transmisor (CR1->TE = 1) y el receptor (CR1->RE = 1)                                       
}

bool USART_read (uint32_t *palabra) {
    bool lectura=0;
    if(USART1->SR & USART_SR_RXNE_Msk) {                        //Cuando se recibe un caracter se pone en 1 el RXNE 
        *palabra = USART1->DR; 
        lectura=1;                                              //Lee el dato recibido en DR (RXNE = 0 en SR automaticamente)         
    }
    return (lectura);                                           
}

void USART_write (unsigned int const c) {
    while(~(USART1->SR & (USART_SR_TXE_Msk)));                 //Espero a que el buffer no este lleno (TXE = 1 en SR)
    USART1->DR = c;
}

void USART_deInit () {
    while(~(USART1->SR & (USART_SR_TC_Msk)));                  //Espero a que TC = 1 en SR para asegurarse que finalizo la transmision
}


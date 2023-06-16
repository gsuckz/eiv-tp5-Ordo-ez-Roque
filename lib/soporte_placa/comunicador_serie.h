#ifndef COMUNICADOR_SERIE_H
#define COMUNIADOR_SERIE_H
#include <stdbool.h>

/**
 * @brief Inicializa el puerto de comunicacion serie
 * 
 */
void USART_init (unsigned long const baudrate);

/**
 * @brief Lee el buffer de entrada
 * 
 * @return Valor leido
 */

bool USART_read (uint32_t *palabra);

/**
 * @brief Escribe en el buffer de salida
 * 
 */

void USART_write (unsigned int const c);

/**
 * @brief Desconfigura el puerto de comunicacion serie
 * 
 */

void USART_deInit ();



#endif
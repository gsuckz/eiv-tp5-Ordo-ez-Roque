#ifndef TIMER_H
#define TIMER_H

/**
 * @brief Inicializa el timer
 * 
 */

void TIM_init ();

/**
 * @brief Establece el timer en modo compare
 * 
 */

void TIM_setCompare ();

/**
 * @brief Establece el timer en modo capture
 * 
 */

void TIM_setCapture ();

void TIM_procesa ();

/**
 * @brief Desconfigura el timer
 * 
 */

void TIM_deInit ();


#endif
#include <Ejercicio1_TP3.h>

#use RS232(BAUD = 9600, XMIT = PIN_B5, BITS = 8, PARITY = N, STOP = 1)

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitTimer0(void);
void Init_GPIO(void);

/*****************************************************************************
* Variables globales
****************************************************************************/

/* TIMER 0 */
int contador_ms = 0;
int flag_segundo = 0;

int b1 = 0;
int b2 = 0;
int b3 = 0;

/*****************************************************************************
* Interrupciones
****************************************************************************/

#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {
  
  set_timer0(61);
  
  if(contador_ms >= 20) { //PASO 1 SEG
       contador_ms = 0;
       flag_segundo = 1; // aviso que ya pasó el tiempo deseado
   }
   
   contador_ms++;
}

/*****************************************************************************
* Funciones
****************************************************************************/

void maquina();

void main()
{
   Init_GPIO();
   InitTimer0();
   
      while(TRUE)
      {
         maquina();
      }

}

void InitTimer0(void) {

    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo Interrupcion timer0
    
}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB1 COMO ENTRADA (RX), PB2 COMO SALIDA (TX) */

   set_tris_a(0b11111111); 
   set_tris_b(0b00000000);
   
   enable_interrupts(GLOBAL);
}

void maquina(void) {

   if(flag_segundo == 1) {
   
     if(input(PIN_A0)) {
      printf("Boton 1: PULSADO");
     }
     else {
      printf("Boton 1: NO PULSADO");
     }

     if(input(PIN_A1)) {
      printf("Boton 2: PULSADO");
     }
     else {
      printf("Boton 2: NO PULSADO");
     }
     
     if(input(PIN_A2)) {
      printf("Boton 3: PULSADO");
     }
     else {
      printf("Boton 3: NO PULSADO");
     }
     
      flag_segundo = 0;
   }

}

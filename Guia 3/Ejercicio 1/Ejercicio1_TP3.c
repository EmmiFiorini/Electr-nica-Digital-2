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
   
   output_low(PIN_B0);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
   output_low(PIN_B5);
   output_low(PIN_B6);
   output_low(PIN_B7);

   output_low(PIN_A3);
   output_low(PIN_A4);
   output_low(PIN_A5);
   output_low(PIN_A6);
   output_low(PIN_A7);
   
   enable_interrupts(GLOBAL);
}

void maquina(void) {

b1 = input(PIN_A0);
b2 = input(PIN_A1);
b3 = input(PIN_A2);

   if(flag_segundo == 1) {
     
     /*
      if(b1 == 1)
         putc('0');
         
        if(b1 == 1)
         putc('0');
         
         if(b1 == 1)
         putc('0');
     */
      
     
      printf("Boton 1: %s\r\n", (b1 ? "PULSADO" : "NO PULSADO")); //Operador ternario, si b1 = 1 pulsado, b1 = 0 no pulsado
      printf("Boton 2: %s\r\n", (b2 ? "PULSADO" : "NO PULSADO"));
      printf("Boton 3: %s\r\n", (b3 ? "PULSADO" : "NO PULSADO"));
      printf("------------------------\r\n");
      
     
      flag_segundo = 0;
   }

}

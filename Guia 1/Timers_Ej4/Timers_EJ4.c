#include <Timers_EJ4.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT // Desactivo el watchdog

/*****************************************************************************
 * Variables globales
 ****************************************************************************/

int contador_ms = 0;

int flag_RB4 = 0;
int flag_RB5 = 0;
int flag_RB6 = 0;
int flag_RB7 = 0;

int flag_RB2_high = 1;
int flag_RB1_high = 0;


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO();

/*****************************************************************************
* Funciones
****************************************************************************/

void InitTimer0(void);
void maquina();

/*****************************************************************************
* Interrupciones
****************************************************************************/

#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {
   
   set_timer0(61);
   
   /* INTERRUPCION RB4 */
   if(flag_RB4 == 1 && contador_ms >= 10) {
      output_low(PIN_B0);
      contador_ms = 0;
      flag_RB4 = 0;
   }
   
   /* INTERRUPCION RB5 */
   if(flag_RB5 == 1 && contador_ms >= 20) {
      output_high(PIN_B1);
      flag_RB1_high = 1;
   }
   if(flag_RB1_high == 1 && contador_ms >= 40) {
      output_low(PIN_B1);
      contador_ms = 0;
      flag_RB5 = 0;
      flag_RB1_high = 0;
   }
   
   /* INTERRUPCION RB6 */
   
   
   
   contador_ms++;
}

#INT_RB
void RB_ISR(void) {
   int estadoB = input_b(); // Leo todo el puerto B

   if(bit_test(estadoB, 4)) {//Veo de qué puerto se emitió la interrupción '1'
      flag_RB4 = 1;
   }
   if(bit_test(estadoB, 5)) {
      flag_RB5 = 1;
   }
   if(bit_test(estadoB, 6)) {
      flag_RB6 = 1;
   }
   if(bit_test(estadoB, 7)) {
      flag_RB7 = 1;
   }
}




void main()
{

Init_GPIO();
InitTimer0();

   while(TRUE) {
      maquina();
   }

}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB0-3 y PA0-3 COMO SALIDA */
   set_tris_b(0b11110000);
   set_tris_a(0b11110000);

   output_low(PIN_B0);
   output_low(PIN_B1);
   output_high(PIN_B2);
   output_low(PIN_B3);
   
   output_low(PIN_A0);
   output_low(PIN_A1);
   output_low(PIN_A2);
   output_low(PIN_A3);
   
   enable_interrupts(INT_RB);// HABILITO INTERRUPCIONES EN LOS PINES RB4–RB7
   enable_interrupts(GLOBAL);
}

void InitTimer0(void){
   
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo Interrupcion timer0
}

void maquina() {

   if(flag_RB4 == 1) {
      output_high(PIN_B0);
   }
   
   
   if(flag_RB6 == 1) { //PASO LOS ESTADOS SEGÚN SE ESTE CORRIENDO OTRA INTERRUPCIÓN
         
         /* RB4 */
         if(flag_RB4 == 1) {
         output_high(PIN_A0);
         }
         else{
         output_low(PIN_A0);
         }
         
         /* RB5 */
         if(flag_RB5 == 1) {
         output_high(PIN_A1);
         }
         else{
         output_low(PIN_A1);
         }
         
         /* RB7 */
         if(flag_RB7 == 1 && flag_RB2_high == 1) {
         output_high(PIN_A2);
         output_low(PIN_A3);
         }
         else if(flag_RB7 == 1 && flag_RB2_high != 1) {
         output_low(PIN_A2);
         output_low(PIN_A3);
         }
         
         flag_RB6 = 0;
      }
       
       
      if(flag_RB7 == 1 && flag_RB2_high == 1) {
         output_low(PIN_B2);
         output_high(PIN_B3);
         flag_RB2_high = 0;
         flag_RB7 = 0;
      }
      else if(flag_RB7 == 1 && flag_RB2_high != 1) {
         output_low(PIN_B3);
         output_high(PIN_B2);
         flag_RB2_high = 1;
         flag_RB7 = 0;
      }
}

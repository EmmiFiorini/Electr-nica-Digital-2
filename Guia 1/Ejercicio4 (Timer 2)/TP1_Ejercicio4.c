#include <TP1_Ejercicio4.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT // Desactivo el watchdog

/*****************************************************************************
 * Variables globales
 ****************************************************************************/

int contador_ms = 0;
int flag_tiempo = 0;
int cont = 0;
int contLEDs = 0;

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO();
void PrenderLEDs(int n);
void reset();

/*****************************************************************************
 * Funciones
 ****************************************************************************/

void InitTimer0(void);

#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {
   
   set_timer0(61);   // Reinicio el timer 0
   contador_ms++;
   
   
   if (contador_ms >= 4) { // 4 interrupciones = 200ms
       contador_ms = 0;
       flag_tiempo = 1;
   }

}

void main()
{
/* EJERCICIO 4 */
Init_GPIO();
InitTimer0();

/* LÓGICA: El progreso en los LEDs se muestra conforme a cómo avanza la cuenta.
Si cada 200ms aumento 1 a mi contador, los 256 números se pueden corresponder
con un led cada 32 número que avanza la cuenta. A los 32 --> 1 LED,
a los 64 --> 2 LEDs, etc*/

   while(TRUE)
   {  
   
    if( (cont%32) == 0 && flag_tiempo == 1)
    {
     contLEDs++;
     flag_tiempo = 0;
     PrenderLEDs(contLEDs);
    }
    
    if(contLEDS == 8 && flag_tiempo == 1) {
     reset();
    }
    
   }
}
/* FUNCIONES PARA SETEAR LOS PUERTOS */
void Init_GPIO()
{
/* SETEAMOS TODOS LOS PINES COMO SALIDA */
   set_tris_b(0b11111111);

   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
   output_low(PIN_B5);
   output_low(PIN_B6);
   output_low(PIN_B7);
}

/* FUNCIÓN PARA IR PRENDIENDO LOS LEDs */
void PrenderLEDs(int n)
{
    switch (n)
    {
    case 1:{
    output_high(PIN_B0);
    break;
    }
    
    
    case 2:{
    output_high(PIN_B1);
    break;
    }
    
    case 3:{
    output_high(PIN_B2);
    break;
    }
    
    case 4:{
    output_high(PIN_B3);
    break;
    }
    
    case 5:{
    output_high(PIN_B4);
    break;
    }
    
    case 6:{
    output_high(PIN_B5);
    break;
    }
    
    case 7:{
    output_high(PIN_B6);
    break;
    }
    
    case 8:{
    output_high(PIN_B7);
    break;
    }
    
    default:
    {
    output_low(PIN_B0);
    output_low(PIN_B1);
    output_low(PIN_B2);
    output_low(PIN_B3);
    output_low(PIN_B4);
    output_low(PIN_B5);
    output_low(PIN_B6);
    output_low(PIN_B7);
    }
   }
}

void InitTimer0(void){
   
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler y osc
    
    set_timer0(61);                  // Reinicio el timer
    enable_interrupts(INT_TIMER0);    // Desactivo Interrupcion timer1
    enable_interrupts(GLOBAL);        // Desactivo Interrupciones globales
}

void reset() {

contLEDs = 0;
contador_ms = 0;
flag_tiempo = 0;

    output_low(PIN_B0);
    output_low(PIN_B1);
    output_low(PIN_B2);
    output_low(PIN_B3);
    output_low(PIN_B4);
    output_low(PIN_B5);
    output_low(PIN_B6);
    output_low(PIN_B7);

}

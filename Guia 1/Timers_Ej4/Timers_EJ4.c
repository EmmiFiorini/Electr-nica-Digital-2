#include <Timers_EJ4.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT // Desactivo el watchdog

/*****************************************************************************
 * Variables globales
 ****************************************************************************/

int contador_ms = 0;
int pata = 0;
int vecesPresionado = 0;


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO();

/*****************************************************************************
* Funciones
****************************************************************************/

void InitTimer0(void);
void IdentificarPata(void);

#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {

    set_timer0(61);
    contador_ms++;
    switch(pata) {
        case 4:
               if(contador_ms >= 20) {  // 1 seg
                output_low(PIN_B0); // Pasado el tiempo apagamos LED
                contador_ms = 0;
                pata = 0;
                disable_interrupts(INT_TIMER0);
               }
            break;
        
        case 5:
            if(contador_ms == 20) {  // 1 seg
                output_high(PIN_B1); // Prendemos
            }
            else if(contador_ms >= 40) {  // 2 seg
                output_low(PIN_B1);  // Apagamos
                contador_ms = 0;
                pata = 0;
                disable_interrupts(INT_TIMER0);
            }
            break;
        
        case 7:
            if(contador_ms >= 10) {  // 500ms
                vecesPresionado++;
                output_toggle(PIN_B2);
                output_toggle(PIN_B3);
                contador_ms = 0;
                if(vecesPresionado >= 10) {  // Togglea 10 veces
                    output_low(PIN_B2);
                    output_low(PIN_B3);
                    vecesPresionado = 0;
                    pata = 0;
                    disable_interrupts(INT_TIMER0);
                }
            }
            break;
        default:
            // Nada
            break;
    }
}


void main()
{

Init_GPIO();
InitTimer0();

   while(TRUE)
   {
    IdentificarPata();
    delay_ms(20); //Hasta tener el anti rebote
   }

}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB0-3 y PA0-3 COMO SALIDA */
   set_tris_b(0b11110000);
   set_tris_a(0b11110000);

   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   
   output_low(PIN_A0);
   output_low(PIN_A1);
   output_low(PIN_A2);
   output_low(PIN_A3);
}

void InitTimer0(void){
   
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo Interrupcion timer0
    enable_interrupts(GLOBAL);        // Activo Interrupciones globales
}

void IdentificarPata() {

   if(!input(PIN_B4) && pata == 0) {
     pata = 4;
     output_high(PIN_B0);
     set_timer0(61);                   // arranco el conteo
     enable_interrupts(INT_TIMER0);    // habilito interrupción recien ahora
   } 
   else if(!input(PIN_B5) && pata == 0) {
     pata = 5;
     set_timer0(61);
     enable_interrupts(INT_TIMER0);
   }
   else if(!input(PIN_B6) && pata == 0) {
     pata = 6;
   }
   else if(!input(PIN_B7) && pata == 0) {
     pata = 7;
     set_timer0(61);
     enable_interrupts(INT_TIMER0);
   }
}

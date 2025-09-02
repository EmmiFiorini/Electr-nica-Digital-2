#include <Semaforo.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Variables globales
 ****************************************************************************/


int flag_segundo = 0;
int max = 0;
int contador_ms = 0;

/*****************************************************************************
 * Maquina de estado
 ****************************************************************************/

typedef enum {
    VERDE,
    AMARILLO,
    ROJO
} eEstado;

eEstado estado_actual = VERDE;

void MaquinaEstado(void);

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitGPIO(void);
void InitTimer0(void);
void InicioCuentaTimer(int maximo);


#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {
   
   set_timer0(61);   // Reinicio el timer 0
   contador_ms++;
   
   
   if (contador_ms >= max) { // max = Depende de la cantidad de segundos que queremos contar
       contador_ms = 0;
       flag_segundo = 1; // aviso que ya pasó el tiempo deseado
   }

}

void main()
{
   InitGPIO();    // Inicializo puertos
   InitTimer0();  // Inicializo el Timer0
   while (TRUE) {
      MaquinaEstado();
   }
}


void MaquinaEstado(void){
   switch (estado_actual) {
      
      case VERDE:
         
         output_low(PIN_B1);
         output_low(PIN_B2);
         output_high(PIN_B0);
         
         if (flag_segundo) {        // ¿ya pasaron 5 segundos?
             flag_segundo = 0;      // limpio flag
             InicioCuentaTimer(40);  // vuelvo a iniciar timer para el siguiente estado
             estado_actual = AMARILLO;        
         }
         break;
         
      case AMARILLO:
         
         output_low(PIN_B0);
         output_low(PIN_B2);
         output_high(PIN_B1);
         
         if (flag_segundo) {        // ¿ya pasaron 2 segundos?
             flag_segundo = 0;      // limpio flag
             InicioCuentaTimer(100);  // vuelvo a iniciar timer para el siguiente estado
             estado_actual = ROJO;        
         }
         
         break;
         
      case ROJO:
         
         output_low(PIN_B0);
         output_low(PIN_B1);
         output_high(PIN_B2);
        
          if (flag_segundo) {        // ¿ya pasaron 5 segundos?
             flag_segundo = 0;      // limpio flag
             InicioCuentaTimer(100);  // vuelvo a iniciar timer para el siguiente estado
             estado_actual = VERDE;        
         }
         
         break;  
      }
}

void InitGPIO(void){
    set_tris_b(0b11111000);// PORTA como ENTRADA menos RA2 que es salida

    output_high(PIN_B0);// VERDE
    output_low(PIN_B1);// AMARILLO
    output_low(PIN_B2);// ROJO
    
    max = 100;
}

void InitTimer0(void){
   
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler y osc
    
    set_timer0(0x3D);                  // Reinicio el timer
    enable_interrupts(INT_TIMER0);    // Desactivo Interrupcion timer1
    enable_interrupts(GLOBAL);        // Desactivo Interrupciones globales
}

void InicioCuentaTimer(int maximo){

   max = maximo;

   set_timer0(61);                  // Reinicio el timer
   contador_ms = 0;                 // Reinicio el acumulador
}


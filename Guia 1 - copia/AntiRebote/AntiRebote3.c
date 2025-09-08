#include <AntiRebote3.h>

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * LCD
 ****************************************************************************/

#define LCD_ENABLE_PIN  PIN_B0
#define LCD_RS_PIN      PIN_B1
#define LCD_RW_PIN      PIN_B2
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7
#include <lcd.c>

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/
 
 /*typedef enum {
    SUELTO,
    Q_PRESIONADO,
    PRESIONADO,
    Q_SUELTO
} eEstado;*/

typedef enum {
    SUELTO,
    PRESIONADO,
    Q_PRES,
    Q_SUELTO
} eEstado;

eEstado estado_actual = SUELTO;

/*volatile int flag_pulsado = 0;
volatile int flag_segundo = 0;
volatile int flanco_d = 0;
volatile int flanco_a = 0;*/

int16 flag_segundo = 0;
int valor = 0;
int16 overflow_count=0; //mi contador q uso en el timer

//FUNCIONES
void MaquinaEstado(void);
void InitGPIO(void);
void EscribirDisplay(signed int valor);
int8 EstadoPulsador(void);
void InitTimer0(void);


#INT_TIMER0 // ACA ESCRIBO QU� DEBO HACER EN CADA INTERRUPCI�N
void Timer0_ISR() {
   set_timer0(178);   // Reinicio el timer 0
   overflow_count++; //incremento el contador
}

/*****************************************************************************
 * Main
 ****************************************************************************/

void main(void) {
   
   InitGPIO();    // Inicializo el PORTA y PORTB
   lcd_init();// Inicializo LCD
   InitTimer0();
  
   printf(LCD_PUTC,"Cuenta: %d",valor);
   estado_actual=SUELTO;
   while (TRUE) {
      if( overflow_count >= 1) {
         overflow_count = 0;
         MaquinaEstado();
      }
   }
}

/*****************************************************************************
 * Implementacion de funciones
 ****************************************************************************/
 
void InitGPIO(void){
    set_tris_a(0xFF);   // PORTA como ENTRADA
    set_tris_b(0x00);   // PORTB como SALIDA
    output_b(0x00); //inicialuizo en 0
}

void EscribirDisplay(signed int valor) {
   lcd_putc('\f');
   printf(LCD_PUTC,"Cuenta: %d",valor);
}

int8 EstadoPulsador(void)
{
   int8 res = 0;
   res = input(PIN_A0);
   return res;
}

void InitTimer0(void){
   
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler y osc
    
    set_timer0(178);                  // Reinicio el timer
    enable_interrupts(INT_TIMER0);    // Desactivo Interrupcion timer1
    enable_interrupts(GLOBAL);        // Desactivo Interrupciones globales
}

void MaquinaEstado(void){
    int boton = EstadoPulsador(); //funcion q cambia el estado

    switch (estado_actual) { //entro en el switch

        case SUELTO:
            if(boton == 1){// bot�n presionado (activo en 0)
                estado_actual = PRESIONADO;
                flag_segundo=0;
            }
            break;
            
            case PRESIONADO:
            if(boton == 1){
                flag_segundo++;
                if(flag_segundo >= 20) //20 = tiempo del antirebote
                  estado_actual = Q_PRES;
            }else {
            // El bot�n se liber� antes de tiempo 
            estado_actual = SUELTO;
         }
            break;

        case Q_PRES:
            if(boton == 0){
                // pas� el tiempo de rebote y sigue apretado
                estado_actual = Q_SUELTO;
            } 
            break;

        case Q_SUELTO:// estuvo presionado y ahora se solt� estable
                valor++; //incremento el valor
                EscribirDisplay(valor);
                estado_actual = SUELTO;
            }
            break;
            
       default: //x si falla
         estado_actual = SUELTO;
         break;
    }
}



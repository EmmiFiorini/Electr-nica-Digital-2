#include <Punto5.h>

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * LCD
 ****************************************************************************/

#define LCD_ENABLE_PIN  PIN_B1
#define LCD_RS_PIN      PIN_B2
#define LCD_RW_PIN      PIN_B3 // CONECTADO A GND SI NO LO USAMOS
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7

#include <lcd.c>
#include <kbd.c>

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/
 
void Init_GPIO(void);
void Init_ADC(void);
void InitTimer0(void);

/*****************************************************************************
* Estados
****************************************************************************/
typedef enum {
    ESCRITURA,
    LECTURA, 
    STAND_BY
} eEstado;

eEstado estado_actual = STAND_BY;

/*****************************************************************************
* Funciones
****************************************************************************/

void maquina(void);


/*****************************************************************************
* Variables globales
****************************************************************************/

/* ADC */
int16 resultado_adc=0;
int flag_adc = 0;


/* TIMER 0 */
int contador_ms = 0;
int flag_segundo = 0;

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

#INT_AD
void ISR_ADC(void) {
   resultado_adc = read_adc(ADC_READ_ONLY);
   flag_adc = 1;
   
}

/*****************************************************************************
* Main
****************************************************************************/
void main()
{

   Init_GPIO();
   lcd_init(); //inicializo el led
   kbd_init();//inicializo el teclado
   Init_ADC();
   InitTimer0();

   while(TRUE) {
      maquina();
   }

}

void maquina(void) {
   switch(estado_actual){
      case 
   
   }

}

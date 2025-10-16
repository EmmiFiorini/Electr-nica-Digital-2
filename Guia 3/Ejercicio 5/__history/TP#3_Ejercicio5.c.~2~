#include <TP#3_Ejercicio5.h>

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

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitTimer0(void);
void Init_GPIO(void);
void Init_ADC(void);

/*****************************************************************************
* Variables globales
****************************************************************************/

/* ADC */
int16 resultado_adc=0;
int flag_adc = 0;

/* INTERRUPCIONES EXTERNAS */
int flag_RB0 = 0;

/* TIMER 0 */
int contador_ms = 0;
int flag_segundo = 0;

/*****************************************************************************
* Interrupciones
****************************************************************************/
/*****************************************************************************
* Funciones
****************************************************************************/
void maquina(void);

void main()
{
   Init_GPIO();
   lcd_init();
   Init_ADC();
   InitTimer0();

   while(TRUE)
   {


      //TODO: User Code
   }

}
void InitTimer0(void) {

    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo Interrupcion timer0
    
}

void Init_GPIO()
{
   set_tris_a(0b11111111); 
   set_tris_b(0b00000100);

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
}

void maquina() {
}

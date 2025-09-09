#include <Ejercicio1_TP2.h>

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * LCD
 ****************************************************************************/

#define LCD_ENABLE_PIN  PIN_B0
#define LCD_RS_PIN      PIN_B1
#define LCD_RW_PIN      PIN_B2 // CONECTADO A GND SI NO LO USAMOS
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7
#include <lcd.c>


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO();

/*****************************************************************************
* Estados
****************************************************************************/
typedef enum {
    MSJ_1,
    MSJ_2,
    MSJ_3
} eEstado;

eEstado estado_actual = MSJ_1;
/*****************************************************************************
* Variables globales
****************************************************************************/
int contador = 0;
int contador_ms = 0;
int flag_segundo = 0;
/*****************************************************************************
* Funciones
****************************************************************************/
void InitTimer0(void);
void maquina(void);



#INT_TIMER0 // ACA ESCRIBO QUÉ DEBO HACER EN CADA INTERRUPCIÓN
void Timer0_ISR() {
  
  set_timer0(61);
  if(contador_ms >= 20) { //PASO 1 SEG
       contador_ms = 0;
       flag_segundo = 1; // aviso que ya pasó el tiempo deseado
   }
   contador_ms++;
}

void main()
{

Init_GPIO();
lcd_init();
InitTimer0();

   while(TRUE) {
   maquina();
   }

}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB0-PB7 COMO SALIDA */
   set_tris_b(0x00);
   output_b(0x00); // TODO COMO SALIDA EN ESTADO BAJO (SI TENGO PINES COMO ENTRADA, LOS FUERZA A SER SALIDA)
   
}

void InitTimer0(void) {

    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo Interrupcion timer0
    enable_interrupts(GLOBAL);        // Activo Interrupciones globales
}

void maquina() {
 
 switch(estado_actual) {
 
  case MSJ_1: 

   if(flag_segundo == 1) {
    lcd_putc("\f");
    printf(LCD_PUTC,"Hello World");
    flag_segundo = 0;
    estado_actual = MSJ_2;
   }
  break;
  
 
  case MSJ_2: 
  
  if(flag_segundo == 1) {
    lcd_putc("\f");
    printf(LCD_PUTC,"Bienvenidos a");
    lcd_gotoxy(1,2); // DIVIDIMOS EN 2 'RENGLONES'. MAXIMO 2 RENGLONES TENEMOS
    printf(LCD_PUTC,"EDI 2");
    flag_segundo = 0;
    estado_actual = MSJ_3;
   }
  break;
  
 
  case MSJ_3: 
  
  if(flag_segundo == 1) {
   lcd_putc("\f");
   lcd_gotoxy(1,1); // REESTABLECEMOS EL PUNTERO DEL CURSOR
   printf(LCD_PUTC,"Contador = %d",contador);
   contador++;
   flag_segundo = 0;
   estado_actual = MSJ_1;
   }
   break;
  
  default:
  estado_actual = MSJ_1;
 }
 
}

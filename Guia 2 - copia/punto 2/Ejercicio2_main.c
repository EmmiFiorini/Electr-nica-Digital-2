#include <Ejercicio2_main.h>
#define use_portb_lcd TRUE
#include <lcd.c>


#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog


/***************************
 * LCD
 **************************/

#define LCD_ENABLE_PIN  PIN_B0
#define LCD_RS_PIN      PIN_B1
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7


/***************************
 * Funciones de Inicializacion de Perifericos
 **************************/

void Init_GPIO();

/***************************
•?  ?Estados
**************************/
typedef enum {
    Espero,
    Prendido,
    Apagado,
} eEstado;

eEstado estado_actual = Espero ;

/***************************
•?  ?Funciones
**************************/

void maquina(void);

void main()
{

Init_GPIO();
lcd_init();

   while(TRUE) {
   maquina();
   }

}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB0-PB7 COMO SALIDA */
   set_tris_b(0x00);
   
/* SETEAMOS LOS PINES RA0 y RA1 como entrada */
   set_tris_a(0b00000011);
   
}

void maquina() {
 
 switch(estado_actual) {
 
  case Espero:

   if(input(PIN_A0) == 0) {
   printf(LCD_PUTC,"\f");
    printf(LCD_PUTC,"Prendiendo");
   estado_actual = Prendido;
   }
  break;
 
  case Prendido:

  if(input(PIN_A1) == 0) {
   printf(LCD_PUTC,"\f");
   printf(LCD_PUTC,"Apangando");
   estado_actual = Apagado;
   }
  break;
 
  case Apagado:
  
  if(input(PIN_A0) == 0) {
  printf(LCD_PUTC,"\f");
   printf(LCD_PUTC,"Prendiendo");
   estado_actual = Prendido;
   }
   break;
 
  default:
  estado_actual = Espero;
 }
 
}

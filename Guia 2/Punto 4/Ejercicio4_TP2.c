#include <Ejercicio4_TP2.h>

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * LCD
 ****************************************************************************/

#define LCD_ENABLE_PIN  PIN_A0
#define LCD_RS_PIN      PIN_A1
#define LCD_RW_PIN      PIN_A2 // CONECTADO A GND SI NO LO USAMOS
#define LCD_DATA4       PIN_A4
#define LCD_DATA5       PIN_A5
#define LCD_DATA6       PIN_A6
#define LCD_DATA7       PIN_A7
#include <lcd.c>


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO();

/*****************************************************************************
* Estados
****************************************************************************/
typedef enum {

} eEstado;

eEstado estado_actual = ;
/*****************************************************************************
* Variables globales
****************************************************************************/

/*****************************************************************************
* Teclado
****************************************************************************/

char teclado[4][4] = {
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}
};
/*****************************************************************************
* Funciones
****************************************************************************/
char read_keypad();
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
   set_tris_b(0b00001111); RB0-RB3 = entrada, columnad, RB4-RB7 = Filas, salidas
   set_tris_a(0b00000000); // TODO COMO SALIDA EN ESTADO BAJO 
   
}

char read_keypad() {
   int fila, col;
   for(fila=0; fila<4; fila++) {
      output_b(0b11111111);            // Todas filas en 1
      output_low(PIN_B4+fila);         // Activar una fila en 0

      for(col=0; col<4; col++) {
         if(!input(PIN_B0+col)) {     // Si columna detecta 0, tecla presionada
            while(!input(PIN_B0+col)); // Esperar que suelte la tecla
            return teclado[fila][col];
         }
      }
   }
   return 0; // nada presionado
}

void maquina() {
 
 switch(estado_actual) {
 

 
}

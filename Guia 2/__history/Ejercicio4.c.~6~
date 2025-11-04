#include <Ejercicio4.h>

#fuses INTRC_IO  // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR   // Desactivo el MCLR
#fuses NOWDT   // Desactivo el watchdog

/*****************************************************************************
 * LCD
 ****************************************************************************/


#define LCD_ENABLE_PIN  PIN_A0
#define LCD_RS_PIN      PIN_A1
#define LCD_RW_PIN      PIN_A2 // CONECTADO A GND SI NO LO USAMOS
#define LCD_DATA4       PIN_A4
#define LCD_DATA5       PIN_A3
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
   ESPERAR,     // Espero que se presione una tecla
   MOSTRAR,      // Muestro la tecla en el LCD
} eEstado;

eEstado estado_actual = ESPERAR;
/*****************************************************************************
* Variables globales
****************************************************************************/
char tecla = 0 ; // tecla que se presiona
int fila_pins[4] = {PIN_B4, PIN_B5, PIN_B6, PIN_B7};
int col_pins[3] = {PIN_B0, PIN_B1, PIN_B2};

/*****************************************************************************
* Teclado
****************************************************************************/

char teclado[4][3] = {{'1','2','3'},
                      {'4','5','6'},
                      {'7','8','9'},
                      {'*','0','#'}};

/*****************************************************************************
* Funciones
****************************************************************************/
char read_keypad(void);
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
  // Estas funciones hacen lo mismo que ANSELA=0 y ANSELB=0
    setup_adc_ports(NO_ANALOGS); 
    
    // El 16F1827 también tiene comparadores que usan pines de PORTA.
    // Hay que desactivarlos también.
    setup_comparator(NC_NC_NC_NC);
/* SETEAMOS LOS PINES PB0-PB7 COMO SALIDA */
   set_tris_b(0b11111000); //RB0-RB2 = columnas, salidas, RB4-RB7 = Filas, entradas
   set_tris_a(0b00000000); // TODO COMO SALIDA EN ESTADO BAJO 
   
   port_b_pullups(TRUE);
   
}

char read_keypad(void) {

   int f, c;
   char result = '0';
   
   for(f = 0; f < 4; f++) {
      // Poner todas las filas en HIGH
      output_high(PIN_B0);
      output_high(PIN_B1);
      output_high(PIN_B2);
      output_high(PIN_B3);

      // Activar la fila r (tirarla a LOW)
      output_low(fila_pins[f]);

      // Leemos columnas
      for(c = 0; c < 3; c++) {
         if(!input(col_pins[c])) { // columna detectada en 0 --> tecla presionada

            if(!input(col_pins[c])) { // sigue presionada
               result = teclado[f][c];
               return result;
            }
         }
      }
   }

   return 0; // nada presionado
}

void maquina() {
   switch(estado_actual) {
         case ESPERAR:
            tecla = read_keypad();       // leo teclado
            if(tecla != 0) {             // si presionaron algo, no hay 0 en el teclado
               estado_actual = MOSTRAR;
            }
         break;
   
         case MOSTRAR:
            lcd_putc(tecla);  // mostrar tecla
            estado_actual = ESPERAR;     // volver a esperar
         break;

   }
}

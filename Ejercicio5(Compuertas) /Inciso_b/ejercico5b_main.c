#include <main.h>

#fuses INTRC_IO // Utilizo oscilador interno con pines RA6 y RA7 como GPIO 
#fuses NOMCLR // Desactivo el MCLR 
#fuses NOWDT // Desactivo el watchdog

void Init_GPIO(void);

// Tabla de conversión de hexadecimal a número
const int tabla[10] = {
   0x3F, // 0
   0x06, // 1
   0x5B, // 2
   0x4F, // 3
   0x66, // 4
   0x6D, // 5
   0x7D, // 6
   0x07, // 7
   0x7F, // 8
   0x6F  // 9
};

void main() {
   int i;
   Init_GPIO();

   while(TRUE) {
      for(i = 0; i < 10; i++) {
         output_b(tabla[i]);   // Muestra número en display
         delay_ms(500);        // Retardo medio segundo
      }
   }
}

void Init_GPIO(void){

   set_tris_b(0x00);  // PORTB como salida conectado al display
   output_b(0x00);    // Apagar al inicio

}

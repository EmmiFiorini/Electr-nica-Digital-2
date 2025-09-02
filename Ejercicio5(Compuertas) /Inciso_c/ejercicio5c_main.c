#include <main.h>

#fuses INTRC_IO // Utilizo oscilador interno con pines RA6 y RA7 como GPIO 
#fuses NOMCLR // Desactivo el MCLR 
#fuses NOWDT // Desactivo el watchdog

void Init_GPIO(void);

// Tabla de conversi�n de hexadecimal a n�mero
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
   int contador = 0;
   Init_GPIO();

   while(TRUE) {
         output_b(tabla[contador]);   // Muestra n�mero en display
     
      // Si se aprieta el bot�n en RA0
      if(!input(PIN_A0)) {
         delay_ms(10); // Antirrebote
         if(!input(PIN_A0)) { // si sigue presionado
            contador++;
            if(contador >= 10) 
               contador = 0; // Vuelve a 0 despu�s de 9
            while(!input(PIN_A0)); // Esperar a que se suelte el bot�n
         }
      }   
   }
}

void Init_GPIO(void){

   set_tris_b(0x00);// PORTB como salida conectado al display
   set_tris_a (0x01); // RA0 como entrada
   output_b(0x00); // Apagar al inicio
}

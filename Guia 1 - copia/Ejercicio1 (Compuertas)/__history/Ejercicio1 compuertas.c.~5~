#include <Ejercicio1 compuertas.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

// DEFINICION DE FUNCIONES
void InitGPIO(void); //inicializo los puesrtos

/*Configurar el puerto B de la siguiente manera: PIN_B7, PIN_B6,
PIN_B5, PIN_B4 como entradas, y PIN_B3, PIN_B2, PIN_B1, y PIN_B0 como
salidas. Suponiendo que dichas salidas están conectadas a 4 leds, enviar por
dichas salidas un dato que permita prender solamente los leds conectados a las
líneas 0 y 1. Suponer que los leds se activan por estado alto.*/

//MAIN
void main()
{
   InitGPIO();

   while(TRUE)
   {
      if(!input(PIN_B4))  { // cuando el pin está en 0 (botón apretado)
         output_high(PIN_B0);
         delay_ms(500);//espero 500ms
         output_low(PIN_B0);
      }else
         output_low(PIN_B0);
   
      if(!input(PIN_B5)){   // cuando el pin está en 0 (botón apretado)
         output_high(PIN_B1);
         delay_ms(500);//espero 500ms
         output_low(PIN_B1);
      }else
         output_low(PIN_B1);
         
         if(!input(PIN_B6))  { // cuando el pin está en 0 (botón apretado)
         output_high(PIN_B2);
         delay_ms(500);//espero 500ms
         output_low(PIN_B2);
         }else
         output_low(PIN_B2);
         
         if(!input(PIN_B7)){   // cuando el pin está en 0 (botón apretado)
         output_high(PIN_B3);
         delay_ms(500);//espero 500ms
         output_low(PIN_B3);
         }else
         output_low(PIN_B3);
   }
}

/*void main()
{

   while(TRUE)
   {
      if(input(PIN_B4)){
         output_high(PIN_B0); //prendo el led
         delay_ms(500);//espero 500ms
         output_low(PIN_B0);
      }
   if(input(PIN_B5)){
         output_high(PIN_B1); //prendo el led
         delay_ms(500);//espero 500ms
         output_low(PIN_B1);
      }
      if(input(PIN_B6)){
         output_high(PIN_B2); //prendo el led
         delay_ms(500);//espero 500ms
         output_low(PIN_B2);
      }
      if(input(PIN_B7)){
         output_high(PIN_B3); //prendo el led
         delay_ms(500);//espero 500ms
         output_low(PIN_B3);
      }
   }

}*/

//INICIALIZACION FUNCIONES
void InitGPIO(void) {
setup_adc_ports(NO_ANALOGS); // Todos los pines como digitales
   // 1) defino a mis puertos como entrada y salida
   set_tris_b(0b11110000); //RB7–RB4 entradas, RB3–RB0 salidas

   // 2) los inicializo en low
   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
   output_low(PIN_B5);
   output_low(PIN_B6);
   output_low(PIN_B7);
}

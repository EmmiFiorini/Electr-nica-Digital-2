#include <Ejercicio7_TP2.h>

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void Init_GPIO(void);
void Init_ADC(void);
void Init_DAC(void);

/*****************************************************************************
* Variables globales
****************************************************************************/

/* ADC */
unsigned int16 resultado_adc = 0;
int flag_adc = 0;

/* DAC */
unsigned int8 resultado_dac = 0;

/*****************************************************************************
* Funciones
****************************************************************************/


/*****************************************************************************
* Interrupciones
****************************************************************************/

#INT_AD
void ISR_ADC(void) {

   resultado_adc = read_adc(ADC_READ_ONLY); // Leo conversión (10 bits)
   resultado_dac = resultado_adc >> 5; // Paso de 10 bits --> 5 bits (0–31)
   
   // Mando los 5 bits menos significativos al puerto B (RB0–RB4)
   output_b(resultado_dac & 0x1F); //Envío 5 bits al dac
   
   flag_adc = 1;
}


void main()
{

Init_GPIO();
Init_ADC();
Init_DAC();

   while(TRUE)
   {
      if(flag_adc == 1) {
         read_adc(ADC_START_ONLY);
         flag_adc = 0;
      }
   }

}

void Init_GPIO()
{
/* SETEAMOS LOS PINES PB1-PB7 COMO SALIDA */
   set_tris_a(0b00000001);   // RA0 (AN0) = entrada, resto salida
   set_tris_b(0b11100000);   // RB0–RB4 = salida DAC, RB5–RB7 no usados

   output_b(0x00);           // Apago DAC al inicio
   
   enable_interrupts(GLOBAL);
}

void Init_ADC() {

   setup_adc_ports(sAN0); // Habilito pin AN0 como entrada analógica
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   enable_interrupts(INT_AD);

}

void Init_DAC(void) {
   setup_dac(DAC_VSS_VDD|DAC_OUTPUT);
}


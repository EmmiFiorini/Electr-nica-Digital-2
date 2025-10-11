#include <Grupo11_EjercicioPresencial.h>

#use RS232(BAUD = 9600, RCV = PIN_B2, XMIT = PIN_B5, BITS = 8, PARITY = N, STOP = 1)

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Funciones de Inicializacion
 ****************************************************************************/

void InitTimer0(void);
void Init_GPIO(void);
void Init_ADC(void);

/*****************************************************************************
* Variables globales
****************************************************************************/

/* TIMER 0 */
int contador_ms = 0;
int flag_segundo = 0;

/* PROTOCOLO SR232 */
int contador = 0;
int accion = 0;
int esperando_mostrado = 0;

char c1=' ';
char c2=' ';

/* ADC */
int16 resultado_adc = 0;
int flag_adc = 0;

/*****************************************************************************
* Interrupciones
****************************************************************************/
#INT_AD
void ISR_ADC(void) {
   resultado_adc = read_adc(ADC_READ_ONLY);
   flag_adc = 1;
   
}

#int_rda
void RDA_isr() {
   
   if(contador == 0) {
      c1 = getc();
      contador = 1;
      
   }
   
   if((c1 == 'S' || c1 == 's') && contador == 1) {
      c2 = getc();
      
      if(c2 == '0') {
         accion = 1;
      }
      if(c2 == '1') {
         accion = 2;
      }
      contador = 0;
   }
}

/*****************************************************************************
* Funciones
****************************************************************************/

void maquina(void);

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

void main()
{
   Init_GPIO();
   InitTimer0();
   Init_ADC();

   enable_interrupts(GLOBAL);
   
   while(TRUE) {
      
      read_adc(ADC_START_ONLY);
      maquina();
   }

}

void InitTimer0(void) {

    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256); // Configuro prescaler
    
    set_timer0(61);                  // Reinicio el timer --> Interrupciones cada 50ms
    enable_interrupts(INT_TIMER0);    // Activo interrupcion timer0
}

void Init_GPIO()
{
   set_tris_a(0b11111111); 
   set_tris_b(0b00000100);
   
   output_low(PIN_A1);
   output_low(PIN_A2);
   output_low(PIN_A3);
   output_low(PIN_A4);
   output_low(PIN_A5);
   output_low(PIN_A6);
   output_low(PIN_A7);
   
   enable_interrupts(INT_RDA);
}

void Init_ADC() {

      setup_adc_ports(sAN0);
      setup_adc(ADC_CLOCK_INTERNAL);
      set_adc_channel(0);
      
      enable_interrupts(INT_AD);
}

void maquina() {
   
   switch(accion) {
   
      case 0:
            if(!esperando_mostrado) {
               printf("\r\nEsperando...\r\n");
               esperando_mostrado = 1; 
            }
           
            break;
      
      case 1:
            printf("\r\nNo se mandan mas datos\r\n");
            accion = 0;
            break;
      
      case 2:
               if(flag_segundo == 1 && flag_adc == 1) {
                  
                  printf("\r\nPot = %ld",resultado_adc);
                  printf("\r\nRA1 = %u ", input(PIN_A1));
                  printf("\r\n------------------------\r\n");
                  flag_segundo = 0;
                  esperando_mostrado = 0;
                  flag_adc = 0;
                  }
            break;
            
      default:
            accion = 0;
            
   }
}

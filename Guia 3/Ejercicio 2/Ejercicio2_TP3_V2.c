#include <Ejercicio2_TP3_V2.h>

#use RS232(BAUD = 9600, RCV = PIN_B2, XMIT = PIN_B5, BITS = 8, PARITY = N, STOP = 1)

#fuses INTRC_IO   // Oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitTimer0(void);
void Init_GPIO(void);

/*****************************************************************************
* Variables globales
****************************************************************************/

/* TIMER 0 */
int contador_ms = 0;
int flag_segundo = 0;

int contador = 0;
int accion = 0;
int esperando_mostrado = 0;

char c1=' ';
char c2=' ';

int N = 1;

/*****************************************************************************
* Interrupciones
****************************************************************************/

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

   if(c1 == 'M' || c1 == 'm') {
      
      c2 = getc();
      
         if(c2 == '0') {
            accion = 3;
         }
         if(c2 == '1') {
            accion = 4;
         }
         if(c2 == '2') {
            accion = 5;
         }
         contador = 0;
   }

  if(c1 == 'C' || c1 == 'c') {
      
      c2 = getc();
      
         if(c2 == '0') {
            accion = 6;
         }
         if(c2 == '1') {
            accion = 7;
         }
         if(c2 == '2') {
            accion = 8;
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
  
  if(contador_ms >= (2*N)) { //PASO 1 SEG
       contador_ms = 0;
       flag_segundo = 1; // aviso que ya pasó el tiempo deseado
   }
   
   contador_ms++;
}

void main()
{
   Init_GPIO();
   InitTimer0();
   setup_adc_ports(NO_ANALOGS);

   while(TRUE) {
      maquina();
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
   
   switch(accion) {
   
      case 0:
            if(!esperando_mostrado) {
               printf("\r\nEsperando...");
               esperando_mostrado = 1; 
            }
           
            break;
      
      case 1:
            printf("\r\nNo se mandan mas datos");
            accion = 0;
            break;
      
      case 2:
               if(flag_segundo == 1) {
               
                  printf("\n");
                  printf("RA0=%u RA1=%u RA2=%u\r\n", input(PIN_A0), input(PIN_A1), input(PIN_A2));
                  printf("------------------------\r\n");
                  flag_segundo = 0;
                  esperando_mostrado = 0;
                  }
            break;
            
      case 3:
            printf("RA0=%u \r\n", input(PIN_A0));
            esperando_mostrado = 0;
            break;
            
      case 4:
            printf("RA1=%u \r\n", input(PIN_A1));
            esperando_mostrado = 0;
            break;
            
      case 5:
            printf("RA2=%u \r\n", input(PIN_A2));
            esperando_mostrado = 0;
            break;
            
      case 6:
            N = 1;
            accion = 2;
            esperando_mostrado = 0;
            break;
            
      case 7:
            N = 5;
            accion = 2;
            esperando_mostrado = 0;
            break;
            
      case 8:
            N = 10;
            accion = 2;
            esperando_mostrado = 0;
            break;
            
      default:
            accion = 0;
            
   }
   
}

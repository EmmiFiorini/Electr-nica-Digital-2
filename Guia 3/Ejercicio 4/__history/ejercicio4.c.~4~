#include <ejercicio4.h>
#use delay(clock=4000000)

#fuses INTRC_IO, NOWDT, NOMCLR



// =================== CONFIGURACIÓN I2C ===================
#use i2c(MASTER, SDA=PIN_B1, SCL=PIN_B4, FAST=100000)

// Dirección del chip PCF8574 (ajustar si es necesario)
#define I2C_LCD_DIR 0x40   // En Proteus suele funcionar con 0x40

// =================== PINES DEL LCD ===================
#define LCD_RS  0x01   // Bit 0 ? RS
#define LCD_RW  0x02   // Bit 1 ? RW
#define LCD_EN  0x04   // Bit 2 ? Enable
// Bits 4–7 ? D4–D7

// =================== PROTOTIPOS ===================
void i2c_enviar_byte(int8 dato);
void lcd_enviar_4bits(int8 nibble, int1 es_texto);
void lcd_comando(int8 comando);
void lcd_texto(char letra);
void lcd_iniciar(void);

// =================================================
void main() {

   lcd_iniciar();                  // Inicializo el LCD

   lcd_comando(0x80);              // Cursor al inicio (fila 1)
   printf(lcd_texto, "ELECTRONICA");    // Escribo texto

   lcd_comando(0xC0);              // Fila 2
   printf(lcd_texto, "DIGITAL");

   while(TRUE) {
      // Programa principal (no hace falta apretar nada)
   }
}

// =================================================
// FUNCIONES
// =================================================

// Envía un byte por I2C al PCF8574
void i2c_enviar_byte(int8 dato) {
   i2c_start();
   i2c_write(I2C_LCD_DIR | 0);   // Dirección + bit de escritura (0)
   i2c_write(dato);
   i2c_stop();
}

// Envía 4 bits al LCD (nibble)
void lcd_enviar_4bits(int8 nibble, int1 es_texto) {
   int8 byte_i2c;

   // Paso 1: Alineo el nibble con los pines de datos D4–D7
   byte_i2c = (nibble << 4);

   // Paso 2: Si es texto, activo RS
   if(es_texto)
      byte_i2c |= LCD_RS;

   // Paso 3: Pulso Enable para que el LCD lea el dato
   i2c_enviar_byte(byte_i2c | LCD_EN);   // EN=1
   delay_us(10);
   i2c_enviar_byte(byte_i2c & ~LCD_EN);  // EN=0
}

// Envía un comando (RS=0)
void lcd_comando(int8 comando) {
   lcd_enviar_4bits(comando >> 4, 0);   // Nibble alto
   lcd_enviar_4bits(comando, 0);        // Nibble bajo
   delay_ms(2);
}

// Envía una letra o símbolo (RS=1)
void lcd_texto(char letra) {
   lcd_enviar_4bits(letra >> 4, 1);
   lcd_enviar_4bits(letra, 1);
   delay_us(40);
}

// Inicializa el LCD en modo 4 bits (secuencia según teoría)
void lcd_iniciar(void) {
   delay_ms(15);               // Esperar que el LCD encienda

   // Secuencia de arranque
   lcd_enviar_4bits(0x03, 0);
   delay_ms(5);
   lcd_enviar_4bits(0x03, 0);
   delay_us(100);
   lcd_enviar_4bits(0x03, 0);
   delay_us(100);

   // Cambiar a modo 4 bits
   lcd_enviar_4bits(0x02, 0);
   delay_us(100);

   // Configuración final (según teoría)
   lcd_comando(0x28); // Modo 4 bits, 2 líneas, 5x8
   lcd_comando(0x0C); // Display ON, cursor OFF
   lcd_comando(0x06); // Cursor se mueve a la derecha
   lcd_comando(0x01); // Limpio pantalla
   delay_ms(2);
}


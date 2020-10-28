/*
version con lib u8glib
  16x16Font.ino
  Termometro con IR melexis 5v, y libreria u8glib con pines modificados
 Jesus
 pines Modificados para Oled 5v clock= A3, data= A2
 pines del ir  clock= A5, data= A4
*/
// melexis
#include <Wire.h>
#include <Adafruit_MLX90614.h>
// oled
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
// se modifican los pines clock y data del display oled para evitar interferencias con el sensor de ttura
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ A3, /* data=*/ A2, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
// End of constructor list

Adafruit_MLX90614 mlx = Adafruit_MLX90614( );
int Estadoled = 1;
int debugg= 0;    
void setup(void)
{
   // para activar salida monitor serie
 // debugg= 1; 
 //
   pinMode(LED_BUILTIN, OUTPUT);
   if (debugg==1){
      Serial.begin(9600);
      Serial.println("Adafruit MLX90614 test");  
   }
  mlx.begin();  
  u8x8.begin();
 
}

void loop(void)
{
  // u8x8.setFont(u8x8_font_px437wyse700b_2x2_r);
 // fuente poco clara se cambia por esta:
  u8x8.setFont(u8x8_font_px437wyse700a_2x2_r);
  String stringAmb =  String(mlx.readAmbientTempC(), 1);   
  String stringObj =  String(mlx.readObjectTempC(), 1); 
 //u8x8.drawString(0, 0, "ABC defg");
 
 u8x8.drawString(0, 0, "Tempe *C");
  u8x8.drawString(0, 3, "Am:");
  u8x8.setCursor(6, 3);
  u8x8.print(stringAmb);
  // 
   u8x8.drawString(0, 5, "Ob:");
   u8x8.setCursor(6, 5);
  u8x8.print(stringObj);
  // salida serial para depuración en pantalla del ide arduino
  if (debugg==1){
    Serial.print("Ambient = "); Serial.print(stringAmb); 
    Serial.print("*C\tObject = "); Serial.print(stringObj); Serial.println("*C");
    Serial.println();
  }
  u8x8.refreshDisplay();		// only required for SSD1606/7  
  
   digitalWrite(LED_BUILTIN, Estadoled);
   if (Estadoled==1){
       Estadoled=0;
    } else{
      Estadoled=1;
    }
  delay(1000);
}

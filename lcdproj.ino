#include <LiquidCrystal.h>  
#include "HX711.h"

#define LOADCELL_DOUT_PIN  10
#define LOADCELL_SCK_PIN  8
int Contrast=50;

HX711 scale;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   

float calibration_factor = 86400; //36300 / 86400

void setup() { 
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();  //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(F("Peso:"));
}
char line1[16], float_str[8];
float valor;
void loop(){  
  lcd.clear();
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  
  lcd.setCursor(0, 0);
  lcd.print(F("Peso:"));
  //delay(500);
  //lcd.setCursor(0, 1);
  if(scale.get_units()>1){
      valor = scale.get_units();
      dtostrf(valor,4,2,float_str);
      lcd.print(float_str);
      lcd.print(" kg");
  Serial.print(scale.get_units(), 2); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  } else {
      valor = scale.get_units()*1000 > 0 ? scale.get_units()*1000 : 0;
      dtostrf(valor,4,2,float_str);
      lcd.print(float_str);
      lcd.print(" g");
  Serial.print(scale.get_units()*1000, 0); //scale.get_units() returns a float
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  }
  delay(500);
}

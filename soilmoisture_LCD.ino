#include <SoftwareSerial.h>
// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup(){
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Soil Moisture");
  lcd.setCursor(0,1);
  lcd.print("starting up");
  delay(7000);
  lcd.setCursor(0,0);
  
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  
}

//declare variables with appropriate precision
int value2;
float VWC1;
double soil1Voltage;


void loop(){
  senseValues();
  //----------------
  lcd.setCursor(0,0);
  lcd.print("VWC =");
  lcd.setCursor(6,0);
  lcd.print(VWC1,4);
  lcd.setCursor(0,1);
  lcd.print("Volts =");
  lcd.setCursor(8,1);
  lcd.print(soil1Voltage,4);
  delay(5000);
  lcd.setCursor(0,0);
  lcd.print("               ");
  lcd.setCursor(0,1);
  lcd.print("               ");


    // Print some values to the serial monitor
  Serial.print("Soil moisture 1 value is: ");
  Serial.println(VWC1,4);
  Serial.print("Moisture Volts are: ");
  Serial.print(soil1Voltage,4);
  Serial.println("V");
  Serial.print("Analog value is:");
  Serial.println(value2,2);
}


void senseValues(){                       
  digitalWrite(A3, HIGH);
  delay(500);
  value2 = analogRead(A1);                      //VH400 soil sensor 1
  digitalWrite(A3, LOW);
  delay(500);

    // Calculate Volumetric Water Content based on calibration and piecewise linear equation
    
   soil1Voltage = value2*(5.0/1023.0);  //Convert to voltage with 5V input
    
    if(soil1Voltage <= 1.1) {
      VWC1 = 10*soil1Voltage-1;
    } else if(soil1Voltage > 1.1 && soil1Voltage <= 1.3) {
      VWC1 = 25*soil1Voltage-17.5;
    } else if(soil1Voltage > 1.3 && soil1Voltage <= 1.82) {
      VWC1 = 48.08*soil1Voltage-47.5;
    } else if(soil1Voltage > 1.82) {
      VWC1 = 26.32*soil1Voltage-7.89;
    }

}




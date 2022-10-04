// ****************************************************************** 
/// I, George Mathioudakis,  001211882, certify that this material is my original work. No other person's work has been used without due acknowledgment and I have not made my work available to anyone else.
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
 
DeviceAddress address;

bool connected = true;
bool Shown = true;

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 
} 
 
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
  // checks if Temperature Sensor is connected
if(DS18B20.getAddress(address, 0)){
    // used to print message once
  if(Shown == true){

    String  deviceAddress;

    // build  sensor address
  for(byte a  : address){
    deviceAddress += String(a,HEX);

  }
  Serial.println("\n\nTemperature Application");
  Serial.println("Found DS18B20 sensor with address: "+deviceAddress);
  // prevents from enter if stament again
  Shown = false;
  }
  

  String info;
  connected = "True";
  // check temperature description
  if(fTemp < 10  ){
    info = "Cold!";
  }else if (fTemp >= 10 && fTemp <=15 )
  {
    info = "cool!";
  }else if(fTemp > 15 && fTemp <=25){
    info = "Perfect!";
  }else if(fTemp > 25 && fTemp <=30){
    info = "Warm!";
  }else if(fTemp > 30 && fTemp <=35){
    info = "Hot!";
  }else{
    info = "Too Hot!";
  }
 
  // print the temp and description to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + info); 
 
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
  }else{
  
  // print out if  there is no Sensor
  if(connected == true )
  Serial.println(" no DS18B20  temperature sensors are installed!");
  connected = false;
  }



} 
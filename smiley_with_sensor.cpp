#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128 // OLED display width, in pixels
#define HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

void baseFace() // Makes the head and the eyes
{
    display.clearDisplay();
    display.drawCircle(64, 32, 30, WHITE);
    display.fillCircle(50, 25, 10, WHITE);
    display.fillCircle(78, 25, 10, WHITE);
}

void setup()
{
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  delay(2000);
  display.clearDisplay();
}


void loop() {
  int moisture = analogRead(0);  // gets sensor data
  delay(100);


  double const startval = 0;  // used for parameterizing the smile
  double const endval = 3.1415; // used for parameterizing the smile
  int const rad = 15; // used for parameterizing the smile
  
  int const cricitalval = 300; // This val has to be recalibrated

  if (moisture < cricitalval) // used to cheek if sensor is wet
  {
    baseFace();
    for(double i = startval; i < endval;i += 0.05)
    {
      display.drawPixel(64 + cos(i)*rad, 40 + sin(i)*rad, WHITE); // parameterization of the smile 
    }
    
  }
  else
  {
    baseFace();
    for(double i = endval; i < 2*endval;i += 0.05)
    {
      display.drawPixel(64 + cos(i)*0.8*rad, 50 + sin(i)*0.8*rad, WHITE); // parameterization of the frown 
    }
  }
  
  display.display(); // sends info to screen
  
}

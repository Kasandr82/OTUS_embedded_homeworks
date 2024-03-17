#include <Math.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels (ширина OLED дисплея)
#define SCREEN_HEIGHT 64 // OLED display height, in pixels (высота OLED дисплея)
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define TRIGGER_PIN 14
#define ECHO_PIN 27
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 100
#define LED_RED 26
#define LED_YELLOW 25
#define LED_GREEN 33

int rect_height = 1;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void loop() {
  display.clearDisplay();
  display.fillRect(0, 0, 128, rect_height, WHITE);
  display.display();
  rect_height = sonar.ping_cm();
  switch((int) round(rect_height/30)){
    case 0:
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_GREEN, LOW);
      break;
    case 1:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_GREEN, LOW);
      break;
    default:
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_GREEN, HIGH);
      break;
  }
  Serial.print("Distance = ");
  Serial.print(rect_height);
  Serial.print(" cm ");
  Serial.println(round(rect_height/30));
}
#include <Math.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#define SCREEN_WIDTH 128  // ширина OLED-экрана
#define SCREEN_HEIGHT 64  // высота OLED-экрана
#define OLED_RESET -1
#define TRIGGER_PIN 14    // T-пин датчика
#define ECHO_PIN 27       // R-пин датчика
#define MAX_DISTANCE 100  // ограничил измерение до 1 метра
#define LED_RED 26        // красный светодиод
#define LED_YELLOW 25     // желтый светодиод
#define LED_GREEN 33      // зелёный светодиод

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
  rect_height = sonar.ping_cm();        // чтение данных с датчика расстояния в переменную
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  if (rect_height == 0) {
  } else if (rect_height < 10) {
    digitalWrite(LED_RED, HIGH);
  } else if (rect_height < 30) {
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
  }
  delay(50);                            // даём небольшую задержку
  Serial.print("Расстояние = ");
  Serial.print(rect_height);
  Serial.println(" см");
}
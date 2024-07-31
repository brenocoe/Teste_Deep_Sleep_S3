#include <Arduino.h>
#include "TFT_eSPI.h"

#define PIN_LCD_BL GPIO_NUM_38          // Pino de luz de fundo do display
#define ADC_EN GPIO_NUM_15              // ADC_EN is the ADC detection enable port
#define ADC_PIN GPIO_NUM_4              // Define o pino onde o sensor de bateria está conectado
#define PinoBotaoSuperior GPIO_NUM_0    // pino botao superior
#define PinoBotaoInferior GPIO_NUM_14   // pino botao inferior

TFT_eSPI tft;

void setup()
{
  // habilita a porta de deteccao do ADC interno
  // se a porta USB for usada para alimentacao, esse pino fica ON por padrao
  // se for alimentado por bateria, é necessario por a porta em nivel alto
  pinMode(ADC_EN, OUTPUT);
  digitalWrite(ADC_EN, HIGH);

  // ajuste da luz de fundo do display
  ledcSetup(0, 2000, 8);
  ledcAttachPin(PIN_LCD_BL, 0);
  ledcWrite(0, 255); // 0 a 255 regulagem do display backlight

  // configura esp para ser acordado por um dos botoes
  //esp_sleep_enable_ext1_wakeup(PinoBotaoSuperior | PinoBotaoInferior, ESP_EXT1_WAKEUP_ALL_LOW);
  esp_sleep_enable_ext0_wakeup(PinoBotaoSuperior, HIGH);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 50);
  tft.println("Ola, mundo!");
  delay(5000);

  // poe esp em modo de hibernacao
  esp_deep_sleep_start();
}

void loop()
{
}

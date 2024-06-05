#include <Servo.h>                      // Inclui a biblioteca Servo.h para controlar o servo motor
#include <LiquidCrystal_I2C.h>          // Inclui a biblioteca LiquidCrystal_I2C.h para controlar o display LCD

#define SERVO 11                        // Define o pino onde o servo motor está conectado

Servo s;                                // Cria um objeto servo
int pos;                                // Variável para armazenar a posição do servo motor

// Pinos para controle do sensor de nível de líquido, do LED e do servo motor
const int sensorPin = A0;               // Pino analógico para o sensor de nível de líquido
const int ledPin = 13;                  // Pino para o LED

LiquidCrystal_I2C lcd(0x27, 16, 2);     // Cria um objeto para o display LCD

// Variáveis para armazenar o valor lido pelo sensor
int sensorValue = 0;

// Limiar para acionamento do LED (simulando vazamento)
const int threshold = 700;

void setup() {
  s.attach(SERVO);                      // Inicializa o servo motor no pino definido
  pinMode(ledPin, OUTPUT);              // Configura o pino do LED como saída
  Serial.begin(9600);                   // Inicializa a comunicação serial
  s.write(0);                           // Define a posição inicial do servo motor como 0 graus
  lcd.init();                           // Inicializa o display LCD
  lcd.backlight();                      // Liga o backlight do display LCD
  lcd.setCursor(5,0);                   // Define a posição do cursor para escrever no display
  lcd.print("Clean");                   // Escreve "Clean" na primeira linha do display
  lcd.setCursor(5,1);                   // Define a posição do cursor para escrever no display
  lcd.print("Ocean");                   // Escreve "Ocean" na segunda linha do display
  delay(2000);                          // Aguarda 2 segundos
  lcd.clear();                          // Limpa o display LCD
}

void loop() {
  sensorValue = analogRead(sensorPin); // Lê o valor do sensor de nível de líquido
  Serial.println(sensorValue);         // Imprime o valor lido no monitor serial

  if (sensorValue > threshold) {       // Verifica se o valor lido ultrapassa o limiar
    digitalWrite(ledPin, HIGH);        // Acende o LED para simular o vazamento
    s.write(180);                      // Move o servo motor para a posição de fechamento (180 graus)
    lcd.clear();                       // Limpa o display LCD
    lcd.setCursor(3,0);                // Define a posição do cursor para escrever no display
    lcd.print("Vazamento");            // Escreve "Vazamento" na primeira linha do display
    lcd.setCursor(3,1);                // Define a posição do cursor para escrever no display
    lcd.print("Detectado!");           // Escreve "Detectado!" na segunda linha do display
    delay(2000);                       // Aguarda 2 segundos
    lcd.clear();                       // Limpa o display LCD
    lcd.setCursor(3,0);                // Define a posição do cursor para escrever no display
    lcd.print("Comportas");            // Escreve "Comportas" na primeira linha do display
    lcd.setCursor(3,1);                // Define a posição do cursor para escrever no display
    lcd.print("Fechadas!");            // Escreve "Fechadas!" na segunda linha do display
    delay(3000);                       // Aguarda 3 segundos
  } else {
    digitalWrite(ledPin, LOW);         // Desliga o LED
    s.write(0);                         // Mantém o servo motor na posição de abertura (0 graus)
    lcd.clear();                        // Limpa o display LCD
    lcd.setCursor(5,0);                 // Define a posição do cursor para escrever no display
    lcd.print("Sem");                   // Escreve "Sem" na primeira linha do display
    lcd.setCursor(3,1);                 // Define a posição do cursor para escrever no display
    lcd.print("Vazamento");             // Escreve "Vazamento" na segunda linha do display
    delay(2000);                        // Aguarda 2 segundos
  }
  
  delay(100);                           // Aguarda um pequeno intervalo antes de realizar a próxima leitura
}



//******Bibliotecas*******/
#include <Arduino.h>
#include <Servo.h>
#include <U8g2lib.h>
#include <DHT.h>


//******Definições*******/

#define pinSensorDeChuva 15

#define DHTTYPE DHT22

#define DHTPIN 4



//******Instancias e Constancias*******/
const int pinServo2 = 2;

int leituraAnalogica = 0;

int pinSensorUmidade = 34;

int sensorUmidade;
// 4095

int posicao = 0;



//******Objetos*******/

Servo servoMotor = Servo();


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

DHT dht(DHTPIN, DHTTYPE);


//*******Prototipos********/
unsigned long lerRFID(void);

float SensordeChuva = 0;

float umservo = 0;

float doiservo = 0;

void umidadeSolo(void);

float lerTemperatura(void);

float lerUmidade(void);

void SensChuva(void);



//******Variaveis booleanas*******/

//******Configuração*******/
void setup()
{
  u8g2.begin();
  Serial.begin(9600);
  pinMode(pinSensorUmidade, INPUT);
  dht.begin();
  Serial.begin(9600); // Iniciar comunicação serial
}

void loop()
{
  leituraAnalogica = analogRead(pinSensorUmidade);

  sensorUmidade = map(leituraAnalogica, 0, 4095, 100, 0);
  delay(100);
  umidadeSolo();
  SensChuva();
}
float lerTemperatura()
{
  float t = dht.readTemperature();
  return t;
}

float lerUmidade()
{
  float u = dht.readHumidity();
  return u;
}

void umidadeSolo()
{
  u8g2.clearBuffer();
  u8g2.drawRFrame(2, 3, 123, 60, 4);  // retangulo com as bordas arredondadas
  u8g2.setFont(u8g2_font_lubBI10_te); // muda para a fonte de texto
  u8g2.drawStr(10, 23, "Umi.Solo:");
  u8g2.drawStr(80, 23, String(sensorUmidade).c_str()); // escreve a umidade do solo
  u8g2.drawStr(100, 23, "%");
  if (sensorUmidade < 2000)
  {
  }
  else
  {
  }

  u8g2.drawStr(10, 52, "Temp:");
  u8g2.drawStr(60, 52, String(lerTemperatura(), 0).c_str()); // escreve a temperatura do ambiente
  u8g2.drawStr(80, 52, "*C");
  u8g2.sendBuffer();
  Serial.println(lerTemperatura());
}
void SensChuva()
{
  SensordeChuva = analogRead(pinSensorDeChuva);

  if (SensordeChuva > 2000)
  {
    umservo = servoMotor.write(pinServo2, 0);
    SensordeChuva = analogRead(pinSensorDeChuva);
  }
  else
  {
    umservo = servoMotor.write(pinServo2, 180);
    SensordeChuva = analogRead(pinSensorDeChuva);
  }
}

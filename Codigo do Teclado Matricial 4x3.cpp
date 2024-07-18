#include <Arduino.h>
#include <Keypad.h>
#include <Servo.h>




void trancada();
void destrancada();


const int pinServo = 2;


Servo servoMotor = Servo();



float doisservo = 0;


float umservo = 0;

// C++ code
//
const byte rowsCount = 4;
const byte columsCount = 3;

char keys[rowsCount][columsCount] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

const char password[] = "40028922";
/* Quantidade de caracteres que a senha possui */
const int caracteres = 8;

int posicao = 0;

//
byte columnPins[columsCount] = {27, 13, 4}; // pino1, pino2, pino3
byte rowPins[rowsCount] = {33, 25, 26, 14}; // pino4, pino5, pino6, pino7

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
void setup()
{

  Serial.begin(9600);
  trancada();
}

void loop()
{

  /* Captura a tecla pressionada */
  char key = keypad.getKey();

  /* Se uma tecla for pressionada */
  if (key)
  {
    Serial.println(key);

    /* Se a tecla pressionada for “*” ou “#”, tranca a fechadura */
    if (key == '*' || key == '#')
    {
      trancada();
    }
    else
    {
      /* Se as teclas pressionadas coincidirem com a senha, incrementa a posição */
      if (key == password[posicao])
      {
        posicao++;
      }
      else
      {
        posicao = 0; // Reinicia a posição se a tecla não coincidir
      }

      /* Se a posição atingir o tamanho da senha, destranque a fechadura */
      if (posicao == caracteres)
      {
        destrancada();
      }
    }
  }

  /* Pequena pausa para retomar a leitura */
  delay(100);
}

/* Função que mantém a fechadura trancada */
void trancada()
{
  /* Servo na posição trancada */
  doisservo = servoMotor.write(pinServo, 0);
  /* Imprime no monitor serial que a fechadura está TRANCADA */
  Serial.println("TRANCADA");

  /* Reinicia a posição para nova tentativa */
  posicao = 0;

  
}

/* Função que mantém a fechadura destrancada */
void destrancada()
{
  /* Servo na posição destrancada */
  doisservo = servoMotor.write(pinServo, 180);
  /* Imprime no monitor serial que a fechadura está ABERTA */
  Serial.println("ABERTA");
  
}

#include <M5Stack.h>

#define PinEntrada 35
#define RL_VALOR (5)//define el valor de la resistencia mde carga en kilo ohms
#define RAL (9.83)  // resistencia del sensor en el aire limpio / RO, que se deriva de la tabla de la hoja de datos
#define GAS_LP (0)
String inputstring = ""; //Cadena recibida desde el PC
float LPCurve[3] = {2.3, 0.21, -0.47};
float Ro = 10;
float k = 2.03 / 2330;
float valores[200];
float muestraVoltios;
int j = 0;
float minimo = 100;
float maximo = 0;
float mitja = 0;
// Ajustar estos valores para vuestro sensor según el Datasheet
// (opcionalmente, según la calibración que hayáis realizado)
const float X0 = 200;
const float Y0 = 1.7;
const float X1 = 10000;
const float Y1 = 0.28;

// Puntos de la curva de concentración {X, Y}
const float punto0[] = { log10(X0), log10(Y0) };
const float punto1[] = { log10(X1), log10(Y1) };
 
// Calcular pendiente y coordenada abscisas
const float scope = (punto1[1] - punto0[1]) / (punto1[0] - punto0[0]);
const float coord = punto0[1] - punto0[0] * scope;

void setup() {

  M5.begin();
  Serial.begin(115200);
  pinMode(PinEntrada, INPUT);
  M5.Lcd.setTextSize(3);
  Serial.println("Iniciando ...");
  //configuracion del sensor
  Serial.print("Calibrando...\n");
  Ro = Calibracion(PinEntrada);//Calibrando el sensor. Por favor de asegurarse que el sensor se encuentre en una zona de aire limpio mientras se calibra
  Serial.print("Calibracion finalizada...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print(" kohm");
  Serial.print("\n");



}

void loop() {
  // put your main code here, to run repeatedly:
  float rs_med = mitja;      // Obtener la Rs promedio
  float concentration = getConcentration(rs_med / Ro);


  muestraVoltios = k * analogRead(PinEntrada);

  valores[j] = muestraVoltios;
  if (Serial.read() == 'a') {

    for (int i = 0; i < 200; i++) {
      Serial.println(valores[i]);
    }
  }
  minimo = 100;
   maximo = 0;
  for (int i = 0; i < 200; i++) { 
    if (valores[i] <= minimo) {
    minimo = valores[i];
  }
  if (valores[i] >= maximo) {
    maximo = valores[i];
  }
    mitja += valores[i];
  }
  mitja /= 200;
  if (j == 99) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Mitja: ");
    M5.Lcd.println(mitja);
    M5.Lcd.print("Maxim: ");
    M5.Lcd.println(maximo);
    M5.Lcd.print("Minim: ");
    M5.Lcd.println(minimo);
  }
  j++;
  if (j == 200) {
    j = 0;
  }

  delay(10);
}

float calc_res(int raw_adc)
{
  return ( ((float)RL_VALOR * (1023 - raw_adc) / raw_adc));
}

float Calibracion(float mq_pin) {
  int i;
  float val = 0;
  for (i = 0; i < 50; i++) { //tomar múltiples muestras
    val += calc_res(analogRead(mq_pin));
    delay(500);
  }
  val = val / 50; //calcular el valor medio
  val = val / RAL;
  return val;
}
float getConcentration(float rs_ro_ratio)
{
   return pow(10, coord + scope * log(rs_ro_ratio));
}

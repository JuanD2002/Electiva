#include "math.h"

int entrada1 = 8;
int entrada2 = 9;
int entrada3 = 10;
int entrada4 = 11;

volatile int cont = 0;
volatile int cont1 = 0;
int pulsos = 0;
//#define   T_SAMPLING  100   /* tiempo de proceso */
#define   NPULSES        20 /* Pulsos que genera el encoder */
unsigned long currentMillis;
unsigned long prevMillis;

/*uint8_t trajectory = LADO1;
uint8_t flag1 = 0;

/************************** Odometry variables  ******************************/
float x   = 0; /* x meters */
float y   = 0; /* y meters */
float phi = 0; /* angle radians */

float xi  = 0; /* x centimeters */
float yi  = 0; /* y centimeters */
float pg  = 0; /* angle degrees */

float R = 0.0032;       /* 5 cm = Wheel radious */
float L   = 0.17;    /* 38.8 cm = Distance betwen wheels */
float dR  = 0;        /* Right wheel displacement */  
float dL  = 0;        /* Left wheel displacement */
int  u16gTicksA = 0;  /* Actual tick counter Right Wheel */
int  u16gTicksAi = 0; /* Previous tick counter Right Wheel */
int  u16gTicksB = 0;  /* Actual tick counter Left Wheel */
int  u16gTicksBi = 0; /* Previous tick counter Left Wheel */

void odometry (void);

void odometry (void){
  dR = 2*PI*(u16gTicksA - u16gTicksAi)R/NPULSES; 
  u16gTicksAi = u16gTicksA;                       /* Ticks counter previous value update */ 
  
  dL = 2*PI*(u16gTicksB - u16gTicksBi)R/NPULSES;
  u16gTicksBi =u16gTicksB;                        /* Ticks counter previous value update */
 
  x = x + cos(phi)(dR + dL)/2;
  y = y + sin(phi)(dR + dL)/2; 
  
  phi = phi + (dR-dL)/L;    /* Calculates angle in rads */

  /* Convert units to m and angle to degrees */
  xi = x * 100;
  yi = y * 100;
  pg = phi*180/3.14159;
  
  if (pg > 360){ pg = pg -360;}
}

void setup() {
  // put your setup code here, to run once:

    delay(10000);
    pinMode(3, INPUT);
    pinMode(2, INPUT);
    pinMode(entrada1, OUTPUT);
    pinMode(entrada2, OUTPUT);
    pinMode(entrada3, OUTPUT);
    pinMode(entrada4, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), interrupcao2, CHANGE); // Usamos CHANGE para detectar ambos flancos
    attachInterrupt(digitalPinToInterrupt(3), interrupcao1, CHANGE); // Usamos CHANGE para detectar ambos flancos
    Serial.begin(9600);
    Serial.println(" - Inicio - ");
    adelante();
}

void loop() {

  detachInterrupt(digitalPinToInterrupt(3));
  u16gTicksA = cont1;
  Serial.println(u16gTicksA);
  attachInterrupt(digitalPinToInterrupt(3), interrupcao1, CHANGE);

  detachInterrupt(digitalPinToInterrupt(2));
  u16gTicksB = cont;
  Serial.println(u16gTicksB);
  attachInterrupt(digitalPinToInterrupt(2), interrupcao2, CHANGE);
  odometry(); 
  
  Serial.println(String(xi)+";"+ String(yi)+";"+String(pg));
  delay(100);
  if (u16gTicksA>300)
  {
    detener();
  }
    
}

void interrupcao1() {
  cont++;
}
void interrupcao2() {
  cont1++;
}


void detener() {
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, LOW);
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, LOW);
}

void adelante() {
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, HIGH);
  digitalWrite(entrada3, HIGH);
  digitalWrite(entrada4, LOW);
}


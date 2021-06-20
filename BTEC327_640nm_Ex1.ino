#define lsr 2
#define ptr A6

float amb;  //ambient light reading
float I0; //incident light
float I;  //recieved light
float A;  //Absorbance
float c1 = 125;  //concentration g/l
float c2;  //concentration g/l
float L = 8.8;  //length (cm)
float e;  //molar absorbtion coefficient

int comm = 0;

void calc(){
  Serial.println("Calculating...");
  A = log10(I0 / I);
  Serial.println("Absorbance is: ");
  Serial.println(A);
  delay(500);
  //e = A / (L*c1);
  c2 = A / (L*e);
  Serial.println("Concentration is: ");
  Serial.print(c2);
  return;
}


void ext(){
  Serial.println("Calculating...");
  A = log10(I0 / I);
  Serial.println("Absorbance is: ");
  Serial.println(A);
  delay(500);
  e = A / (L*c1);
  //c = A / (L*e);
  Serial.println("Concentration is: ");
  Serial.print(e);
  return;
}

void acquire(){
  Serial.println("Acquiring...");
  digitalWrite(lsr, HIGH);
  I = analogRead(ptr) - amb;
  delay(1000);
  Serial.println("Acquire Done");
  digitalWrite(lsr, LOW);
  //calc();
}

void initialize(){
  Serial.println("Initializing...");
  amb = analogRead(ptr);
  Serial.println(amb);
  delay(1000);
  digitalWrite(lsr, HIGH);
  delay(1000);
  I0 = analogRead(ptr) - amb;
  Serial.println(I0);
  delay(1000);
  digitalWrite(lsr, LOW);
  Serial.println("Initialization Done!");
  return;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ptr, INPUT);
  pinMode(lsr, OUTPUT);
  Serial.begin(9600);
  Serial.print("BTEC327_Exp1!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    comm = Serial.read();
  

  switch(comm){
    case '1':
      initialize();
    break;

    case '2':
      acquire();
    break;
    
    case '3':
      calc();
    break;

    case '4':
      ext();
    break;
  }
  }
}

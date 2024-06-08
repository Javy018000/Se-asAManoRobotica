#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Si los siguientes paréntesis, están vacios, 
// se usará la dirección                   por default 0X40.
Adafruit_PWMServoDriver brazo = Adafruit_PWMServoDriver();
// Puedes tambien nombrarla con una dirección diferente.
// Adafruit_PWMServoDriver brazo = Adafruit_PWMServoDriver(0x41);

// Dependiendo de la marca de tus servos, pueden variar el pulso mínimo y máximo.
// Consulta sus especificaciones.

#define SERVOMIN  125 // Pulso mínimo (fuera de 4096)
#define SERVOMAX  575 // Pulso máximo (fuera de 4096)

// Primer servo # de contador
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
    Serial.println("  Prueba de 6 servos para brazo robótico: ");
    Serial.println("  ");
  brazo.begin();
  
  brazo.setPWMFreq(60);  // Servos analógicos funcionan a ~60 Hz actualizado.

  yield(); 

  
}
// Inicia el ciclo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void loop() {

  


  if (Serial.available() > 0) {
    char receivedChar = (char)Serial.read(); // Lee el carácter recibido
    if (receivedChar == 'A') { // Compara el carácter recibido con 'A'
      letras(0, 0, 0, 0, 100, 180);
    } else if (receivedChar == 'B') { // Compara el carácter recibido con 'B'
        letras(180, 180, 180, 180, 160, 60);
    } else if (receivedChar == 'C') { // .....
        letras(70, 70, 70, 70, 70, 30);
    } else if (receivedChar == 'U') {
        letras(180, 0, 0, 180, 70, 30);
    } else if (receivedChar == 'I') { 
        letras(0, 0, 0, 180, 70, 2);
    } else if (receivedChar == 'D') {
        letras(180, 0, 0, 0, 70, 2);
    } else if (receivedChar == 'F') {
        letras(0, 180, 180, 180, 70, 60);
    } else if (receivedChar == 'L') { 
        letras(180, 0, 0, 0, 180,180 );
    } else if (receivedChar == 'O') { 
        letras(70, 70, 70, 70, 70, 30);
    } else if (receivedChar == 'V') { 
        letras(180, 180, 0, 0, 70, 30);
    } else if (receivedChar == 'W') { 
        letras(180, 180, 180, 0, 70, 30);
    } else if (receivedChar == 'X') { 
        letras(180, 180, 0, 0, 0, 90);
    } else if (receivedChar == 'M') { 
      letras(0, 0, 0, 0, 100, 180);
    } 
  }

 
}
// Termina el ciclo >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
 Convierte los pulsos a grados sexagesimales.
*/
int anguloApulsar(int ang){
   // Regla de tres para convertir pulsos a grados (0 a 180). 
   int pulso = map(ang,0, 180, SERVOMIN,SERVOMAX); 
   Serial.print("     ");
   Serial.print(ang);
   Serial.print("        ");
   Serial.println(pulso);
   
   return pulso;
}



void letras (int indiceAng, int corazonAng, int anularAng, int meniqueAng, int centralAng, int pulgarAng){
  //---------------------*****devueltaa******-----------------------
 
  Serial.println("   ***  Pulgar devuelta  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =180; angulo>pulgarAng; angulo -=2){
     brazo.setPWM(4, 0, anguloApulsar(angulo) );
     delay(10); 
  }
  Serial.println("  ");

  //------------------------------------------------ 
  Serial.println("   *** Central devuelta *** ");
  Serial.println("    Angulo     Pulso "); 
  for( int angulo =180; angulo>centralAng; angulo -=2){
     brazo.setPWM(5, 0, anguloApulsar(angulo) );
     delay(10); 
  }
  Serial.println("  ");
   //------------------------------------------------  
  Serial.println("  ***  indice devuelta  *** ");
  Serial.println("    Angulo     Pulso ");
  // Regreso "Suavizado"
  for( int angulo = 180; angulo>indiceAng; angulo -=2){
    brazo.setPWM(0, 0, anguloApulsar(angulo) );
    delay(25); 
  }
  Serial.println("  ");

    //------------------------------------------------  

  Serial.println("   ***  Corazon devuelta  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =180; angulo>corazonAng; angulo -=2){
    brazo.setPWM(1, 0, anguloApulsar(angulo) );
    delay(10); 
  }
  Serial.println("  ");

  //------------------------------------------------  

  Serial.println("  ***  Anular devuelta  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =180; angulo>anularAng; angulo -=2){
    brazo.setPWM(2, 0, anguloApulsar(angulo) );
    delay(10); 
  }
  Serial.println("  ");

  //------------------------------------------------  

  Serial.println("   ***  Meñique devuelta  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =180; angulo>meniqueAng; angulo -=2){
     brazo.setPWM(3, 0, anguloApulsar(angulo) );
     delay(10); 
  }
  Serial.println("  ");


  delay(5000);

  //------------------idaaaa------------------------------
  
 Serial.println("   ***  Central ida  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =0; angulo<180; angulo +=2){
     brazo.setPWM(5, 0, anguloApulsar(angulo) );
     delay(10);
  }
  
  Serial.println("  ");
  

  
  //------------------------------------------------ 

  Serial.println("  ***  indice ida  *** ");
  Serial.println("    Angulo     Pulso ");
  // Ida "Intermitente"
  for( int angulo =indiceAng; angulo<180; angulo +=2){ 
    brazo.setPWM(0, 0, anguloApulsar(angulo) );
    delay(10);
  }
  
  Serial.println("  ");

 
  
  //------------------------------------------------  
  Serial.println("   ***  Corazon ida  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =corazonAng; angulo<180; angulo +=2){
    brazo.setPWM(1, 0, anguloApulsar(angulo) );
    delay(10);
  }
  
  Serial.println("  ");
  
//------------------------------------------------ 
Serial.println("  ***  Anular ida  *** ");
  Serial.println("    Angulo     Pulso ");
  
  for(int angulo =anularAng; angulo<180; angulo +=2){
    brazo.setPWM(2, 0, anguloApulsar(angulo) );
    delay(10);
  }
    
  Serial.println("  ");
 
//------------------------------------------------  
  Serial.println("   ***  Meñique ida  *** ");
  Serial.println("    Angulo     Pulso ");
  for( int angulo =meniqueAng; angulo<180; angulo +=2){
     brazo.setPWM(3, 0, anguloApulsar(angulo) );
     delay(10);
  }
  
  Serial.println("  ");

  //------------------------------------------------  

 Serial.println("   *** pulgar ida *** ");
  Serial.println("    Angulo     Pulso ");
  

  for( int angulo = pulgarAng; angulo>0; angulo -=2){
    brazo.setPWM(4, 0, anguloApulsar(angulo) );
    delay(10);
  }
  
  Serial.println("  ");
  
}



//void pocisionInicial(){
//  //------------------idaaaa------------------------------
//  Serial.println("  ***  indice ida  *** ");
//  Serial.println("    Angulo     Pulso ");
//  // Ida "Intermitente"
//  for( int angulo =0; angulo<180; angulo +=2){ 
//    brazo.setPWM(0, 0, anguloApulsar(angulo) );
//    delay(10);
//  }
//  
//  Serial.println("  ");
//
// 
//  
//  //------------------------------------------------  
//  Serial.println("   ***  Corazon ida  *** ");
//  Serial.println("    Angulo     Pulso ");
//  for( int angulo =0; angulo<180; angulo +=2){
//    brazo.setPWM(1, 0, anguloApulsar(angulo) );
//    delay(10);
//  }
//  
//  Serial.println("  ");
//  
////------------------------------------------------ 
//Serial.println("  ***  Anular ida  *** ");
//  Serial.println("    Angulo     Pulso ");
//  
//  for(int angulo =0; angulo<180; angulo +=2){
//    brazo.setPWM(2, 0, anguloApulsar(angulo) );
//    delay(10);
//  }
//    
//  Serial.println("  ");
// 
////------------------------------------------------  
//  Serial.println("   ***  Meñique ida  *** ");
//  Serial.println("    Angulo     Pulso ");
//  for( int angulo =0; angulo<180; angulo +=2){
//     brazo.setPWM(3, 0, anguloApulsar(angulo) );
//     delay(10);
//  }
//  
//  Serial.println("  ");
// 
////------------------------------------------------ 
// Serial.println("   ***  Central ida  *** ");
//  Serial.println("    Angulo     Pulso ");
//  for( int angulo =0; angulo<20; angulo +=2){
//     brazo.setPWM(5, 0, anguloApulsar(angulo) );
//     delay(10);
//  }
//  
//  Serial.println("  ");
//  
////------------------------------------------------  
//
// Serial.println("   *** pulgar ida *** ");
//  Serial.println("    Angulo     Pulso ");
//  
//
//  for( int angulo =0; angulo<20; angulo +=2){
//    brazo.setPWM(4, 0, anguloApulsar(angulo) );
//    delay(10);
//  }
//  
//  Serial.println("  ");
//}

// Project by Till_Meiners and Daniel_Kazimierczuk
//       ---  github.com/daniel-k-05  ---


//   Da es nicht möglich ist Diesen code ohne 
//   funktionierendes Board zu nutzen, Schließen
//   Sie einen Arduino Nano oder UNO an und laden
//   den Sketch herunter.
//   Öffnen sie nun Den Seriellen Monitor.

//   Der jetztige Code ist ohne große Probleme auf 8 LED's erweiterbar

   
//Deklarierung der Pins, welche zum ShiftRegister führen.
int latchPin = 8;      //ST_CP
int clockPin = 12;     //SH_CP
int dataPin = 11;     //DS


// Deklarierung der des Delays in 100ms schritten zwischen jedem an und ausschalten
// hierbei gilt: ( 10.0 = 1000ms = 10*takt )
// ---Dies ist Bei jetztigem Setup bis zu 8 erweiterbar---
double bps1 =  5.0  ;   //60  Bpm ; alle 0.5 sek an und wieder aus
double bps2 =  2.5  ;   //120 Bpm (Herzschlag eines Menschen) alle 0.25 sekunden an und wieder aus
double bps3 = 42.2  ;   // 7.3 babies per minute (((noch problematisch)))

//(7.3 babies per minute = ~every 8,22 >> 4.22sec del pes on/off >> 


int takt = 1;           //festlegung des zu erhöhenden Taktes
int del  = 100;         //festlegung des Delays pro takt




//berechnung des Delays in Millisekunden
//Bei jetztigem code nicht genutzt
int del1 = float( bps1 );
int del2 = float( bps2 );
int del3 = float( bps3 );


int data;
int PastMilliseconds ;
int PastSeconds ;
int bytes ;

int controldata;


//Troubleshooting and worked on principals
/*int controlbytes ;

int OnTime1;
int On1;
int OnTime2;
int On2;
int OnTime3;
int On3;

*/

void setup() {
  Serial.begin(9600);               // Serial Begin
  //Pins der ShiftRegister
  pinMode(latchPin, OUTPUT);        //Pin Output...
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  PastSeconds = 0;                  // Festsetzung anfänglicher Variabeln
  bytes = 0b10000000;               // 0b"1"000   ist um funktionalität des registers un des codes zu testen


//Troubleshooting and worked on principals  
/*  controlbytes = 0b00001000;

  On1 = 0;
  OnTime1 = 0;
  On2 = 0;
  OnTime2 = 0;
  On3 = 0;
  OnTime3 = 0;
  On4 = 0;
  OnTime4 = 0;
*/
}



void loop() {
  delay(del);      // Delay
  Test();          // Neu veränderter Takt wird nach gewollten Veränderungen getestet 
  data = bytes;    // und die daten für die Ausgabe vorbereitet
   
  Serial.write("Derzeitige Bits: ");               // Zur kontrolle werden die 
  Serial.print(data, BIN);                         // Bits 
  Serial.write("  Past Time: ");                   // und die jetztige (Takt) Zeit ausgegeben
  Serial.println(PastSeconds/ 10);                 // die " /10 " ermöglicht einfacheres lesen im Serial monitor
  
  digitalWrite(latchPin, LOW);                     // Informationen werden an die Shift register
  shiftOut(dataPin, clockPin, MSBFIRST, data);     // weiter gegeben
  digitalWrite(latchPin, HIGH);
  PastSeconds = PastSeconds + takt ;               // Der Takt wird weiter geführt
  

  }


void Test(){
  
  if  (PastSeconds % del1 == 0){       // alle del1(0.5 sekunden) 
  bytes = bytes ^ 0b00000001;          // bytes 0000 nor 0001 >>> 0001
                                       // bytes 0000 nor 0001 >>> 0000
 /* 
  On1 = 1;
  OnTime1 = 1; */
  }
 /* else if (On1 == 1) {
  OnTime1 ++;
  }
  else if (OnTime1 >= 100){
  bytes = bytes ^ 0b00000001;
  On1 = 0;
  OnTime1 = 0;
  }

*/


  if  (PastSeconds % del2 == 0){
  bytes = bytes ^ 0b00000010;
  }
  if  (PastSeconds % del3 == 0){
  bytes = bytes ^ 0b00000100;
  }



  
}

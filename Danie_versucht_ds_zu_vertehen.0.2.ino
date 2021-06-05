int latchPin = 8;                                 
int clockPin = 12;
int dataPin = 11;

byte data;
byte dataArray[10];

void setup() {
  
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);


  //Binary notation as comment                      //dieser bereich müsste aktiv geändert werden, um unabhängige stäuerung der lesd's zu gewährleisten
  dataArray[0] = 0b11111111;
  dataArray[1] = 0b11111110;
  dataArray[2] = 0b11111100;
  dataArray[3] = 0b11111000;
  dataArray[4] = 0b11110000;
  dataArray[5] = 0b11100000;
  dataArray[6] = 0b11000000;
  dataArray[7] = 0b10000000;
  dataArray[8] = 0b00000000;
  dataArray[9] = 0b11100000;

  //function that blinks all the LEDs                  //         l
  blinkAll_2Bytes(2,500);                              //startet  \/
}




                                                           //bringt alle led's kurz zum leuchten (anfang des sketches)
//blinks the whole register based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}








void loop() {

  for (int j = 0; j < 10; j++) {

    data = dataArray[j];                             //dies mit hilfe der berechnung per led verändern
    
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, data);
    digitalWrite(latchPin, 1);
    delay(300);                                       //1 würde den standard takt von 1 millis bedeuten
  }
}



// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else { 
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

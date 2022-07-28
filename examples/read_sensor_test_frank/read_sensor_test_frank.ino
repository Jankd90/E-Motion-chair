void setup() {
  

// pins for power to FSR (MUX)
pinMode(0, OUTPUT);
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);

Serial.begin(115200);

}

void loop() {
  
  int a[9][2] = { {0,3}, 
                  {0,4},
                  {0,5},
                  {1,3},
                  {1,4},
                  {1,5},
                  {2,3},
                  {2,4},
                  {2,5}};
                  
  //Serial.println("newloop");
  for(int s=0; s<9; s++){

    //setting the matrix combination to high and reading it according to array a [9][2]
    digitalWrite(a[s][0], HIGH);
    int x = analogRead(a[s][1]);

    //setting all pins to low
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    
//    Serial.print("sensor value for ");
//    Serial.print(s);
//    Serial.print(" is = ");
//    Serial.println(x);

    Serial.print(x);
    Serial.print(",");
  }
  Serial.println("");
  delay(100);
}

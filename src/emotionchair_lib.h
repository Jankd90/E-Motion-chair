int sensorPin;
int state = 10;
int read_RTC(){
  int result;
  return result;
};
void set_device_state(int input_state){
  state = input_state;
};
int get_device_state(){
  return state;
};
int write_data_to_SD(){
  int result;
  return result;
};
void set_sensor_to_read(int pin){
  sensorPin = (sensorPin + 1) % 10;
  //sensorPin = pin;
};
int read_sensor(int i){
  //some functionality to read from sensorPin
  int a[9][2] = { {1,4}, 
                  {1,5},
                  {1,6},
                  {2,4},
                  {2,5},
                  {2,6},
                  {3,4},
                  {3,5},
                  {3,6}};
                  
  digitalWrite(a[i][0], HIGH);
  int result = analogRead(a[i][1]);

  //setting all digital write pins to low
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  
  return result;
};
void synchronize_clock(){
  
};
void get_network_time(){
};
void set_time(){
};

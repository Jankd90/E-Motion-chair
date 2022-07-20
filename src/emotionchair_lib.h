int state = 0;
int sensorPin;

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
int read_sensor(){
  //some functionality to read from sensorPin
  int result = sensorPin;
  return result;
};
void synchronize_clock(){
  
};
void get_network_time(){
};
void set_time(){
};

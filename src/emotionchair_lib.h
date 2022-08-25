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
void calculateCOG(int v[], int arrSize, int & fX, int & fY){
    int dis[3]= {1,13,25};
    int sumV = 0;
    for (int i = 0; i <arrSize; i++) {
        sumV += v[i];
    }
    fX = (    dis[0]*v[0]+dis[1]*v[1]+dis[2]*v[2]+
              dis[0]*v[3]+dis[1]*v[4]+dis[2]*v[5]+
              dis[0]*v[6]+dis[1]*v[7]+dis[2]*v[8]
             )/sumV;
    fY = (    dis[0]*v[0]+dis[1]*v[3]+dis[2]*v[6]+
              dis[0]*v[1]+dis[1]*v[4]+dis[2]*v[7]+
              dis[0]*v[2]+dis[1]*v[5]+dis[2]*v[8]
             )/sumV;
return;
}

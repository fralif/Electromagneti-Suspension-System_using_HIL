// Create a union to easily convert float to byte
typedef union {
  float number;
  uint8_t bytes[4];
} 

FLOATUNION_t;

float output;
//create variable to send
FLOATUNION_t PIDcontr;
//parameter controller
float Kp = 1;
float Ki = 0.1;
//float Kd = 0.540;
//float Kp = 1;
float Kd = 1;
float Error, dError, sum_Error;
void setup() {
  // initialize serial, use the same boudrate in the Simulink Config block
  Serial.begin(115200);
}
float getFloat() {
  int cont = 0;
  FLOATUNION_t f;
  while (cont < 4) {
    f.bytes[cont] = Serial.read();
    cont = cont + 1;
  }
  return f.number;
}
// PID algorithm
void loop() {
  output = getFloat();
  float Error = output;
  dError = Error;
  sum_Error += Error;
  
  float P = Kp * Error;
  float I = Ki * sum_Error;
  float D = (Kd / 100) * (Error - dError);
  PIDcontr.number = P + I + D;  //PID calculation
  //Send controller algorithm to plant/simulink
  // Print header: Important to avoid sync errors! to make sure
  Serial.write('A');
  // Print float data
  for (int i = 0; i < 4; i++) {
    Serial.write(PIDcontr.bytes[i]);
  }
  // Print terminator
  Serial.print('\n');
  // Use the same delay in the Serial Receive block
  delay(50);
}

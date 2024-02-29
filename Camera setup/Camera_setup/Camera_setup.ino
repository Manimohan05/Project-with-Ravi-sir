#include <Wire.h>
#include <ArduCAM.h>

ArduCAM myCAM( OV7670, 7 ); // Use pin 7 for the XCLK connection

void setup() {
  Serial.begin(115200);

  while (!Serial);

  myCAM.write_reg(ARDUCHIP_GPIO, GPIO_PWDN_MASK); // Power down the camera
  delay(1000);

  myCAM.write_reg(ARDUCHIP_GPIO, GPIO_RESET_MASK); // Reset the camera
  delay(1000);

  myCAM.write_reg(ARDUCHIP_GPIO, 0); // Release the camera from power down mode
  delay(1000);

  Serial.println("OV7670 Camera Initialization Successful!");
}

void loop() {
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  
  myCAM.start_capture();
  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));

  Serial.println("Capture Done");
}

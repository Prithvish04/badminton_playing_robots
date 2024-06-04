#include <NewPing.h>
//Receiver LEFT Transmitter RIGHT
#define TRIG_1  22
#define TRIG_2 23// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_1 11
#define ECHO_2 10// Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIG_1, ECHO_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIG_2, ECHO_2, MAX_DISTANCE);
void setup() 
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS1 = sonar1.ping();
  unsigned int uS2 = sonar2.ping();
  uS1=uS1/US_ROUNDTRIP_CM;
  uS2=uS2/US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping 1: ");
  Serial.print(uS1); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.print("cm");
  Serial.print ("  Ping 2:");
  Serial.print(uS2);
  Serial.println("cm");
  if(uS1>0||uS2>0)
  delay(1000);
}

#include <Servo.h>

Servo myservo;  // Create Servo object

#define LDR_1 A0  // Pin for the first LDR
#define LDR_2 A1  // Pin for the second LDR

int pos = 90;         // Starting position of the servo (centered)
int Resistance = 20;  // Threshold for LDR difference to detect light imbalance

void setup() {
  myservo.attach(10);        // Attach the servo to pin 4
  pinMode(LDR_1, INPUT);    // Set LDR1 pin as input
  pinMode(LDR_2, INPUT);    // Set LDR2 pin as input
  myservo.write(pos);       // Initialize servo position to the middle (90 degrees)
  Serial.begin(9600);       // Initialize serial communication at 9600 baud
  delay(1000);              // Wait for a moment for initialization
}

void loop() {
  int value_1 = analogRead(LDR_1);  // Read the value from LDR1
  int value_2 = analogRead(LDR_2);  // Read the value from LDR2
  
  // Print LDR values for debugging
  Serial.print("Value1: ");
  Serial.print(value_1);
  Serial.print("\tValue_2: ");
  Serial.println(value_2);
  
  // Compare LDR values and move the servo based on the difference
  if(abs(value_1 - value_2) > Resistance) {
    if(value_1 > value_2) {
      pos++;  // Move servo right (increase position)
    } else {
      pos--;  // Move servo left (decrease position)
    }
  }

  // Ensure the servo position stays within the valid range (0 to 180 degrees)
  pos = constrain(pos, 0, 180);

  myservo.write(pos);  // Move the servo to the new position
  
  delay(50);  // Small delay for smooth operation
}
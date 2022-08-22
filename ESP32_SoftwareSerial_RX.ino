#include <SoftwareSerial.h>
#define ON_BOARD_LED 2

SoftwareSerial softSerial(12, 13); //5 = RX | 4 = TX
char string[40];
const unsigned int MAX_MESSAGE_LENGTH = 12;

void setup()
{
  Serial.begin(9600);
  softSerial.begin(9600);
  pinMode(ON_BOARD_LED, OUTPUT);
  Serial.println("Program started ");
}
void loop()
{
  while (softSerial.available() > 0)
  {
    // Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    // Read the next available byte in the serial receive buffer
    char inByte = softSerial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      Serial.println("Incoming Data : ");
      // Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    // Full message received...
    else
    {
      // Add null character to string
      message[message_pos] = '\0';

      // Print the message (or do other things)
      Serial.println(message);

      // Reset for the next message
      message_pos = 0;
    }
  }
}

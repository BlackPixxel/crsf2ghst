#define CRSF_FRAMETYPE_RC_CHANNELS_PACKED = 0x16,
HardwareSerial Serial2(D52, D53); // USART 2 on STM32 F767ZI
// Packet buffer
unsigned char cbuffer[64];
uint16_t channels[11];

void setup()
{
  Serial.begin(115200);
  Serial2.begin(420000);
  
  // Next packet started?
  while (Serial2.peek() != 238) // 238 = CF module address
  {
    // Consume one Byte
    Serial2.read();
  }
}

void loop()
{
  if (Serial2.available() > 25)
  {
    for (int i = 0; i < 26; i++)
    {
      cbuffer[i] = Serial2.read();
    }
    // Check Header
    if ( cbuffer[0] == 238)
    {
      Serial.println("");
      int k = 0;
      // Decode Channels
      channels[0] = (cbuffer[3] << 0) + ((cbuffer[4] & (0b00000111)) << 8);
      Serial.print(channels[0], DEC);
      Serial.print(",");
      channels[1] = ((cbuffer[4] & (0b11111000)) >> 3) + ((cbuffer[5] & (0b00111111)) << 5);
      Serial.print(channels[1], DEC);
      Serial.print(",");
      channels[2] = ((cbuffer[5] & (0b11000000)) >> 6) + ((cbuffer[6] & (0b11111111)) << 2) + ((cbuffer[7] & (0b00000001)) << 10);
      Serial.print(channels[2], DEC);
      Serial.print(",");
      channels[3] = ((cbuffer[7] & (0b11111110)) >> 1) + ((cbuffer[8] & (0b00001111)) << 7);
      Serial.print(channels[3], DEC);
      Serial.print(",");
      channels[4] = ((cbuffer[8] & (0b11110000)) >> 4) + ((cbuffer[9] & (0b01111111)) << 4);
      Serial.print(channels[4], DEC);
      Serial.print(",");
      channels[5] = ((cbuffer[9] & (0b10000000)) >> 7) + ((cbuffer[10] & (0b11111111)) << 1) + ((cbuffer[11] & (0b0000000011)) << 9);
      Serial.print(channels[5], DEC);
      Serial.print(",");
    }
    else
    {
      Serial.println("RX Error!");

      // Next packet started?
      while (Serial2.peek() != 238)
      {
        // Consume one Byte
        Serial2.read();
      }
    }
  }
}

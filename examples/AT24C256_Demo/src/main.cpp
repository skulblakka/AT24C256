#include <Arduino.h>
#include <AT24C256.h>

#define EEPROM_WIRE     Wire
#define EEPROM_ADDRESS  0x50
#define EEPROM_SIZE     (UINT16_MAX / 2)


AT24C256 eeprom(EEPROM_ADDRESS, &EEPROM_WIRE);


void setup()
{
    Serial.begin(115200);

    eeprom.begin();
}

void loop()
{
    uint8_t data[256];
    for (uint16_t i = 0; i < sizeof(data); i++) {
        data[i] = i;
    }

    for (uint32_t i = 0; i < EEPROM_SIZE; i += 256) {
        eeprom.write(i, data + i, sizeof(data));
    }

    for (uint32_t i = 0; i < EEPROM_SIZE; i += 256) {
        eeprom.read(i, data + i, sizeof(data));

        for (uint16_t j = 0; j < sizeof(data); j++) {
            if (j != data[j]) {
                Serial.print("Unexpected data: ");
                Serial.print(j);
                Serial.print(" != ");
                Serial.print(data[j]);
                Serial.print(" @ ");
                Serial.println(i + j);
            }
        }
    }

    Serial.println("Done");
    while (true) {
        ;
    }
}

#include <Arduino.h>
#include <Wire.h>

#include "AT24C256.h"


AT24C256::AT24C256(uint8_t address, TwoWire *twi)
{
    _address = address;
    _twi = twi;
}

void AT24C256::begin(uint32_t baudrate)
{
    _twi->begin();

    // Switch to passed baudrate
    _twi->setClock(baudrate);
}

bool AT24C256::write(uint16_t writeAddress, uint8_t *data, size_t len)
{
    size_t i = 0;
    while (i < len) {
        if (!ready()) {
            return false;
        }

        _twi->beginTransmission(_address);
        _twi->write((uint8_t) ((writeAddress >> 8) & 0xFF));
        _twi->write((uint8_t) (writeAddress & 0xFF));

        while (i < len) {
            _twi->write(data[i]);
            i += 1;
            writeAddress += 1;

            if (((writeAddress - 1) & AT24C256_PAGE_MASK) != (writeAddress & AT24C256_PAGE_MASK)) {
                break;
            }
        }

        if (_twi->endTransmission() != 0) {
            return false;
        }
    }

    return true;
}

uint8_t AT24C256::read(uint16_t readAddress, uint8_t *data, size_t len)
{
    if (!ready()) {
        return 0;
    }

    size_t i = 0;
    while (i < len) {
        size_t requestBytes = AT24C256_READ_CHUNK;
        if (requestBytes > (len - i)) {
            requestBytes = len - i;
        }


        _twi->beginTransmission(_address);

        const uint16_t currentAddress = readAddress + i;
        _twi->write((uint8_t) ((currentAddress >> 8) & 0xFF));
        _twi->write((uint8_t) (currentAddress & 0xFF));

        if (_twi->endTransmission(false) != 0) {
            return 0;
        }

        if (_twi->requestFrom(_address, requestBytes) == 0) {
            return 0;
        }

        const size_t prevI = i;

        while (_twi->available()) {
            data[i] = _twi->read();
            i++;
        }

        if ((i - prevI) != requestBytes) {
            return i;
        }
    }

    return i;
}

bool AT24C256::ready(void)
{
    const uint32_t timeout = millis();
    uint8_t err;

    do {
        _twi->beginTransmission(_address);
        err = _twi->endTransmission();
    } while ((err != 0) && ((millis() - timeout) < AT24C256_READY_TIMEOUT_MS));

    return (err == 0);
}

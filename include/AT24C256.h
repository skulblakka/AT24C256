#pragma once

#include <Arduino.h>
#include <Wire.h>


#ifndef AT24C256_READY_TIMEOUT_MS
    /**
     * @brief   Write cycle/ready timeout (in ms)
     */
    #define AT24C256_READY_TIMEOUT_MS       25
#endif

#ifndef AT24C256_READ_CHUNK
    /**
     * @brief   Read chunk size (in bytes)
     *
     * Number of bytes to read in a single read operation.
     * Usually limited to 256 bytes due to the Arduino Wire library.
     */
    #define AT24C256_READ_CHUNK             256
#endif

#ifndef AT24C256_PAGE_MASK
    /**
     * @brief   Mask for page write
     *
     * Mask defining the relevant bits for page-writes.
     * Filters the lower 6-bits allowing for 64-byte page-writes.
     */
    #define AT24C256_PAGE_MASK              (0xFFC0)
#endif


class AT24C256
{
    public:
        /**
         * @brief   AT24C256 instance
         *
         * @param   address         Device address
         * @param   twi             TwoWire interface
         */
        AT24C256(uint8_t address, TwoWire *twi);

        /**
         * @brief   Begin function for AT24C256
         *
         * @warning Call before any other function of this class!
         *
         * @param   baudrate        Baudrate to use for I2C communication
         */
        void begin(uint32_t baudrate = 1000000);

        /**
         * @brief   Write data
         *
         * Write data to EEPROM. Page-writes will be performed if possible.
         * ready() is called before and between writes.
         *
         * @param   writeAddress    EEPROM write start address
         * @param   data            Data
         * @param   len             Data length (in bytes)
         *
         * @return  true if successful; false otherwise
         */
        bool write(uint16_t writeAddress, uint8_t *data, size_t len);

        /**
         * @brief   Read data
         *
         * Read data from EEPROM.
         * ready() is called before read.
         *
         * @param   readAddress     EEPROM read start address
         * @param   data            Pointer to read into
         * @param   len             Number of bytes to read
         *
         * @return  Number of bytes actually read
         */
        uint8_t read(uint16_t readAddress, uint8_t *data, size_t len);

        /**
         * @brief   Check if EEPROM ready
         *
         * Check if EEPROM is ready by using ACK polling.
         * Waits for maximum #AT24C256_READY_TIMEOUT_MS before timeout.
         *
         * @return  true if ready; false on timeout
         */
        bool ready(void);

    private:
        uint8_t _address;
        TwoWire *_twi;
};
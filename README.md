# AT24C256

Simple library for accessing AT24C256 EEPROM from Microchip.

The library supports page-write and ACK-polling for improved (write) performance.


## Usage
This library is intended to simply write binary data into the EEPROM. It doesn't define any datatypes or memory organization.

Check [AT24C256.h](include/AT24C256.h) for the full documentation.<br>
Make sure to check [Examples](examples) as well.

## Compatibility
The library was tested with an MKRZero but should support all Boards supporting the official Wire interface.

If the interface uses a transmit buffer of less than 256 bytes the `AT24C256_READ_CHUNK` define must be adjusted accordingly.

Additionally if the transmit buffer is less than 64 bytes the `AT24C256_PAGE_MASK` must be adjusted as well.

These defines can also be used to support different EEPROMs from the AT24CXXX series.
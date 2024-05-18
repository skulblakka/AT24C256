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

## License
```
MIT License

Copyright (c) 2024 skulblakka

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

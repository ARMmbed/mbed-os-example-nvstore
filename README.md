# mbed-os-example-nvstore

NVStore example for Mbed OS

## Getting started with NVStore ##

This is an example of an application that uses the NVStore APIs.

The application invokes the NVStore APIs and prints the results after each such invocation. 

## Required hardware
* An [FRDM-K64F](http://os.mbed.com/platforms/FRDM-K64F/) development board.
* A micro-USB cable.

### Other hardware

Although the board shown in this examples is K64F, the example should work on any Mbed enabled hardware supporting the internal flash driver (has "FLASH" in the "device_has" in targets/target.json file).

##  Getting started ##

1. Import the example.

   ```
   mbed import mbed-os-example-nvstore
   cd mbed-os-example-nvstore
   ```
   
2. Configure the NVStore areas (if needed).

   Edit ```mbed_app.json``` to reflect the addresses and sizes of both NVStore areas. Each area should reside on complete and continuous sectors (typcally one), which aren't used for any other purposes (like the programmed application). The values shown in this example supports the K64F and K82F boards (two last sectors for each). Add your own board there. 

3. Compile and generate binary.

   For example, for `GCC`:

   ```
   mbed compile -t GCC_ARM -m K64F
   ```
   
 4. Open a serial console session with the target platform using the following parameters:
 
    * **Baud rate:** 115200
    * **Data bits:** 8
    * **Stop bits:** 1
    * **Parity:** None
 
 5. Copy the application `mbed-os-example-nvstore.bin` in the folder `mbed-os-example-nvstore/BUILD/<TARGET NAME>/<PLATFORM NAME>` onto the target board.
 
 6. Press the **RESET** button on the board to run the program
 
 7. The serial console should now display a series of results following the NVStore API invocations. 
 
## Troubleshooting

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.

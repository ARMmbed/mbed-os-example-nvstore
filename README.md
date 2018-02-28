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
   
 2. Start with the default NVStore configuration, which uses the last two sectors (4KB each) as NVStore areas.

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
 
 8. Now copy ```mbed_app-8KB-areas.json``` to  ```mbed_app.json```. This should use 8KB areas (two pairs of last sectors) as NVStore areas.

 9. Repeat steps 3-7. Notice the changes in prints of area addresses and sizes and with the amount of possible keys this configuration can hold.

10. Now copy ```mbed_app-disabled.json``` to  ```mbed_app.json```. This disables NVStore.

11. Repeat steps 3-7. Notice that the program now prints that NVStore is disabled.

12. To restore default configuration, copy ```mbed_app-default-areas.json``` to  ```mbed_app.json```.

## Troubleshooting

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.

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
   
 2. Keep the default NVStore configuration, which uses the last two sectors (4KB each) as NVStore areas.

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
 
 8. Unless specifically configured by the user, NVStore selects the last two flash sectors as its areas, with the minimum size of 4KBs. This means that if the sectors are smaller, a few continuous ones will be used for each area.
 
    If the automatically selected sectors do not fit your flash configuration, you can override this by setting the addresses and sizes of both areas in `mbed_lib.json` for each board. 
    
	Copy `mbed_app-K64F-8KB-areas.json` to `mbed_app.json` and edit `mbed_app.json` to match your board.
	This example is defining 2 areas of 8KB each (the last four sectors) as NVStore areas.
        
	Set the following four attributes:
        
	-   `area_1_address`
	-   `area_1_size`
	-   `area_2_address`
	-   `area_2_size`
	
	

 9. Repeat steps 3-7. Notice the changes in prints of area addresses and sizes and with the amount of possible keys this configuration can hold.

10. To restore the default configuration, copy `mbed_app-default-areas.json` to `mbed_app.json`.

## Troubleshooting

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.

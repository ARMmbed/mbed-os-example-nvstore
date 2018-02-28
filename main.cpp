/*
* Copyright (c) 2018 ARM Limited. All rights reserved.
* SPDX-License-Identifier: Apache-2.0
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "mbed.h"
#include "nvstore.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Entry point for the example
int main() {
    printf("\n--- Mbed OS NVStore example ---\n");

    uint16_t actual_len_bytes = 0;

    // NVStore is a sigleton, get its instance
    NVStore &nvstore = NVStore::get_instance();

    int rc;
    uint16_t key;

    // Values read or written by NVStore need to be aligned to a uint32_t address (even if their sizes
    // aren't)
    uint32_t value;

    // Initialize NVstore. Note that it can be skipped, as it is lazily called by all other APIs
    rc = nvstore.init();
    printf("Init NVStore. ");
    printf("Return code is %d\n", rc);

    // Show NVStore size, maximum number of keys and area addresses and sizes
    printf("NVStore size is %d\n", nvstore.size());
    printf("NVStore max number of keys is %d (out of %d possible ones in this flash configuration)\n",
            nvstore.get_max_keys(), nvstore.get_max_possible_keys());
    printf("NVStore areas:\n");
    for (uint8_t area = 0; area < NVSTORE_NUM_AREAS; area++) {
        uint32_t area_address;
        size_t area_size;
        nvstore.get_area_params(area, area_address, area_size);
        printf("Area %d: address 0x%08lx, size %d (0x%x)\n", area, area_address, area_size, area_size);
    }

    // Clear NVStore data. Should only be done once at factory configuration
    rc = nvstore.reset();
    printf("Reset NVStore. ");
    printf("Return code is %d\n", rc);

    // Now set some values to the same key
    key = 1;

    value = 1000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    printf("Return code is %d\n", rc);

    value = 2000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    printf("Return code is %d\n", rc);

    value = 3000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    printf("Return code is %d\n", rc);

    // Get the value of this key (should be 3000)
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. Value is %ld. ", key, value);
    printf("Return code is %d\n", rc);

    // Now remove the key
    rc = nvstore.remove(key);
    printf("Delete key %d. ", key);
    printf("Return code is %d\n", rc);

    // Get the key again, now it should not exist
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. ", key);
    printf("Return code is %d\n", rc);

    key = 12;

    // Now set another key once (it can't be set again)
    value = 50;
    rc = nvstore.set_once(key, sizeof(value), &value);
    printf("Set key %d once to value %ld. ", key, value);
    printf("Return code is %d\n", rc);

    // This should fail on key already existing
    value = 100;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    printf("Return code is %d\n", rc);

    // Get the value of this key (should be 50)
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. Value is %ld. ", key, value);
    printf("Return code is %d\n", rc);

    // Get the data size for this key (should be 4)
    rc = nvstore.get_item_size(key, actual_len_bytes);
    printf("Data size for key %d is %d. ", key, actual_len_bytes);
    printf("Return code is %d\n", rc);

    printf("\n--- Mbed OS NVStore example done. ---\n");
}

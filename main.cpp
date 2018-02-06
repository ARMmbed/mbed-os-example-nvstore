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

void display_return_code (int rc, int expected_rc)
{
    char ret_str[32];

    switch (rc) {
    case NVSTORE_SUCCESS :
        strcpy(ret_str, "Success");
        break;
    case NVSTORE_READ_ERROR :
        strcpy(ret_str, "Read error");
        break;
    case NVSTORE_WRITE_ERROR :
        strcpy(ret_str, "Write error");
        break;
    case NVSTORE_NOT_FOUND :
        strcpy(ret_str, "Key not found");
        break;
    case NVSTORE_DATA_CORRUPT :
        strcpy(ret_str, "Data corrupt");
        break;
    case NVSTORE_BAD_VALUE :
        strcpy(ret_str, "Bad value");
        break;
    case NVSTORE_BUFF_TOO_SMALL :
        strcpy(ret_str, "Buffer too small");
        break;
    case NVSTORE_FLASH_AREA_TOO_SMALL :
        strcpy(ret_str, "Flash area too small");
        break;
    case NVSTORE_OS_ERROR :
        strcpy(ret_str, "OS error");
        break;
    case NVSTORE_BUFF_NOT_ALIGNED :
        strcpy(ret_str, "Buffer not aligned");
        break;
    case NVSTORE_ALREADY_EXISTS :
        strcpy(ret_str, "Key already exists");
        break;
    }
    printf("Return value is %s (%s)\n",
           ret_str, (rc == expected_rc) ? "expected" : "NOT EXPECTED!");
}

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

    // Initialize NVstore. Note that it can be skipped, as it is lazily called by all APIs
    rc = nvstore.init();
    printf("Init NVStore. ");
    display_return_code(rc, NVSTORE_SUCCESS);

    // Clear NVStore data. Should only be done regularly at initial installation
    rc = nvstore.reset();
    printf("Reset NVStore. ");
    display_return_code(rc, NVSTORE_SUCCESS);

    // Show NVStore size and maximum number of keys
    printf("NVStore size is %ld\n", nvstore.size());
    printf("NVStore max number of keys is %d\n", nvstore.get_max_keys());

    // Now set some values to the same key
    key = 1;

    value = 1000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    value = 2000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    value = 3000;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    // Get the value of this key (should be 3000)
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. Value is %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    // Now remove the key
    rc = nvstore.remove(key);
    printf("Delete key %d. ", key);
    display_return_code(rc, NVSTORE_SUCCESS);

    // Get the key again, now it should not exist
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. ", key);
    display_return_code(rc, NVSTORE_NOT_FOUND);


    key = 12;

    // Now set another key once (can't set again)
    value = 50;
    rc = nvstore.set_once(key, sizeof(value), &value);
    printf("Set key %d once to value %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    // This should fail on key already existing
    value = 100;
    rc = nvstore.set(key, sizeof(value), &value);
    printf("Set key %d to value %ld. ", key, value);
    display_return_code(rc, NVSTORE_ALREADY_EXISTS);

    // Get the value of this key (should be 50)
    rc = nvstore.get(key, sizeof(value), &value, actual_len_bytes);
    printf("Get key %d. Value is %ld. ", key, value);
    display_return_code(rc, NVSTORE_SUCCESS);

    // Get the data size for this key (should be 4)
    rc = nvstore.get_item_size(key, actual_len_bytes);
    printf("Data size for key %d is %d. ", key, actual_len_bytes);
    display_return_code(rc, NVSTORE_SUCCESS);

    printf("\n--- Mbed OS NVStore example done. ---\n");
}

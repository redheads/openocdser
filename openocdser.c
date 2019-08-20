/* 
 * Copyright (c) 2019 Moritz Strübe, Redheads Ltd
 * 
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <stdio.h>

int main(int argc, const char * argv[]) {
    if(!argv[1]){
        printf("Run using %s [file with serial]\n"
            "\n"
            "To find all Stlink devices you can run:\n"
            "grep STLink -l /sys/bus/usb/devices/*/product | xargs dirname  | xargs -I{} -n1 %s {}/serial\n",  argv[0],  argv[0]); 
        return 1;
    }
    FILE * fd = fopen(argv[1], "r");
    if(!fd) {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }

    unsigned char buf[64];

    int len = fread(buf, 1, sizeof(buf), fd);

    if(!len) {
        printf("No data in %s\n", argv[1]);
        fclose(fd);
        return 3;
    }

    //I have no idea why len is -1
    for(int idx = 0; idx < len - 1; idx++) {
        if(buf[idx] & 0x80){
                 putchar('?'); //libusb_get_string_descriptor_ascii
                 if(buf[idx+1] &0x80) idx++; // Trial and Error
        }
        else if(buf[idx] > 0x20) putchar(buf[idx]);
        else printf("\\x%02x", buf[idx]);
    }

    putchar('\n');
    fclose(fd);
}

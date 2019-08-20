# OPENOCDSER

This little program converts a serial number of a USB device to a string that can be passed to OpenOCD via the command line.

## Building

`make openocdser` should do the job on most systems.
Otherwise compile it with your favorite C-compiler.

## Running

You need to pass a file containing the serial number to openocdser.
To list all serials of STLink debuggers you can use:

```sh
grep STLink -l /sys/bus/usb/devices/*/product | xargs dirname | xargs -I{} -n1 ./openocdser {}/serial
```

## License

GPL v3

Have fun.

# Switch Tester by RAW HID

## Requirements

* a keyboard using RP2040
* building environment for pico-sdk
* WebHID enabled Web browser (Edge, Chrome, etc)

## Build

Configure `ROW_COUNT`, `COL_COUNT`, `row_pins` and `col_pins` in `pico/main.c` 

Then

```shell
$ mkdir -p pico/build
$ cd pico/build
$ cmake ..
$ make -j8
```

## Try

1. drag-n-drop `switch_tester.uf2` into `RPI-RP2` drive
2. open [docs/switch-tester.html](https://yswallow.github.io/switch-tester/switch-tester.html) by a WebHID-enabled Web browser
3. click `Connect` button
4. select device
5. the page starts showing the switch number


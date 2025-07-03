# O51go Custom Firmware (Based on Salicylic-acid3's Vial-QMK Firmware)

This is a modified Vial-QMK firmware for the [o51go keyboard](https://github.com/Salicylic-acid3/vial-qmk/tree/vial/keyboards/salicylic_acid3/o51go), originally created by [Salicylic-acid3](https://github.com/Salicylic-acid3).

## Changes
- Some JIS keycodes have been overridden to emulate a pseudo-US layout
- Host OS detection

## License
This project inherits the original MIT license from QMK and Salicylic-acid3's firmware.

![O51Go](https://s2.booth.pm/1d33594d-0c5f-4f93-baf5-2e89e0d99afc/i/5528166/b6492818-45d6-44d5-a60c-c3066d6362d8_base_resized.jpg)

40% Ortholinear Keyboard

* Keyboard Maintainer: [Salicylic-acid3](https://github.com/Salicylic-acid3)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: (https://keeb-on.com/products/40keyboard-goforty)

Make example for this keyboard (after setting up your build environment):

    make o51go:vial

Flashing example for this keyboard:

    make o51go:vial:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

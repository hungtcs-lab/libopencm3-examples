# README
[![Build Status](https://travis-ci.org/libopencm3/libopencm3-examples.svg?branch=master)](https://travis-ci.org/libopencm3/libopencm3-examples)

[![Gitter channel](https://badges.gitter.im/libopencm3/discuss.svg)](https://gitter.im/libopencm3/discuss)

此项目库包含libopencm3的各种示例项目。

libopencm3项目旨在为各种ARM Cortex-M微控制器创建一个开源固件库。

更多信息请访问 http://libopencm3.org

这些简单示例是基于多个平台上不同子系统的。如果您只是想测试您的构建环境或硬件，[libopencm3-miniblink](https://github.com/libopencm3/libopencm3-miniblink)项目是一个很好方案。

## 使用方法

必须先在项目根目录=执行`make`，它构建libopencm3库所示项目。
如果修其任何示项目可直示项目目运行`make clean && make`命令从新构建项目。

For more verbose output, to see compiler command lines, use "make V=1"
For insanity levels of verboseness, use "make V=99"

The makefiles are generally useable for your own projects with
only minimal changes for the libopencm3 install path (See Reuse)

## Make Flash Target

Please note, the "make flash" target is complicated and not always self-consistent.  Please see: https://github.com/libopencm3/libopencm3-examples/issues/34

For flashing the 'miniblink' example (after you built libopencm3 and the
examples by typing 'make' at the top-level directory) onto the Olimex
STM32-H103 eval board (ST STM32F1 series microcontroller), you can execute:

    cd examples/stm32/f1/stm32-h103/miniblink
    make flash V=1

The Makefiles of the examples are configured to use a certain OpenOCD
flash programmer, you might need to change some of the variables in the
Makefile if you use a different one.

To program via a Black Magic Probe, simply provide the serial port, eg:

    cd examples/stm32/f1/stm32-h103/miniblink
    make flash BMP_PORT=/dev/ttyACM0

To program via texane/stlink (st-flash utility), use the special target:

    cd examples/stm32/f1/stm32vl-discovery/miniblink
    make miniblink.stlink-flash

If you rather use GDB to connect to the st-util you can provide the STLINK\_PORT
to the flash target.

    cd examples/stm32/f1/stm32vl-discovery/miniblink
    make flash STLINK_PORT=:4242

## Flashing Manually
You can also flash manually. Using a miriad of different tools depending on
your setup. Here are a few examples.

### OpenOCD

    openocd -f interface/jtagkey-tiny.cfg -f target/stm32f1x.cfg
    telnet localhost 4444
    reset halt
    flash write_image erase foobar.hex
    reset

Replace the "jtagkey-tiny.cfg" with whatever JTAG device you are using, and/or
replace "stm32f1x.cfg" with your respective config file. Replace "foobar.hex"
with the file name of the image you want to flash.

### Black Magic Probe

    cd examples/stm32/f1/stm32vl-discovery/miniblink
    arm-none-eabi-gdb miniblink.elf
    target extended_remote /dev/ttyACM0
    monitor swdp_scan
    attach 1
    load
    run

To exit the gdb session type `<Ctrl>-C` and `<Ctrl>-D`. It is useful to add the
following to the .gdbinit to make the flashing and debugging easier:

    set target-async on
    set confirm off
    set mem inaccessible-by-default off
    #set debug remote 1
    tar ext /dev/ttyACM0
    mon version
    mon swdp_scan
    att 1

Having this in your .gdbinit boils down the flashing/debugging process to:

    cd examples/stm32/f1/stm32vl-discovery/miniblink
    arm-none-eabi-gdb miniblink.elf
    load
    run

### ST-Link (st-util)

This example uses the st-util by texane that you can find on [GitHub](https://github.com/texane/stlink).

    cd examples/stm32/f1/stm32vl-discovery/miniblink
    arm-none-eabi-gdb miniblink.elf
    target extended-remote :4242
    load
    run

## Reuse

If you want to use libopencm3 in your own project, the _easiest_ way is
to use the template repository we created for this purpose.

See https://github.com/libopencm3/libopencm3-template

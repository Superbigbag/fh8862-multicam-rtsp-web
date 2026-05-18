#!/bin/sh

set_gpio()
{
    if [ ! -d "/sys/class/gpio/GPIO$1" ]; then
        echo $1 > /sys/class/gpio/export
        echo out > /sys/class/gpio/GPIO$1/direction
    fi

    echo $2 > /sys/class/gpio/GPIO$1/value
}

insmod vmm.ko mmz=anonymous,0,0x18000000,916992K anony=1

#reset sensor
set_gpio 13 0
set_gpio 71 0


sleep 1

insmod xbus_rpc.ko fn=rtthread_arc_FH8862.bin fa=0x4ff80000

#reset sensor
set_gpio 13 1
set_gpio 71 1

insmod media_process.ko
insmod vb.ko
insmod isp.ko
insmod vpu.ko vpu_mode=buf_0_2,buf_1_2
insmod enc.ko
insmod jpeg.ko
insmod bgm.ko
insmod nna.ko
insmod vgs.ko
insmod vou.ko
insmod hello_world.ko

echo iptocycle_0>/proc/driver/vpu
#echo ecbypass_on_0 > /proc/driver/vicap
#echo ecbypass_on_1 > /proc/driver/vicap
#echo ecbypass_on_2 > /proc/driver/vicap

echo 2 >/proc/sys/kernel/printk

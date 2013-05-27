#!/bin/sh
TMP=$(sed -n '1p' ./etc/tmp/devices.list)
#ANDROID_DEVICE=$(echo $TMP  | sed -e 's/ .*//g')
echo $TMP > ./etc/vusr/devices.list

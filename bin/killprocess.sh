#!/bin/sh
$PID = $(./bin/adb shell pgrep com.acanoe.appmanager)
echo $PID
./bin/adb shell kill $PID 

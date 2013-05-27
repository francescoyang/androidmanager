#!/bin/sh

./bin/adb shell am broadcast -a ServiceStop
./bin/adb shell am broadcast -a ServiceStop
#./bin/adb shell am broadcast -a ServiceStop
#./bin/adb forward tcp:2222 tcp:2222
./bin/adb forward tcp:12580 tcp:10086
./bin/adb shell am broadcast -a ServiceStart

#./bin/adb  shell am start -a android.intent.action.SENDTO -d sms:10086 --es sem_body csye 3053
#./bin/adb  shell am start -a android.intent.action.SENDTO -d sms:10086 --es sms_body 3053
#./bin/adb  shell am start -a android.intent.action.SENDTO -d sms:10086 --es sms_body 你叫什么名字
#./bin/adb  shell am profile com.android.mms stop
./bin/adb  shell am  start -a android.intent.action.SENDTO -d sms:10086 --es sms_body 你叫什么名字
#./bin/adb  shell am  start -a android.intent.action.SENDTO -d sms:10086 --es sms_body 你叫什么名字
./bin/adb shell input keyevent 22
./bin/adb shell input keyevent 66
#./bin/adb  shell am profile com.android.mms stop

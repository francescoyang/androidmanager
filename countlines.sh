judge_your_input()
{
	if [ -z $1 ] ;  then
		echo "please input your want count dir!"
		echo ""
		echo "example:"
		echo "./back_file ./"
		echo "like this example"
		echo ""
		exit
	fi
}

judge_your_input $1
C_file_linescount=$(find $1 -name "*.c" |xargs cat|grep -v ^$|wc -l)
CPP_file_linescount=$(find $1 -name "*.cpp" |xargs cat|grep -v ^$|wc -l)
INCLUDE_file_linescount=$(find $1 -name "*.h" |xargs cat|grep -v ^$|wc -l)
UI_file_linescount=$(find $1 -name "*.ui" |xargs cat|grep -v ^$|wc -l)
QSS_file_linescount=$(find $1 -name "*.qss" |xargs cat|grep -v ^$|wc -l)
JAVA_file_linescount=$(find $1 -name "*.java" |xargs cat|grep -v ^$|wc -l)
echo "c	file count = "$C_file_linescount
echo "cpp	file count = "$CPP_file_linescount
echo "inc	file count = "$INCLUDE_file_linescount
echo "ui	file count = "$UI_file_linescount
echo "qss	file count = "$QSS_file_linescount
echo "java	file count = "$JAVA_file_linescount
total=$[$C_file_linescount+$CPP_file_linescount+$INCLUDE_file_linescount+$UI_file_linescount+$QSS_file_linescount+$JAVA_file_linescount]
echo "The total =	 "$total

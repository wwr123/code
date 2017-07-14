#!/bin/bash
#if [ -f file ];then  #判断是否为普通文件
#while read line
#do
#	str1=$(echo $line | cut -c 1-3) #$()将标准输出作为输入
#	str2=$(echo $line | cut -c 4-6 | tr '[a-z]' '[A-Z]')
#	str3=$(echo $line | cut -c 7-)
#	echo $str3$str2$str1
#done <file
#fi

#1 1 2 3 5 8 ....
[ $# -ne 1 ] && exit 1 
function fib()
{
	if [ $1 -lt 3 -a $1 -gt 0 ]; then
		echo 1
		return 
	else
		n=$1
		#let count=n-1
		let n--
		ret1=$(fib $n)
		#let count=n-2
		let n--
		ret2=$(fib $n) 
		let ret3=ret1+ret2
		echo ${ret3}
	fi
}
fib $1

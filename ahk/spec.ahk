#NoEnv
SetWorkingDir %A_ScriptDir%
CoordMode, Mouse, Client
SendMode Input
#SingleInstance Force
SetTitleMatchMode 2
#WinActivateForce
SetControlDelay 1
SetWinDelay 0
SetKeyDelay -1
SetMouseDelay -1
SetBatchLines -1

; ANTI-BAN
sleep_upper = 40
sleep_lower = 30

; Random Sleep within a range
RandSleep(x,y) {
Random, rand, %x%, %y%
Sleep %rand%
return
}
; ANTI-BAN
; Random Speed within a range must be between 0-1000
; x is lower bound y is upper
RandSpeed(x,y) {
	if (y > 100 or x > y or x < 0 or y < x) {
		Random, rand, 1,5
	}else{
		Random, rand, %x%, %y%
	}
		return rand
}

; 1st spec and Prayers
4:: 
; Click weapon and spec bar
MouseGetPos xpos, ypos
MouseMove, 621, 537, RandSpeed(1,5)

Click
RandSleep(sleep_lower,sleep_upper)
Send, {f2}
RandSleep(sleep_lower, sleep_upper)
Click

; Prayers On
Send, {f3}
RandSleep(sleep_lower, sleep_upper)
MouseMove, 609, 456, RandSpeed(1,5)
RandSleep(sleep_lower, sleep_upper)
Click
RandSleep(sleep_lower, sleep_upper)
MouseMove, 758, 430, RandSpeed(1,5)
RandSleep(sleep_lower, sleep_upper)
Click
RandSleep(sleep_lower, sleep_upper)


; Click Player
MouseMove, xpos, ypos, RandSpeed(1,5)
RandSleep(sleep_lower,sleep_upper)
Click
return

; 2nd spec and Prayers off
5::
; Click weapon and spec bar
MouseGetPos xpos, ypos
Send, {f1}
RandSleep(sleep_lower,sleep_upper)
Click, 656, 540
RandSleep(sleep_lower,sleep_upper)
Send, {f2}
RandSleep(sleep_lower,sleep_upper)
Click, 556, 540
RandSleep(sleep_lower,sleep_upper)
Send, {f1}
RandSleep(sleep_lower,sleep_upper)
MouseMove, xpos, ypos, RandSpeed(1,5)
RandSleep(sleep_lower, sleep_upper)
Click
return




shift::suspend
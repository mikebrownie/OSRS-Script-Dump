﻿#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
CoordMode, Mouse, Client
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
sleep_lower = 20

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

; Gmaul Double Whack
4:: 
; Click weapon
MouseGetPos xpos, ypos
MouseMove, 637, 498, RandSpeed(1,5)
RandSleep(sleep_lower,sleep_upper)

Click
RandSleep(sleep_lower,sleep_upper)

; Click spec bar x2
Send, {f2}
RandSleep(sleep_lower, sleep_upper)
Click
; Once now
RandSleep(sleep_lower, sleep_upper)
Click

; Ultimate Strength On
Send, {f3}
RandSleep(sleep_lower, sleep_upper)
MouseMove, 666, 350, RandSpeed(1,5)
RandSleep(sleep_lower, sleep_upper)
Click
RandSleep(sleep_lower, sleep_upper)


; Click Player
MouseMove, xpos, ypos, 1
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




`::suspend
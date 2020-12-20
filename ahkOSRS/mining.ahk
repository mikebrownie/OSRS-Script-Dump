1::

loop {

	;tinrocks
	Random, x1, 155, 275
	Random, y1, 293, 424

	Random, x2, 288, 426
	Random, y2, 190, 300
		
		
	;inventory
	Random, inv1, 588, 619
	Random, inv2, 630, 661
	Random, inv3, 672, 703
	Random, row1, 296, 326
	
	;sleeps
	Random, s1, 250, 500
	Random, s2, 3000, 4000 
	
	;speed
	Random, mouseSpeed, 0, 20

Mousemove, x1, y1, mouseSpeed
sleep s1
click

PixelGetColor, originalColor, 160, 367
newColor = %originalColor%
MsgBox, originalColor: %originalColor% newColor: %newColor%
while (True){
	PixelGetColor, newColor, 160, 367
	if %originalColor% == %newColor%
		break
}
MsgBox, originalColor: %originalColor% newColor: %newColor%


Mousemove, x2, y2, mouseSpeed
sleep s1
click
PixelGetColor, originalColor, 372, 221
newColor = %originalColor%
while (%originalColor% == %newColor%){
	PixelGetColor, newColor, 372, 221
}
sleep s1


	;dropping
	send {shift down}
	sleep s1
	
	MouseMove inv1, row1
	sleep s1
	click
	sleep s1
	
	MouseMove inv2, row1
	sleep s1
	click
	sleep s1
	
	send {shift up}
	sleep s1
}
2::reload
3::exitapp


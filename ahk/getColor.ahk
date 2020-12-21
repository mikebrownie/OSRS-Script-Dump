1::

MouseGetPos, MouseX, MouseY
	PixelGetColor, c, %MouseX%, %MouseY%
	
MsgBox, The color at the current cursor position is: %c%

2::reload
3::exitapp
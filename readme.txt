"Melody" library
Created by: Matan Bright
--------------------------------------------------------------------------------------------------------------------------------------


Introduction
------------
This library allows you to play melodies with a passive buzzer.
If you are using Arduino MEGA you can play melodies on multiple passive buzzers asynchronously (at the same time).
The library is easy to use and does not require any advanced knowledge in Arduino.


How to use the library?
-----------------------
1) Include the library in your sketch
	#include <Melody.h>
2) Create an object of the library's "Melody" class (or multiple objects on arduino MEGA)
	Melody melodyName;


Limitations
-----------
* You can't create copies from the "Melody" class objects (by assigning a value-type object to another value-type object).
This is because each object is statically assigned to a free timer.
If you do that, the copied object will be invalid and useless (the function "isValid" will return 'false', and all the other functions will not work on that object).
	Melody melody1;
	Melody melody2 = melody1;
But you can assign the object to a pointer or a reference, because they don't copy the object.
	Melody melody1;
	Melody *melody2 = &melody1;
	Melody &melody3 = melody1;
So, if you make a function which gets a "Melody" object, make the parameter as a pointer or a reference (a reference is more recommended, because it is used like a normal value-type object).

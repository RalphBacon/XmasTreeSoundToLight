# XmasTreeSoundToLight
Arduino code for (and details of the kit for) a 3D Xmas Tree Sound To Light project

A sound-to-light Xma Tree? Well, why not, the festive season is almost upon us and it's great to see this tree flashing along to the music (or TV, or just you talking). And when there's silence it just gently fades in and out the 3 different colour LEDs.

This is a good example of how to take a decent enough kit but then add value with an Arduino. Not only that but you're exposed to some *analogue discrete components* as you build the *two-transistor, ultra-simple microphone preamplifier*. It's so easy and very satisfying to get it all working.

The code (sketch) for the Arduino demonstrates the use of arrays, pointers (well, just the one, actually) and it all runs in real time without the use of any "delay" statements (OK, just the one) to get it moving towards a "state-machine", which is where many things seem to be happening at once but in reality the Arduino is giving each of them a small time-slice to do something in.

Download the sketch and have a look. Anything not clear or confusing? Something need a bit more explanation? Leave me a comment or ask a question below this video and I'll see what I can do.

----------------------------
Music attribution:
----------------------------
Traditional Christmas Songs. Instrumental Music. Free downloads completely legal for all the world. The most famous traditional Christmas songs. Royalty free music for no-profit use as youtube videos, phone ringtones, email attachment, school plays soundtrack. http://www.freexmasmp3.com/index.html

Jingle Bells 7 by Kevin MacLeod is licensed under a Creative Commons Attribution licence (https://creativecommons.org/licenses/by/4.0/)
Artist: http://incompetech.com/


------------------------------------------
Sketch can be found here:
------------------------------------------
https://github.com/RalphBacon/XmasTreeSoundToLight

-------------------------------------------------------
Links to the Xmas Tree kit(s) here:
-------------------------------------------------------

Banggood: http://www.banggood.com/Christmas-Tree-LED-Flash-Kit-3D-DIY-Electronic-Learning-Kit-p-1007523.html?rmmds=search

GearBest: http://www.gearbest.com/kits/pp_265052.html?wid=21

Whichever one you choose make sure you get the 3-colour version NOT the 'colourful' version which uses those RGB LEDs that cannot be controlled by the Arduino using this sketch.

See https://www.youtube.com/c/RalphBacon video #57 for full details.

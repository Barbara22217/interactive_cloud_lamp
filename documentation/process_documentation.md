### 1.	Project Overview ###
The goal of this project was to design and build an interactive cloud lamp using an Arduino Uno and a WS2812B LED strip.
The lamp combines aesthetic lighting with interactive controls including buttons, brightness control, and a touch-activated breathing effect. I wanted to create an interactive lamp that at the same time is and aesthetic and calming. I took my inspiration from a Pinterest, where I saw all of these cozy, aesthetic cloud lamps trending a while ago. 
### 2.	Concept Development ###
I came up with my idea pretty quickly, when scrolling through Pinterest. From the very beginning I knew I wanted to make the lamp interactive and was really motivated to create something aesthetically looking using Arduino. 
At first my idea was to use RGB LED included in the Arduino set. But after talking about this with professor and colleagues I realized that, since the RGB LED is really small, even after enhancing the reflection of it with for example baking paper, it will not be strong enough to create nice, bright effect of lamp.
So I thought that maybe I can use multiple small one color LEDs. But I have to leave this idea as well, cause it would cause some wiring problems, and I wouldn’t have enough pins to collect the LEDs to. 
So I finally decided to use LED strip. This way I could have a nice bright light, with the option of different colors and no wiring problems. 
As I had all of my hardware, I started wiring and testing. 
At first I connected the LED strip to the breadboard, using resistor. (look: photo #1, video #1) 
After this connection has been made I tested it with a code from the FastLED library, to see if the connection is working. The code I took from file --> examples --> FastLED --> Color Pallete. 
I had to make some changes in it. I changed the LED type to WS2812B, and I also had to change the LED pin (look: code 1). 
It was working so I could start experimenting with different features. The code from the library was making the color constantly changing every second, changing them along the strip, without any breaks. I wanted it to be calm lamp so I started experimenting.
I started small, with just changing the code (I used ChatGPT to simplify the code a bit) so I have multiple colors on the strip, but not changing, not blinking, just there. (code #2).
It worked great, so I thought I want to try just having one color stable all the time (code #3). 
Then I was ready to add more elements to control the lamp.
I started by adding the button to breadboard and connecting it with Arduino. I wanted the button to turn the LED on and off. I asked ChatGPT about the code I should use for that. (look: code #4). It worked great. (photo #2, video #2)
Next, I added potentiometer to control the brightness of the lamp (look: photo #3). I made all connections, and using the code we did in class when working with potentiometer, I managed to create my code piece(look: code #5) that enabled to control the brightness of the light. (look: video #3). 
After that, I decided I want to use the button to also control the color change. The short click of the button was supposed to turn the lamp on/off, and the long press was supposed to change the colors: white, blue and pink. With that I also asked chatgpt what to change in the code to enable this color change after a long press. (look: code #6). At first in the code, ChatGPT used “WarmWhite” as the color, but since it was not defined in the fastLED library I got error, and have to change it, defining the warm white myself. After I did it, it worked out and just like that, another feature was added to my lamp (look: video #4). 
This is where things started to get a bit complicated, cause I had many ideas on what else to implement, and I realized that I am mixing it a bit: the interactive features with non-interactive features. So I had to make up my mind and decide. I decided to focus on very interactive, conscious features. So I started testing. 
At first I thought I would like to add the breathing mode. I wanted it to be controlled also through potentiometer – meaning, when the potentiometer was turned maximum to the left the breathing mode was enabled, when it was turned to right, the breathing mode was disabled, and you could only control the brightness with the potentiometer (code #7, video #5). But after I implemented it, I thought it is not very intuitive for user, so decided to change it. 
So I thought that maybe I can use the ultrasonic sensor and when the hand was next to the ultrasonic sensor the breathing mode was enabled (code #8). It worked, but I wasn’t fully satisfied with how it worked, and the fact that user could accidentally turn on the breathing mode, just by getting closer to the lamp wasn’t ideal either. But I decided to leave it for a moment. 
And then, I still wanted to add a feature, so I tried with tilt switch. My idea was that when the tilt switch is being shaken/touched “the storm effect” (lamp blinking very fast) is enabled (visible in code #9). But after I implemented it, it wasn’t really working properly, and also moving the whole breadboard with all wires was pretty risky, so I decided that this feature won’t work great.  (photo #4)
So I removed these two, and decided to add another feature, using the second button from my kit. With the second button user would be able to control “party mode” – colors changing very fast. So, I added second button (photo #5), asked chat gpt to help me with code (code #10) and implemented the party mode on/off with the second button. This function worked great and was fun, so I decided to stick to it. 
Yet, I still wanted my lamp to have the breathing effect, as I feel like it is very cozy. So I decided to use touch sensor in order to enable breathing mode. When touch sensor is touched, the breathing mode is enabled, when it is touched again the breathing mode stops (photo #6). For the code, I used a mix of a code that we used in the class with chat gpt help. (code #11). And as that was done, I was satisfied with my lamp, and decided to leave it as it is:
1.	Button nr.1 – short press: lamp on/off, long press: change of led color
2.	Button nr. 2 – party mode on/off
3.	Potentiometer – adjusting the brightness of the lamp 
4.	Touch sensor – breathing mode on/off
I think these features make lamp interactive, with good amount of options to play with. 
### 3.	System Components ###
Hardware used:

•	Arduino Uno

•	WS2812B LED strip (60 LEDs)

•	capacitive touch sensor

•	push buttons

•	potentiometer

•	breadboard and wiring

•	3D printed cloud shell

•	cotton for light diffusion

### 4.	Electronics and Wiring ###

LED strip data → Arduino pin 3

Button 1 → pin 6

Button 2 → pin 2

Touch sensor → pin 4

Potentiometer → A0

Of course, each of these is also connected to ground and 5v. Since I didn’t have enough GND and 5V pins, I made connections from - on breadboard to gnd and from + to 5V, so then I was connecting to the gnd and 5v through + and - on my breadboard. 

### 5.	Software Development ###
For the code development, I started by downloading the FastLED library, so I can control the WS2812B LED. As far as I understood, without this library I would need to manually generate very precise data timing signals, which sounded very complicated, so this library definitely helped a lot. Thanks to it I could control many LEDs at once, adjust colors, brightness, and animation.
I also added state variables in my code, to track the current behavior of the lamp. Variables such as lampOn, partyMode, and breathingMode store the current operating state of the system. Input devices such as buttons and the touch sensor modify these variables, allowing the program to switch between different lighting modes. This structure simplifies control logic and ensures that multiple features can operate simultaneously.

**The logic of the code:**
User Input
(buttons / touch / potentiometer)
        ↓
   Arduino Uno
        ↓
 State Variables
(lampOn, partyMode, breathingMode)
        ↓
 Lighting Logic
        ↓
 FastLED Library
        ↓
 WS2812B LED Strip
 
### 6.	Physical Design ###
After the coding part was done, and I had my LED working properly, it was time to actually start designing the body of lamp. I had two ideas: first was to use 2 paper lanterns, connect them and put LED inside. But that probably wouldn’t be very stable and aesthetic, so I decided to print the body of the lamp in the 3d printer (photo #7). I decided to search and use ready project and just adjust the settings. Here is the link to the project I used: https://cults3d.com/en/3d-model/home/cloud-lamp-pbwyo3d?srsltid=AfmBOopauAGP6Rlrd1O3OovqPy6XgSI7atRFC10OZplSg_REQXQZBcEC

After the lamp body was printed (photo #8), I placed my LED strip into the lamp. It had a tape on the back side, so it was easy to just stick it to the inside of the lamp. Initially, I planned on using a baking paper/aluminum foil to get better light effect, but it turned out it wasn’t needed, and light was well distributed and bright enough without it (photo #9,10,11). Next, I used hot glue to add the cotton onto the lamp base, so the cloud effect is even better (photo #12). And my lamp was ready to be presented (photo #13).
### 7.	Challenges and Solutions ###
When working on this project I encountered some problems:

1.	The LED RGB being too small, and multiple LEDs hard to wire. But I solved it by ordering LED strip. 
2.	I struggled a bit with proper connecting of the LED to the Arduino, since I haven’t made it before, and also wasn’t sure if 5V is enough power for this LED, but with some help of youtube tutorials I was able to connect the LED successfully. 
3.	I also struggled with conceptualizing what kind of features I want to use in my lamp and how interactive I want it to be, since I had many ideas, and wanted to try different elements from the kit, but I think I managed to balance it quite well in the end. 
4.	Too many sensors – as mentioned earlier, after adding tilt switch and ultrasonic distance sensor, the lamp started to have to many functions, that were overlapping with each other, and not giving great solution, so I decided to remove these two sensors. 
5.	At first, the breathing effect coded by ChatGPT was looking very unnatural, more like the signal from ambulance than calm breathing. So I asked ChatGPT how can we change it to really soft and calm breathing and it proposed this sin-wave brightness calculation. After I implemented that, the breathing looks nice and natural. 
6.	As described above, I sometimes didn’t know how to approach coding, so then I was asking ChatGPT – for example with the breathing mode, how to make it work, or how to enable the long press to change the colors. When something wasn’t working I was either using notes from our classes, youtube tutorials, or ChatGPT to help me out. 
7.	The final challenge was to put the lamp together. I really wanted it to be aesthetic, but I had hard time with thinking about how to hide the breadboard, wiring and Arduino, when at the same time, the breadboard has to be easily accessible to control the lamp. I also couldn’t find a good 3d cloud lamp project, and didn’t know how to properly sketch it myself, so to find my final lamp body was also pretty problematic. 
8.	Final Product 
The final prototype is an interactive cloud lamp designed to create soft cozy lighting. It allows the user to interact with it in different ways. The lamp can be turned on and off, change colors, adjust brightness, and activate breathing or party mode. 
### 9.	Future Improvements ###
Ideas:
•	remote control
•	smartphone control
•	battery powered version
•	hided wiring, with just buttons and potentiometer visible and not the whole breadboard. 


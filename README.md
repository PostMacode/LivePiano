<img src= "https://i.imgur.com/iSf4pji.png">

# Implementation and How to Use

SDL, SDL_image, and SDL_mixer C++ libraries are necessary to run this program. The program simulates a 25-key MIDI keyboard, and allows you to play live music with low latency. The SDL library event handler and SDL_mixer audio library together are capable of reading user input and outputting low latency audio of relatively good quality. Notes C3 through C6 are represented with qwerty keyboard characters q-n (the m key does not do anything). The user can press 1 to switch between synthesized piano sounds and grand piano sounds. When the user makes an input, the corresponding piano key on the screen will light up. 

SDL can be found here: https://www.libsdl.org/download-2.0.php

SDL_image can be found here: https://www.libsdl.org/projects/SDL_image/

SDL_mixer can be found here: https://www.libsdl.org/projects/SDL_mixer/

All of the relevant code is in LTexture.hpp, LTexture.cpp, and main.cpp



# Project Background

I prioritized functionality over aesthetics with this project because I wanted to ensure that the program could be somewhat useful for someone. All of the live piano/MIDI keyboard programs I have tried have had between 10-40ms of audio latency, so a program would be worth using if it had less latency. I estimated that a very bare-bones C++ program using a suitable library and the right settings would be faster than the commercial programs I've tried. I downloaded the sounds used in this program from the [University of Iowa](http://theremin.music.uiowa.edu/MISpiano.html). Raw lossless files are slower than compressed files, so I converted raw aiff and flac files into compressed files; in some programs like Ableton's live MIDI program, customizing the format of the internal files they provide doesn't seem to be a provided option, so users are forced to play instruments with high latency, making playing more difficult. The SDL_mixer audio library not only loads compressed audio files very fast, but also has a built in function to set buffer size and sampling rate, which can easily be optimized for latency. On my Macbook Pro with 3.1Ghz i5 processor using default Core Audio drivers, I measured a median latency of 4.7ms from the time a key is pressed to the time that the audio plays. I took 10 samples of data using the computer's built in speakers and a CRT oscilloscope.

<img src= "https://i.imgur.com/cc3UfgY.png" width="50%" height="50%">


# Possible Future Improvements

Visually the program is not very appealing, so I think that in the future it would make sense to edit some of the graphics and also add a menu with a brief explanation on how to use the program. It would also help to add more options for sounds, instead of just a synth piano and grand piano. 

Currently, when the user inputs a key press, the corresponding piano key on the screen lights up for just one frame. It would be ideal for the key on the screen to light up for a longer time, and even stay lit if the user continues to hold down that key on the keyboard. This would require the use of different threads when manipulating the graphics, because there would need to be a delay after displaying the lit up key. When this is done with SDL_image and SDL_mixer, there isn't any way to continue playing audio during the delay time, because there are 64 different channels being used for audio, and the different threads do not know what channels the other thread is using. The solution to this according to my research online is that when dealing with graphics and audio and using multiple threads, SDL_image and [OpenGL](https://www.opengl.org) libraries have to be used together for graphics. A logical next step is for me to familiarize myself with OpenGL and use the library for multi threaded graphics. 

Another significant improvement I hope to implement in the future is support for different input devices. A program like this is much more useful if it can be used with a physical MIDI keyboard or even other instruments that one might plug into their computer. A popular library for USB input devices I've been researching online is [Gainput](http://gainput.johanneskuhlmann.de).

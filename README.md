


#  NIGHTWATCH VIDEO NAVIGATOR
## 2020 (c) Vladi Belperchinov-Shabanski "Cade"

![Nightwatch Screenshot](screenshots/nightwatch-screenshot1.jpg)

#  INTRODUCTION

NightWatch (NW) is directory browser for video media files. It has 
full keyboard access and can use single separated keypad 
(also wireless keypads) for navigation.

NW has all functions available in the main menu. However with single keypad
the regular main menu is not accessible. Because of this there is the
"keypad menu" accessible with INSERT key.

NW has Auto-Play function, which goes to the next video file and play it for the 
next 3 video files in the list with pause of 4 seconds between.
Pressing any key during the pause will cancel Auto-Play. 
Also it will be cancelled if end-of video files list reached.
   
NW shows Last-Played marker (red arrow) for the last video file played in a 
directory if more than one video file found. When entering new directory, the 
last played video file will be selected as current position in the list.
   
When changing directory to the parent directory, the current position will be 
set to the name of the last directory.

Keypad menu "Reload current directory" will re-read current directory without 
any caching.   

Nightwatch is written entirely in C++ with Qt Toolkit.

Screenshots can be found in !["docs/screenshots"](docs/screenshots) directory.

#  CREDITS

    NightWatch Video Navigator 
    (c) Vladi Belperchinov-Shabanski <cade@bis.bg> <shabanski@gmail.com>
    Github repo/site for Nightwatch: https://github.com/cade-vs/nightwatch

    "Journey" artwork 
    (c) Martina Stipan <martina.stipan@gmail.com> 
    https://www.deviantart.com/t1na

    Coolvetica Font 
    (c) Typodermic Fonts 
    https://typodermicfonts.com/coolvetica/

    Tango Icons 
    (c) Tango Project 
    http://tango-project.org/

    NightWatch created with Qt Toolkit (c) The Qt Company 
    https://qt.io/

#  LICENSE

Nightwatch is licensed under GPLv2, for full text see file "COPYING".

#  CONTACT

Questions and ideas, please, send to:

    Vladi Belperchinov-Shabanski "Cade"
    <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
    https://github.com/cade-vs
    github repo: git@github.com:cade-vs/nightwatch.git

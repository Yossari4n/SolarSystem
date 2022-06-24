# SOLAR SYSTEM
SolarSystem is rather simplistic visualization of our Solar System. Planet's position calculation are based on this [publication](https://stjarnhimlen.se/comp/ppcomp.html). On a simulation begin all planets are setup in a respect to a system time. All objects are in relative size and distance to each other, but to manage huge scale of Solar System all distances between planets has been reduced three times. By default each second of program corresponds to one day of simulation. This can be changed to respectively to 2, 4, 10 or 50 days per second.

Programmed with C++17 and modern OpenGL.


### CONTROLS 
* WSAD to move
* MOUSE to rotate
* LEFT SHIFT to move camera faster
* 0 - 8 to focus camera on object
* SCROLL to change camera's distance from observed object
* ARROWS to control time flow
* SPACE to puase/unpasue time
* TAB to change rendering mode


### SHOWCASE
![Alt text](Photo1.png?raw=true "Solar System")
![Alt text](Photo2.png?raw=true "Earth")
![Alt text](Photo3.png?raw=true "Planets")


[![Watch the video](Thumbnail.png)](https://www.youtube.com/watch?v=hU9H0ZCd1cY)


### HOW TO BUILD
    git clone https://github.com/Yossari4n/SolarSystem.git
    cd RayTracer
    mkdir build && cd build
    conan install ..
    cmake .. -G
    
To properly load resources and shaders source code make sure you have your executable path set up correctly - preferably pointing to the root of a project. Or copy 'data' and 'src/shaders' directories to your build target directory.


### SPECIAL THANKS
* 3D planet model: https://free3d.com/user/printable_models
* Planet textures: https://www.solarsystemscope.com/textures/
* Skybox texture: http://www.custommapmakers.org/skyboxes.php

# LinuxOpenGL

## Installation guide Linux

### 1. Install glfw and glad
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev

git clone https://github.com/Dav1dde/glad.git
cd glad
cmake ./
make
sudo cp -a include /usr/local/

### 2.Install dependencies
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev xorg-dev
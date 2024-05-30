# About
It's a simple project for college homework made with C++ language and `ncurses` library.
 [Video of how it's working](https://streamable.com/37qakl)
# Build
For building you need GCC or MinGW, `ncurses` library and `cmake`

To install all requirements on Arch Linux simply use one command:
```sh
sudo pacman -S gcc ncurses cmake
```
For every other OS find out by yourself.

After install all requirements, use these commands:
```sh
git clone https://github.com/VALAD47/Cafe.git && cd Cafe
cmake -B build -S .
cmake --build build --target cafe-cli
```

After successfully building project, you can find executable in `build` directory.

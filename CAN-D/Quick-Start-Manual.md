# Quick Start Manual

*Note: although this manual has been written specifically for MacOS systems, similar steps can be used for Windows or Linux systems.*

## 0. Requirements:
* CAN-D printed circuit board
* [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm) (arm-none-eabi)
* [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) for easy programming of the STM32 MCU
* [OpenOCD](http://openocd.org) (>= 0.10.0) or [texane/stlink](https://github.com/texane/stlink) for optional programming using a GDB server 
* MacOS Command Line Tools (CLT)
* [Homebrew](https://brew.sh) (package manager): recommended for installing several of the above packages

1. Install Xcode CLT. This installs necessary UNIX components such as *Make*:

```
$ xcode-select --install
```

2. Install *Homebrew*

```
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

Additional instructions can be found at [brew.sh](https://brew.sh)

3. Install the GCC Arm Embedded Toolchain:

```
$ brew install caskroom/cask/gcc-arm-embedded
$ arm-none-eabi-gcc --version
```

4. Install OpenOCD
```
$ brew install openocd
$ openOCD --version
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
```

5. Install open source [texane/stlink] (>= 1.4.0):
```
$ brew install stlink
$ st-info --version
v1.5.1
```

7. Install [STM32CubeProgrammer].

*Note: if the installer from the website doesn't work, use:*

```
$ unzip en.stm32cubeprog.zip -d en.stm32cubeprog
$ cd en.stm32cubeprog
$ java -jar SetupSTM32CubeProgrammer-1.1.0.exe
```
If the above command does not work, you could try installing `java8`:
```
$ brew tap caskroom/versions
$ brew cask install java8
```
Java 8 *should* be installed at `/Library/Java/JavaVirtualMachines/jdk1.8.xxx.jdk/`. You can then use the full java path to launch the  STM32CubeProgrammer setup.
```
$ /Library/Java/JavaVirtualMachines/jdk1.8.0_181.jdk/Contents/Home/bin/java -jar SetupSTM32CubeProgrammer-1.0.0.exe
```
**Pro Tip**: Create a symbolic link to one of the binary directory searched by your `$PATH` variable:
```
$ ln -sv /Applications/STMicroelectronics/STM32Cube/STM32CubeProgrammer/STM32CubeProgrammer.app/Contents/MacOs/bin/STM32_Programmer_CLI /usr/local/bin/
```
Then, `STM32_Programmer_CLI` can be invoked diectly without having to specify the full path:
```
$ STM32_Programmer_CLI
      -------------------------------------------------------------------
                        STM32CubeProgrammer v2.0.0                  
      -------------------------------------------------------------------


Usage : 
STM32_Programmer_CLI.exe [command_1] [Arguments_1][[command_2] [Arguments_2]...] 

Generic commands:
...
```

## 1. Get the CAN-D Project
```
$ git clone https://github.com/CAN-D/CAN-D.git
$ cd CAN-D/CAN-D/ # This is the Firwmare project directory
```
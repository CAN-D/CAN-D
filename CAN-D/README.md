# STM Project Setup Instructions

1. Install SW4STM32 (toolchain)
    * http://www.openstm32.org/Downloading%2Bthe%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Binstaller


2. Download STM32CubeMX (Project Code Creation)
    * https://www.st.com/en/development-tools/stm32cubemx.html
    * _Note: if you are on MacOS, the SetupSTM32CubeMX-5.0.1 application may not work.
if this happens, run the following command: `sudo java -jar SetupSTM32CubeMX.exe`_


3. Download OpenSTM32 (Eclipse System Workbench)
    * http://www.openstm32.org/Installing%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Bfrom%2BEclipse
    * _Note: this workbench is a series of Eclipse plug-ins, so you will first need to install the latest version of Eclipse._


4. Open STM32CubeMX and Create your Project
    * Start by selecting your MCU
    * Configure Peripherals and any middleware you would like to use (e.g. FreeRTOS)
    * **IMPORTANT**: Select **SW4STM32** under "Project Manager > Project > Toolchain/IDE"
    * Press "Generate Code" in the top right


5. Open your Project in Eclipse
    * Open Eclipse
    * Import your generated project



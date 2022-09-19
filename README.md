# STM32Watch

This is a project im currently working on, and it revolves around using an STM-32 MCU to interface with an OLED display and an RTC IC to fetch the current time and display it on the OLED. As of now, I implemented a very crude form of the program - later updates will make the routines more 'state-machine' like.

I designed the PCB myself using Altium Designer, and I've uploaded the schematics too. The board is designed to take a 3.7V input for power, and uses it to power the STM-32 and the logic of the OLED after passing it through an LDO voltage regulator. As for supplying the voltage of the OLED itself, I designed some power electronics, specifically a boost converter to take 3.7V up to 14V.

The OLED display communicates using SPI - I created my own functions/libraries to interface with the OLED via SPI (with the help of STM32's HAL).
The RTC IC communcates using I2C - This was pretty straightforward using the STM32 HAL.

Here are some pictures:

![image1](https://user-images.githubusercontent.com/71983579/190934295-30bffb4d-c075-4cf8-8a95-91360dd1e502.jpeg)




![image0](https://user-images.githubusercontent.com/71983579/190934296-ee6281af-3761-43ae-a8af-36d61408d4f8.jpeg)



As this is a work-in-progress, I've added the header pins to access some the STM32's pins in case I want to add things (which I am planning on doing).

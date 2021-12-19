# CLOCK MODULE
The clock module is a small form factor product with a screen to indicate time and buttons to turn the LEDs on and off. One is able to update time, date and day displayed depending on your time_zone by use of a single buttons thanks to efficiently designed firmware.The product is powered by a single non-rechargeable coin cell battery ensuring a small and efficient form factor.

![WhatsApp Image 2021-12-19 at 5 09 21 AM](https://user-images.githubusercontent.com/85989401/146666220-9c076c63-bdca-4207-948f-92d210eb038a.jpeg)

### How it works 🔧
        
The LOGO button is used to wake the chip from sleep and set time.
When pressed, the board wakes up and displays the current time, date and day for 30seconds then it goes to sleep once more

#### Setting time 🕙

when the borad is active:
1. LONG PRESSING (1second press) the logo button makes the board to go to time setting mode which allows one to set the time.
2. SINGLE PRESS (press then release) increments the variable you wamt to set by one until the maximum and then it goes back to zero and repeats
3. DOUBLE PRESS (pressing two times in relatively fast succession) allows one to change from one variable to the other(from sec to Min.......)
4. LONG PRESSING AGAIN - exits the time setting mode

the current time will be updated with the time just set and displayed on the screen

# Download the Files : arrow_down_small:
From this repo click on the download option at the code :arrow_double_down: 
- You will have two folders inside the main folder i.e 📁 Bootloader and  📁clock_module_code
# Burning bootload to the MCU :fire:
  <h3> Note: 
 DO THIS ON A WINDOWS OPERATING SYSTEM!!!
  </h3>
1) To do this you will need an older version of the arduino particularly version 1.6.9 find it here :link: [Old SoftwareReleases Arduino IDE](https://www.arduino.cc/en/main/OldSoftwareReleases) <br/>
2) Once you have it setup to burn the bootloader follow this tutotial keenly:link: [Burning Arduino Bootloader](https://create.arduino.cc/projecthub/techmirtz/arduino-without-external-clock-crystal-on-atmega328-d4fcc4) 
3) You can also use a USBASP to burn the bootloader. Note the above instruction will be used but instead of selecting arduino as ISP your programmer the USBASP is selected. 

![image](https://user-images.githubusercontent.com/85989401/146667082-94dd6fc7-de50-4675-a084-ad729f834af0.png)

[buy usbasp](https://aliexpress.ru/af/USBASP-USBISP-AVR-Programmer-USB.html?catId=0&d=y&aff_platform=portals-tool&initiative_id=SB_20201020044645&origin=n&sk=_9JHld5&aff_trace_key=4b1704d992da43b586041dfb7cd31d7e-1606574782769-00350-_9JHld5&SearchText=USBASP%2BUSBISP%2BAVR%2BProgrammer%2BUSB&terminal_id=351d58321dfa473cb106b58978d7c19c)
or here 
 :link: [buy usbasp](https://aliexpress.ru/item/32649685244.html?spm=a2g0o.productlist.0.0.22e26eaf2mIeLt&algo_pvid=b6506204-320d-4244-9d76-c7a1c32c5ee5&algo_expid=b6506204-320d-4244-9d76-c7a1c32c5ee5-16&btsid=0b8b036a16065747853274219e2939&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
 <br/>
 
# Uploading the codes  :arrow_up:
1) Open the 📁clock_module_code Folder and open the INO file with your arduino
2) If you use Arduino as your programmer or an FTDI, Follow the instructions here from step 3: [Uploading Code](https://create.arduino.cc/projecthub/techmirtz/arduino-without-external-clock-crystal-on-atmega328-d4fcc4)
3) However if you are using a USBASP, Follow the following instructions:
   a) Insert the ISP programmer cable socket onto ISP header. ...<br>
   b) Open Arduino IDE software. ...<br>
   c) Next, call out any example of source code. ...<br>
   d) Select “USBasp” from the Tools > Programmer menu.<br>
   e) Select “Upload using Programmer” from the File menu.<br>
 You can also explore more from the following tutorial :link:[How to Use USBasp Programmer with Arduino Boards](https://www.youtube.com/watch?v=ToKerwRR-70)
 

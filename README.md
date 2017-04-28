<img align="right" src="Logo.png"/>

# Notos

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/01772fe49d4c452887582b17bea2e4c0)](https://www.codacy.com/app/Xasin/Notos?utm_source=github.com&utm_medium=referral&utm_content=XasWorks/Notos&utm_campaign=badger)

Public repository of the Notos robot project of the [Kolleg St. Thomas][kst] robotics group, competing in the 2016/2017 RoboCup Junior Line Secondary competition.

[kst]:http://www.kolleg-st-thomas.de

[![Autodesk Render][a360render]](http://a360.co/2o4hNXv)

[a360render]:https://raas-render-prod.s3.amazonaws.com/4X94RSB8UWMK/032a44cb-500d-4c63-8523-b9808dced95d/gallery.0.jpg?AWSAccessKeyId=AKIAITZA7W7GF2PHDUIA&Expires=1493482261&response-cache-control=public%2C%20max-age%3D86400&response-expires=Sat%2C%2029%20Apr%202017%2016%3A11%3A01%20GMT&Signature=a5WDxJ9cIiIUDjMGTwVzO8Sr1yc%3D

----------

# Features
Notos was built mainly with DIY-capability in mind. All components can be printed out with a home 3D printer of normal size, and can be easily bought or soldered at home. The total costs lay beneath 100€

- AVR-Based MCU (ATMega32 and ATMega328P)
- NEMA 14 stepper motors for both precision and power
- Completely 3D printed chassis with sturdy screw-connections
	- This even includes the belts themselves! (Flexible material printing capabilities required though)
- Completely open-source code and design, for everyone to work with
- Simple "stacking" design for sensor mounts, PCBs and other attachments, allowing for a great deal of flexibility.

# History
Notos was started in the late summer of 2016, by DIY-enthusiast David Bailey.
After his mildly successfull run with his first robot [Zephyr][zephyrRepo], awarding him the 20th place in the german-open championship in the RoboCup Line Secondary contest in 2016, he applied his newfound knowledge to build something more suitable for the contest.
As a name, it was only fitting to continue Zephyr's legacy by choosing another greek god of the wind: **Notos**

[zephyrRepo]:https://www.github.com/XasWorks/Hexa-Bot

# Development
To overcome the problems that the old robot Zephyr had, a lot of the elements had to be replaced, and a complete redesign was necessary. This design process began in the late summer of 2016, maintaining many of the features that made Zephyr successfull, while swapping out the bad parts. The AVR-MCU and stepper motor drive system had been kept, while chassis and omniwheel-design were traded in for a much sturdier and compacter design, as well as more reliable, self-printed belts.

As of now the development still continues, as only over time differet features, flaws, and ideas come apparent.

---

# Prerequisites
- Using the OpenSCAD models here requires having the [XasCode Library][XasCode] next to this (the Notos) repository, as the Tagging.scad function is used.
	Later on the AVR libraries of that repository will also be used, so it is recommended to clone it completely!
- To properly work with the AVR Code, it is recommended to install the [AVR-Plugin for eclipse][avrplug] (for C and C++ eclipse versions)
	The current workspace is in EclipseWS. Eclipse should auto-detect the projects, if not, use the "import C++ project" function and import the project folders inside EclipseWS


[avrplug]:http://avr-eclipse.sourceforge.net/wiki/index.php/The_AVR_Eclipse_Plugin
[XasCode]:https://www.github.com/XasWorks/XasCode

# Project Nyx
Project Nyx, the successor to Project 250.

To launch (Spring or Summer) 2018.

Bugs: Don't run setup.sh in cron, for some reason the files won't get saved. Are subsequent cron commands forking early?

Todo:
  - Improve/degrade video quality
      - Mode 1 : 247 mA
      - Mode 2 : 
      - Mode 3 : Same as 2
      - Mode 4 : 
      - Mode 5 : 228 mA
      - Mode 6 : 226 mA
      - Mode 7 : 200 mA
  - Improve battery life
      - Disabled BT
      - Disabled wifi after 2* minutes (adjustable depending on OS)
      - Disabled HDMI
      - (maybe turn off the LED?)
      
Parts:
  - Raspberry Pi Zero W
    - Running latest version of Raspbian Jessie Lite with update (no dist-upgrade)
  - Raspberry Pi Camera v2.1
  - 2,000 mAh Lithium Polymer Ion Battery
  - Tracksoar Open-Source APRS Tracker
  - 2 Ultimate Lithium AA Batteries
  - 3D Printed Frame

Code written by Logan Grosz

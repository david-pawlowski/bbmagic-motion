I bought sensor here(slot for battery and battery is not included):
https://botland.store/bbmagic-bluetooth-automation/15522-bbmagic-motion-wireless-pir-sensor-5904422363130.html

I found initial version of this software here:
http://bbmagic.net/do-pobrania/
Refactored it to minimal code for object detection with saving output to file.

I am using this script on **raspberry pi zero w**

Compile by:
```bash
make all
```
Then(sudo might be needed):
```bash
./bbmagic_motion_sketch
```

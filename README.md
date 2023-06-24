# Digital Alarm Clock with Dot Matrix display

## Part of Embedded Systems Course
A month long final project 

### Features
1. Real time clock, Calendar, Temperature display
    - if clock is wrong, it can be configured with PS/2 Keyboard
2. Alarms,
    - Can be configured with PS/2 Keyboard to,
      - set when alarms start/end
      - set text to display when an alarm starts
    - Alarm types:
      - alarm-1 and alarm-2, will output hardcoded defined text into Dot Matrix display
      - alarm-3, will output text from PS/2 Keyboard input into Dot Matrix Display
3. Dot Matrix Display will change brightness according to surroundings,
    - if surrounding is bright, brightness is bright
    - if surrounding is not bright, brightness is dimmed

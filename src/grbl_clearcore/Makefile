ino = $(wildcard *.ino)
sketch = main

bin:
	arduino-cli compile -v -b ClearCore:sam:clearcore --build-path /tmp/build

flash:
	@ openocd -f clearcore.cfg -c "program /tmp/build/$(sketch).bin verify reset 0x4000;shutdown"

reset:
	@ openocd -f clearcore.cfg -c "init;reset;shutdown"

debug:
	@ openocd -f clearcore-debug.cfg -c "program /tmp/build/$(sketch).bin verify 0x4000"

clean:
	@ rm -rf /tmp/build
	@ rm -rf /tmp/arduino-core-cache/

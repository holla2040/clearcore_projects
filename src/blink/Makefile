ino = $(wildcard *.ino)
sketch = $(shell basename `pwd`).ino

bin:
	arduino-cli compile -b ClearCore:sam:clearcore --build-path /tmp/build
	

flash:
	@ openocd -f clearcore.cfg -c "program /tmp/build/$(sketch).bin verify reset 0x4000;shutdown"

reset:
	@ openocd -f clearcore.cfg -c "init;reset;shutdown"

clean:
	@ rm -rf /tmp/build

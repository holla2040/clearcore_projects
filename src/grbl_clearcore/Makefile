ino = $(wildcard *.ino)
sketch = $(shell basename `pwd`).ino

bin:
	arduino-cli compile -b ClearCore:sam:clearcore --build-path /tmp/build

flash:
	@ openocd -f clearcore.cfg -c "program /tmp/build/$(sketch).bin verify reset 0x4000;shutdown"

reset:
	@ openocd -f clearcore.cfg -c "init;reset;shutdown"

serve:
	@ openocd -f clearcore-debug.cfg -c "program /tmp/build/$(sketch).bin verify 0x4000"

debug:
	@ gdb /tmp/build/$(sketch).elf

watch:
	@ while [ 1 ]; do clear;make; sleep 1; inotifywait -e modify *.c *.h *.ino; done

clean:
	@ rm -rf /tmp/build

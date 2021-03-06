@echo off

set name="main"

set path=%path%;..\bin\

set CC65_HOME=..\

cc65 -Oi %name%.c --add-source
ca65 reset.s
ca65 %name%.s
ca65 asm.s

ld65 -C nes.cfg -o %name%.nes reset.o %name%.o asm.o nes.lib

del *.o main.s

pause

%name%.nes

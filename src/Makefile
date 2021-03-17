TARGET	= gu3000.a
OBJ	= gu3000graphic.o gu3000gpio.o framebuffer.o font.o gu3000normal.o
DEPENDFILE = depends.d

#CFLAGS	= -Wall -g3
CFLAGS	= -Wall

CC	= g++ $(CFLAGS)

all: $(OBJ) $(TARGET)

$(TARGET): $(OBJ)
	ar rc $@ $^

.cpp.o:
	$(CC) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ) $(DEPENDFILE)

depend:
	for i in *.cpp; do $(CC) -MM $$i; done > $(DEPENDFILE)

font.o: font.cpp font.h fonts/16segments_font.h fonts/4x6_font.h \
 fonts/H68TR_font.h fonts/MICRlike6x6_font.h fonts/MICRlike7x8_font.h \
 fonts/Noritake6x8_font.h fonts/TK80BS_font.h fonts/TK80BS_JIS_font.h \
 fonts/TK80BS_ASCII_font.h fonts/TK80BS_KANA_font.h \
 fonts/TK80BS_GREEK_font.h
framebuffer.o: framebuffer.cpp framebuffer.h font.h
gu3000graphic.o: gu3000graphic.cpp gu3000graphic.h gu3000gpio.h \
 gu3000common.h framebuffer.h font.h
gu3000normal.o: gu3000normal.cpp gu3000normal.h gu3000gpio.h \
 gu3000common.h framebuffer.h font.h
gu3000gpio.o: gu3000gpio.cpp gu3000gpio.h gu3000common.h

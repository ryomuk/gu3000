SUBDIRS = brightness clear font2txt fonttest \
	hello lifegame playbmp showbmp \
	showfb showwire test viewtxt

all: $(SUBDIRS)

clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean $(SUBDIRS)

SUBDIRS = clear lifegame power showbmp test testcommand

all: $(SUBDIRS)

clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all clean $(SUBDIRS)

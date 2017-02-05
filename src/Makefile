BIN=jcp
PREFIX?=~/.local

OBJS=$(patsubst %.c, %.c.o, $(wildcard *.c))
CFLAGS=-w `pkg-config --cflags glib-2.0 json-glib-1.0`
LDFLAGS=`pkg-config --libs glib-2.0 json-glib-1.0`
INSTALL=`which install` -c

$(BIN) : $(OBJS)
	@echo CC $@
	@$(CC) -o $@ $^ $(LDFLAGS)

%.c.o : %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -o $@ -c $^

CLEAN_OBJS=$(OBJS:%=clean-%) $(BIN:%=clean-%)

.PHONY : clean

clean : $(CLEAN_OBJS)

$(CLEAN_OBJS) :
	@echo RM $(@:clean-%=%)
	@$(RM) $(@:clean-%=%)

.PHONY : install

install : $(BIN)
	@echo INSTALL $^
	@$(INSTALL) $^ $(PREFIX)/bin/$^

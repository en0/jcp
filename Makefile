PREFIX?=~/.local
SRCDIR=./src
_MAKE=$(MAKE) --no-print-directory -C $(SRCDIR)

## Build

.PHONY : all
.PHONY : clean
.PHONY : install

all : FORCE
	@$(_MAKE)

install : FORCE
	@$(_MAKE) install PREFIX=$(PREFIX)

clean : FORCE
	@$(_MAKE) clean

FORCE:

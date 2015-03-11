# -*- Makefile -*-

#
# step #1 - system specific compilers, setttings etc
#

OSTYPE := $(shell uname -s)

#
#
#

ifeq ($(CONFIG),) # not defined

include build/GNUmakefile.config # default is debug

endif


#
# external libraries
#

LOCAL_INCLUDE =

#
# utilities
#

ECHO := /bin/echo

#
# defines
#

DEFS  :=

#
# compiler flags, dependncy generation and implicit build rules
#

-include build/GNUmakefile.compiler
-include build/GNUmakefile.ABI
-include build/GNUmakefile.depends
-include build/GNUmakefile.rules

#
# sources, objects and targets
#
# object files - done by string substitution
#

SRCS_SPECTR := main.cpp Spectrum.cpp
OBJS_SPECTR := $(addsuffix .o, $(basename $(SRCS_SPECTR)))	
DEPS_SPECTR := $(addsuffix .d, $(basename $(SRCS_SPECTR)))

OBJS := $(OBJS_SPECTR)
DEPS := $(DEPS_SPECTR)

# all targets

SPECTR := spectr

.PHONY: all tags dox clean realclean

all: $(SPECTR)

$(SPECTR): $(OBJS_SPECTR)
	$(LD) $(LDFLAGS) -o $@ $(wordlist 1,10000000,$^) -L/usr/local/lib $(SYSLIB)	

#dependencies
-include $(DEPS)

tags:
	@(find . -name "*.h" -print | etags -)
	@(find . -name "*.cpp" -print | etags -a -)
	@(find . -name "*.cc" -print | etags -a -)
	@/bin/echo "TAGS updated"

dox:
	doxygen

clean:
	-rm -rf $(SPECTR)
	-rm -rf $(OBJS)

realclean:
	-rm -rf $(SPECTR)
	-rm -rf $(OBJS)
	-rm -rf $(DEPS)
	-rm -rf TAGS

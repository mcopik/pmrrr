include ./make.inc

DIRS = ./INCLUDE ./SRC ./SRC/LAPACK ./SRC/BLAS

CFLAGS += -I./INCLUDE
CPPFLAGS += $(CFLAGS)

ifeq ($(SPINLOCK_SUPPORT),0)
 CFLAGS += -DNOSPINLOCKS
endif

# Source files
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))

#CPPSRCS   := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
#CPPOBJS = $(CPPSRCS:.cpp=.o)

CSRCS   := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))
COBJS = $(CSRCS:.c=.o)


FSRCS  := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.f))
FOBJS = $(FSRCS:.f=.o)


# Build target #
#libpmrrr.a: $(COBJS) $(CPPOBJS) $(FOBJS) $(HEADERS)
#	    $(AR) $(ARFLAGS) ./LIB/libpmrrr.a $(COBJS) $(CPPOBJS) $(FOBJS)
libpmrrr.a: $(COBJS) $(FOBJS) $(HEADERS)
	    $(AR) $(ARFLAGS) ./LIB/libpmrrr.a $(COBJS) $(FOBJS)

$(COBJS): $(HEADERS)
#$(CPPOBJS): $(HEADERS)
$(FOBJS):

.PHONY: clean
clean:
	rm -f *~ core.* *__genmod* \
        ./INSTALL/*~ \
        $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.o)) \
        $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*~)) \
        $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.mod.*)) \
        $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*__genmod*))
        

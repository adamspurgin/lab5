TARGETS         = mipsim
SRCS            = classify.cc execute_unfinished.cc main.cc mipsim_unfinished.cc parse.cc
HEADERS         = mipsim.hpp
OBJS            = $(SRCS:.cc=.o)
srcdir          = .
INCLUDES	= -I$(srcdir)
CXXFLAGS          = -g
# CXXFLAGS        = -O3
LDFLAGS		= 
LIBS		= -lstdc++

# DEPEND		= makedepend
# DEPEND_FLAGS	= 
# DEPEND_DEFINES	= 


default: $(TARGETS)

all: default

$(TARGETS): $(OBJS) $(HEADERS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:  
	-rm -f *.o $(TARGETS)

# depend:
# 	$(DEPEND) -s '# DO NOT DELETE: updated by make depend'		   \
# 	$(DEPEND_FLAGS) -- $(INCLUDES) $(DEFS) $(DEPEND_DEFINES) $(CFLAGS) \
# 	-- $(SRCS)

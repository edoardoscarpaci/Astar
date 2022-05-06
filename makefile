BUILDDIR = build
CC = gcc
CFLAGS  = -g -Wall
LDLIBS += -lOpenCL -lopencv_core -lopencv_videoio -lopencv_highgui -lstdc++ -lopencv_imgcodecs -lopencv_imgproc
SOURCEDIR = src
HEADERDIR = -Iinclude -I/usr/local/include/opencv4/
PROG = Astar
LD = gcc

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(addprefix $(BUILDDIR)/,$(SOURCES:src/%.cpp=%.o))

$(info $$SOURCES is [${SOURCES}])
$(info $$OBJECTS is [${OBJECTS}])


all: $(BUILDDIR)/$(PROG)

$(BUILDDIR)/$(PROG): $(OBJECTS)
	$(LD) $(LDFLAGS)  $(OBJECTS)  -o $(BUILDDIR)/$(PROG) $(LDLIBS)

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LDLIBS) $(HEADERDIR) -c $< -o $@




    




EXEC := PhysicsGame

DIRSRC := src/
DIROBJ := obj/
DIRHEA := include/

SUBDIRHEA := $(shell ls -p $(DIRHEA) | grep /)

CXX := g++

# Compiling flags --------------------------------------------------------------
CXXFLAGS := $(addprefix -I$(DIRHEA), $(SUBDIRHEA))
CXXFLAGS += -Wall -I/usr/local/include/cegui-0/CEGUI -I/usr/local/include/cegui-0 `pkg-config --cflags OGRE OGRE-Overlay` -std=c++11 `pkg-config --cflags OIS`

# Linker flags -----------------------------------------------------------------
LDFLAGS := `pkg-config --libs-only-L OGRE` -lOIS -lGL -lstdc++ -lboost_system  -lCEGUIBase-0 -lCEGUIOgreRenderer-0
LDLIBS := `pkg-config --libs-only-l OGRE OGRE-Overlay SDL2_mixer` -lboost_system -lOIS -lGL -lstdc++ -lCEGUIBase-0 -lCEGUIOgreRenderer-0

# Compiling mode (-mode=release -mode=debug) -----------------------------------
ifeq ($(mode), release)
	CXXFLAGS += -O2 -D_RELEASE
else
	CXXFLAGS += -g -D_DEBUG
	mode := debug
endif

ALL_CPP := $(shell find $(DIRSRC)* -name "*.cpp" -exec basename {} \;)
ALL_OBJ := $(patsubst %.cpp, %.o, $(ALL_CPP))
OBJS    := $(addprefix $(DIROBJ), $(ALL_OBJ))

.PHONY: all clean

all: dir $(EXEC)
	./$(EXEC)

debug: dir $(EXEC)
	gdb -ex run ./$(EXEC)

info:
	@echo '------------------------------------------------------'
	@echo '>>> Using mode $(mode)'
	@echo '    (Call "make" with [mode=debug|release])  '
	@echo '------------------------------------------------------'

# Linking ----------------------------------------------------------------------
$(EXEC): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compiling --------------------------------------------------------------------
# Main
$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS)

# Subdirectories
$(DIROBJ)%.o: $(DIRSRC)*/*%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS)

# Temporals cleaning -----------------------------------------------------------
clean:
	$(RM) -r *.log $(EXEC) *~ $(DIROBJ) $(DIRSRC)*~ $(DIRHEA)*~ ./core
	@find . -name 'scene.scene' -exec rm -vf {} \;

dir:
	@mkdir -p obj/

edit:
	atom .

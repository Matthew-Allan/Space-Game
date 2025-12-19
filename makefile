# Program info.
PROG_NAME := SpaceGame
PROG_NAME_LC  := $(shell echo $(PROG_NAME) | tr A-Z a-z)

PROG_VER := 0.0
BUNDLE_VER := 1

BUNDLE_ID := com.suityourselfgames.$(PROG_NAME_LC)

# Folder structure.
OUT := out
ASSETS := assets
SHADERS := $(ASSETS)/shaders
MODELS := $(ASSETS)/models
PROG_LOC := $(OUT)/$(PROG_NAME)
SOURCE_ICON := $(ASSETS)/Icon1024.png

# Source files / arguments.
CORE_FILES := camera files matrix program quaternion shader transform vector vaos wfobj
APP_FILES := beltshad main objectshad ship
FILES := $(foreach file,$(APP_FILES) $(foreach core_file,$(CORE_FILES), core/$(core_file)) glad/glad, src/$(file).c)
GEN_ARGS := -fdiagnostics-color=always -g -Wall -Werror -Iinclude -lSDL2

#OS specifics.
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)

# General vals.
OS := MAC
ARGS := $(GEN_ARGS) -framework CoreFoundation

# .app package folders.
APP := $(OUT)/$(PROG_NAME).app
APP_CONTENTS := $(APP)/Contents
APP_RESOURCES := $(APP_CONTENTS)/Resources
APP_FRAMEWORKS := $(APP_CONTENTS)/Frameworks
APP_MAC_OS := $(APP_CONTENTS)/MacOS

# Icon vals.
ICON_NAME := Icon
ICON_SET := $(ICON_NAME).iconset
ICON := $(ICON_NAME).icns

# Substitutions for Info.plist.
SUBS := -e 's:PROG_NAME:$(PROG_NAME):' -e 's:BUNDLE_ID:$(BUNDLE_ID):' -e 's:BUNDLE_VER:$(BUNDLE_VER):' -e 's:PROG_VER:$(PROG_VER):' -e 's:ICON_FILE:$(ICON):'

else ifeq ($(OS),Windows_NT)

# General vals.
OS := WIN
ARGS := $(GEN_ARGS) -LWindows/lib

else

$(error "Unsupported Operating system");

endif

# Build and run the executable.
all: build run
	echo $(BUNDLE_ID)

# Build the executable.
build: clean
	mkdir -p $(OUT)
	ln -sf ../assets/shaders $(OUT)/
	ln -sf ../assets/models $(OUT)/
ifeq ($(OS),WIN)
	cp Windows/SDL2.dll $(OUT)/SDL2.dll
endif
	gcc $(FILES) $(ARGS) -o $(PROG_LOC)

# Run the program.
run:
	./$(PROG_LOC)

# Clean any files that may have been created on build.
clean:
	rm -fr $(OUT)

# Create a .app package.
mac: clean build
#Create the required directories.
	mkdir -p $(APP_RESOURCES)
	mkdir $(APP_MAC_OS)
	mkdir $(APP_FRAMEWORKS)

# Place files in the package.
	cp MacOS/libSDL2-2.0.0.dylib $(APP_FRAMEWORKS)/libSDL2-2.0.0.dylib
	cp MacOS/Info.plist $(APP_CONTENTS)/Info.plist
	sed $(SUBS) MacOS/Info.plist > $(APP_CONTENTS)/Info.plist
	cp MacOS/Icon.icns $(APP_RESOURCES)/$(ICON)
	cp -R $(SHADERS) $(APP_RESOURCES)/shaders
	cp -R $(MODELS) $(APP_RESOURCES)/models
	cp $(PROG_LOC) $(APP_MAC_OS)/$(PROG_NAME)

# Set the program to look in the apps frameworks instead of the pcs frameworks.
# Probably weird and not suggested :/. Only an issue if it doesn't work on another computer.
	install_name_tool -change $(shell brew --prefix sdl2)/lib/libSDL2-2.0.0.dylib @executable_path/../Frameworks/libSDL2-2.0.0.dylib $(APP_MAC_OS)/$(PROG_NAME)

# Create and zip a .app package.
mac_zip: mac
	zip -r $(PROG_LOC).app.zip $(PROG_LOC).app

# Create icons from a file named Icon1024.png that is 1024x1024 pixels.
icns:
	mkdir $(ICON_SET)
	sips -z 16 16     $(SOURCE_ICON) --out $(ICON_SET)/icon_16x16.png
	sips -z 32 32     $(SOURCE_ICON) --out $(ICON_SET)/icon_16x16@2x.png
	sips -z 32 32     $(SOURCE_ICON) --out $(ICON_SET)/icon_32x32.png
	sips -z 64 64     $(SOURCE_ICON) --out $(ICON_SET)/icon_32x32@2x.png
	sips -z 128 128   $(SOURCE_ICON) --out $(ICON_SET)/icon_128x128.png
	sips -z 256 256   $(SOURCE_ICON) --out $(ICON_SET)/icon_128x128@2x.png
	sips -z 256 256   $(SOURCE_ICON) --out $(ICON_SET)/icon_256x256.png
	sips -z 512 512   $(SOURCE_ICON) --out $(ICON_SET)/icon_256x256@2x.png
	sips -z 512 512   $(SOURCE_ICON) --out $(ICON_SET)/icon_512x512.png
	cp $(SOURCE_ICON) $(ICON_SET)/icon_512x512@2x.png
	iconutil -c icns $(ICON_SET) -o MacOS/$(ICON)
	rm -r $(ICON_SET)
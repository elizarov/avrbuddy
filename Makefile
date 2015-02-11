
CPPSRC = test/TestPorts.cpp

MCU    = atmega328p
F_CPU  = 16000000
OBJDIR = build

# Same basic parameters that Arduino 1.6.0 uses
CPPFLAGS += -std=c++11 # will have to be added to Arduino
CPPFLAGS += -DF_CPU=$(F_CPU)UL
CPPFLAGS += -Os
CPPFLAGS += -g
CPPFLAGS += -fno-exceptions 
CPPFLAGS += -ffunction-sections 
CPPFLAGS += -fdata-sections 
CPPFLAGS += -fno-threadsafe-statics
CPPFLAGS += -fno-exceptions
CPPFLAGS += -Wall
CPPFLAGS += -Wundef
CPPFLAGS += -Wa,-adhlns=$(<:%.cpp=$(OBJDIR)/%.lst)

#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
LDFLAGS += -Wl,--relax

#============================================================================

# Define programs and commands.
CC = avr-gcc
OBJDUMP = avr-objdump

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MMD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CPPFLAGS = -mmcu=$(MCU) -I. -x c++ $(CPPFLAGS) $(GENDEPFLAGS)

# Default target.
all: mkdirs elf lss

elf: $(CPPSRC:%.cpp=$(OBJDIR)/%.elf)
lss: $(CPPSRC:%.cpp=$(OBJDIR)/%.lss)

# Create extended listing file from ELF output file.
%.lss: %.elf
	$(OBJDUMP) -h -S -z $< > $@

# Link: create ELF output file from object files.
%.elf: %.o
	$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)

# Compile: create object files from C++ source files.
$(OBJDIR)/%.o: %.cpp
	$(CC) -c $(ALL_CPPFLAGS) $< -o $@ 

# Create object files directories
mkdirs:
	$(shell mkdir $(OBJDIR)         2>/dev/null)
	$(shell mkdir $(OBJDIR)/io      2>/dev/null)
	$(shell mkdir $(OBJDIR)/test    2>/dev/null)

# Remove stuff
clean:
	$(shell rm -rf $(OBJDIR))
	$(shell rm -rf .dep)

# Listing of phony targets.
.PHONY: all els lss clean

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

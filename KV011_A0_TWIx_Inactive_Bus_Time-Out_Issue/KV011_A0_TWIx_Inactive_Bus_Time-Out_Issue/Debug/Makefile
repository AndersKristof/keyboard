################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf

OUTPUT_FILE_PATH_AS_ARGS +=KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.46
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.46\bin\xc8-cc.exe$(QUOTE)  -mcpu=AVR32SD32  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\AVR-Sx_ENG_DFP\1.0.22\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__AVR32SD32__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.46
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.46\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=AVR32SD32  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\AVR-Sx_ENG_DFP\1.0.22\xc8"  -Wl,-Map="KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"C:\Program Files\Microchip\xc8\v2.46\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.hex"
	"C:\Program Files\Microchip\xc8\v2.46\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.eep" || exit 0
	"C:\Program Files\Microchip\xc8\v2.46\bin\avr-objdump.exe" -h -S "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf" > "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.elf" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.hex" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.eep" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.map" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.usersignatures" "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.a"  "KV011_A0_TWIx_Inactive_Bus_Time-Out_Issue.lss"
	
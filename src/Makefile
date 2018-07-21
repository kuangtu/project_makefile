-include ../Make.defines

###文档模板来自于
###通过对该模板进行修改
###（1）提出gcc、编译选项到Make.defines
###（2）增加外部静态库
###（3）可以编译多个二进制生成程序
#### PROJECT SETTINGS ####
# The name of the executable to be created
BIN_NAME := project_makefile
# Extension of source files used in the project
SRC_EXT = c
# Path to the source directory, relative to the makefile
SRC_PATH = .
# Add additional include paths
INCLUDES = -I $(SRC_PATH)
# General linker settings
LINK_FLAGS =-lpthread
# Additional release-specific linker settings
RLINK_FLAGS =
# Additional debug-specific linker settings
DLINK_FLAGS =
# Destination directory, like a jail or mounted system
DESTDIR = /
#### END PROJECT SETTINGS ####

# Optionally you may move the section above to a separate config.mk file, and
# uncomment the line below
# include config.mk

# Generally should not need to edit below this line

# Shell used in this makefile
# bash is used for 'echo -en'
SHELL = /bin/bash
# Clear built-in rules
.SUFFIXES:
# Programs for installation
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644


# Build and output paths
release: export BIN_PATH := ../bin

# Find all source files in the source directory, sorted by most
# recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
						| sort -k 1nr | cut -f2-)

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
# 将文件.c替换为.o
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(SRC_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
# 将.o文件替换为.d依赖文件，赋给DEPS
DEPS = $(OBJECTS:.o=.d)


# Standard, non-optimized release build
# .PHONY定义一个伪目标，make命令执行默认从release开始执行
# 先执行dirs目标，即建立build和bin目录
# （1）然后显示Beginning release build
# （2）然后make all 
# （3）基于all目标，编译.o
.PHONY: release
release: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning release build v$(VERSION_STRING)"
else
	@echo "Beginning release build"
endif
	@echo "step2"
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Debug build for gdb debugging
.PHONY: debug
debug: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning debug build v$(VERSION_STRING)"
else
	@echo "Beginning debug build"
endif
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Create the directories used in the build
.PHONY: dirs
dirs:
	@echo $(SOURCES)
	@echo "step1"
	@echo "Creating directories"
	@mkdir -p $(BIN_PATH)


# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r ../bin
	@$(RM) *.o *.d

# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "step5"
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Link the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "step4"
	@echo "Linking: $@"
	@$(START_TIME)
	$(CC) $(OBJECTS) $(LDFLAGS) ${THRD_LIB_PATH} -o $@
	@echo -en "\t Link time: "
	@$(END_TIME)

# Add dependency files, if they exist
# 增加依赖文件
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
#　@不回显命令
# @echo ${OBJECTS}
# @echo ${DEPS}
$(SRC_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "step3"
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_FLAGS) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)

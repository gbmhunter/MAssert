#
# @file 			Makefile
# @author 			Geoffrey Hunter <gbmhunter@gmail.com> (wwww.mbedded.ninja)
# @edited 			n/a
# @created			2014-08-19
# @last-modified 	2014-09-12
# @brief 			Makefile for Linux-based make, to compile the MAssert-Cpp library, example code and run unit test code.
# @details
#					See README in repo root dir for more info.

SRC_CC := g++
SRC_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRC_LD_FLAGS :=
SRC_CC_FLAGS := -Wall -g -c  -I. -I./lib -std=c++0x

TEST_CC := g++
TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard test/*.cpp))
TEST_LD_FLAGS := 
TEST_CC_FLAGS := -Wall -g -c  -I. -I./lib -std=c++0x

EXAMPLE_CC := g++
EXAMPLE_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard example/*.cpp))
EXAMPLE_LD_FLAGS := 
EXAMPLE_CC_FLAGS := -Wall -g -c -I. -I./lib -std=c++0x

DEP_LIB_PATHS := -L ../MUnitTest
DEP_LIBS := -l MUnitTest
DEP_INCLUDE_PATHS := -I../

.PHONY: depend clean

# All
all: src test
	
	# Run unit tests:
	@./test/Tests.elf

#======== MAssertCpp LIB ==========#

src : $(SRC_OBJ_FILES) | deps
	# Make library
	ar r libMAssert.a $(SRC_OBJ_FILES)
	
# Generic rule for src object files
src/%.o: src/%.cpp
	# Compiling src/ files
	$(SRC_CC) $(SRC_CC_FLAGS) $(DEP_INCLUDE_PATHS) -MD -o $@ $<
	-@cp $*.d $*.P >/dev/null 2>&1; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d >/dev/null 2>&1

-include $(SRC_OBJ_FILES:.o=.d)

# ======== DEPENDENCIES ========

deps:
	if [ ! -d ../MUnitTest ]; then \
	git clone https://github.com/mbedded-ninja/MUnitTest ../MUnitTest; \
	fi;
	$(MAKE) -C ../MUnitTest/ all
	
	
# ======== TEST ========
	
# Compiles unit test code
test : $(TEST_OBJ_FILES) | src deps
	# Compiling unit test code
	g++ $(TEST_LD_FLAGS) -o ./test/Tests.elf $(TEST_OBJ_FILES) $(DEP_LIB_PATHS) $(DEP_LIBS) -L./ -lMAssert

# Generic rule for test object files
test/%.o: test/%.cpp
	# Compiling test/ files
	$(TEST_CC) $(TEST_CC_FLAGS) $(DEP_INCLUDE_PATHS) -MD -o $@ $<
	-@cp $*.d $*.P >/dev/null 2>&1; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d >/dev/null 2>&1

-include $(TEST_OBJ_FILES:.o=.d)
	
	
# ====== CLEANING ======
	
clean: clean-ut clean-src clean-deps
	
clean-ut:
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	
clean-src:
	@echo " Cleaning src object files..."; $(RM) ./src/*.o
	@echo " Cleaning src dependency files..."; $(RM) ./src/*.d
	@echo " Cleaning src static library..."; $(RM) ./*.a
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test dependency files..."; $(RM) ./test/*.d
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	@echo " Cleaning example object files..."; $(RM) ./example/*.o
	@echo " Cleaning example executable..."; $(RM) ./example/*.elf

clean-deps:
	@echo " Cleaning deps...";
	$(MAKE) -C ../MUnitTest/ clean
	

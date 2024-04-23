# config
COMPILER=gcc
VERSION=c17
FLAGS=-Wall -Wextra -Wpedantic

C_FILES=$(wildcard ./src/*.c)
H_FILES=$(wildcard ./src/*.h)
OUT_FILE=geekymicky

## build         : Compilke and build executable
.PHONY : build
build:
	$(COMPILER) $(C_FILES) $(H_FILES) -std=$(VERSION) $(FLAGS) -o $(OUT_FILE)

## run           : Run executable
.PHONY : run
run:
	./$(OUT_FILE)

## clean        : Remove executable
.PHONY : clean
clean :
	rm -f ./$(OUT_FILE)

## info         : Print source and out files
.PHONY : info
info:
	@echo SRC_FILES: $(C_FILES) $(H_FILES)
	@echo OUT_FILES: $(OUT_FILE)

.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $<

# resource + motivation :- \
Mike Jackson (ed.): "Software Carpentry: Automation and Make." \
Version 2016.06, June 2016, \
https://github.com/swcarpentry/make-novice, 10.5281/zenodo.57473.

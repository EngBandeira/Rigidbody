buildP = build
includeP = include
srcP = src

executable = $(buildP)/final

source = $(shell find ./$(srcP) -path -prune -o -name '*.cpp' -print)

#objects = $(addprefix $(buildP), $(basename $(addprefix  $(dir $(source)), $(addsuffix .o , $(basename $(notdir $(source)))))))
objects = $(subst $(srcP),$(buildP),$(basename $(source)))

libs = X11 

flags_gcc = -Wall -I./$(includeP) -g -ggdb $(addprefix -l, $(libs))

flags_ld = -Wall -I./$(includeP) -g -ggdb

CC = g++

% :
	$(CC) $(flags_ld) $(subst $(buildP),$(srcP),$(addsuffix .c ,$@)) -c -o $(addsuffix .o, $@) 

$(executable):	$(objects) 
	$(CC) $(flags_gcc) $(addsuffix .o, $^) -o $@


clean:
	rm $(shell find ./$(buildP) -name '*.o') ./$(buildP)/final

all: $(executable)
	@echo buildado

create:
	$(shell mkdir -p $(dir $(objects)))
	$(shell mkdir -p $(dir $(subst $(srcP),$(includeP), $(source))))

init: 
	$(shell mkdir -p $(srcP) $(includeP) $(buildP))

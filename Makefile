CC = clang++
CFLAGS = -std=c++17
TASKS = Task1 Task2 Task3 Task4

.PHONY: all clean $(TASKS) run

all: $(TASKS)

$(TASKS):
	cd $@ && $(CC) $(CFLAGS) *.cpp -o $(shell echo $@ | tr A-Z a-z)

run:
	./$(filter-out $@,$(MAKECMDGOALS))/$(shell echo $(filter-out $@,$(MAKECMDGOALS)) | tr A-Z a-z)

clean:
	rm -f $(TASKS)
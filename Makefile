OBJS +=  test.o

PROGRAM=test

all: $(PROGRAM)

%o: %.cpp
	$(CXX) -c $^ -o $@

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ 

clean:
	$(RM) $(OBJS) $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

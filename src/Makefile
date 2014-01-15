BOOST=/home/liweic/boost_1_48_0
INCLUDE=-I../include -I $(BOOST)
LIB=-L /home/liweic/lib  -L ../lib 
LINKS=-lcachetube -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lboost_system
default:ctAgent
ctAgent:ctAgent.cpp mgAgent.cpp
	g++ -o ctAgent ctAgent.cpp $(INCLUDE) $(LIB) -lcachetube
	g++ -o mgAgent mgAgent.cpp $(INCLUDE) $(LIB) $(LINKS)
exe:
	./ctAgent
test:
	@echo $(INCLUDE)
	@echo $(LINKS)
clean:
	rm ctAgent mgAgent


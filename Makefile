CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Werror=return-type -Werror=uninitialized -pthread


server: server.o User.o
	$(CXX) $(CXXFLAGS) -o $@ $^

client: client.o TCPClient.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* server client


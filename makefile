# Part 2
social_network: social_network.o user.o network.o post.o
	g++ social_network.o user.o network.o post.o -o social_network
social_network.o: social_network.cpp
	g++ -c social_network.cpp -o social_network.o
user.o: user.cpp
	g++ -c user.cpp -o user.o
network.o: network.cpp
	g++ -c network.cpp -o network.o
post.o: post.cpp
	g++ -c post.cpp -o post.o
clean:
	-rm -f *.o
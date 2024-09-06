test : 
# Question 1
	g++ -c q1.cpp
	g++ -g -o ans1 q1.o
	g++ -O3 -o opt1 q1.o

	./ans1


# Question 2
	g++ -c q2.cpp
	g++ -g -o ans2 q2.o
	g++ -O3 -o opt2 q2.o

	./ans2
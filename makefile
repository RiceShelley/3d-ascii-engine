CC = g++

make:
	$(CC) main.cpp screen.cpp vector.cpp worldObj.cpp wObjCreator.cpp -lncurses

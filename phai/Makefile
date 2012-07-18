CC=g++
CFLAGS=-fPIC

transferlib.so:
	$(CC) $(CFLAGS) `Magick++-config --cxxflags --cppflags --ldflags --libs` histmatch.cpp -shared -o transferlib.so
phai.bin:
	$(CC) -ldl main.cpp -o phai.bin

clean:
	rm phai.bin transferlib.so

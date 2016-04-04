# huớng dẫn compile source code #

File tải về là file transColor.taz.gz

Phần thư viện cho việc chuyễn đổi ảnh sẽ đuợc build thành file .so trên linux nhằm thuận tiện cho việc gọi và thực thi thư viện này.

Cách build :

## Build histmatch.cpp to transferlib.so ##

### g++ -lMagick++ histmatch.cpp -shared -o transferlib.so ###

### g++ `Magick++-config --cxxflags --cppflags` -o magick++ histmatch.cpp `Magick++-config --ldflags --libs` -shared -o lib.so ###

Huớng dẫn nạp thư viện lên bộ nhớ,
Với C++ thì chỉ cần

void **my\_lib\_handle;
int (**some\_func)(char **,char**);
my\_lib\_handle = dlopen("./transferlib.so",RTLD\_NOW);


Với python sẽ cập nhật sau

Cách build với C++ để nạp thư viện lên bộ nhớ và sử dụng

## Build file main to phai.bin ##

### g++ -ldl -I/opt/gcc.3.3/include main.cpp -o phai.bin ###


Với python để load thư viện thì dùng code sau :

import ctypes

libc = ctypes.CDLL("./lib.so")

print libc.transfer\_color("5.jpg","c.jpg")
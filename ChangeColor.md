# Làm quen với IM bằng phuơng pháp transfer ảnh bằng cách phân tích histogram #

## Cách phân tích histogram : ##

Trong phần convert có 1 phần khá quan trọng là 1 option có tên là -equalize.Đây chính là phần cân bằng histogram cho ảnh màu.

Từ phần này ta tiếp tục trace sâu vào phần histogram của ảnh.Sau quá trình nghiên cứu code của file magick/histogram.c thì trong phần này có đuợc 1 phần có thể lấy histogram của 1 ảnh bật kỳ,nhưng đầu ra không đồng đều

Tôi đã thử test với 1 số ảnh khác nhau và kết quả lấy màu chưa chính xác nếu chỉ lấy khỏang nhỏ(256 bậc trong hệ thống màu),chính xác nếu lấy hết các pixel rồi gom lại.

## Các commandline đã test : ##

convert rose.bmp -format %c histogram:info:- > test1.txt

convert rose.bmp -colors 256 -depth 8 -format %c histogram:info:- > test2.txt


## Các command biến đổi contract ảnh : ##


convert anhthu2.jpg   +level-colors 'rgb(102,75,25)', anhtest.png


ảnh test rất khả quan.Phuơng pháp này biến đổi màu rất hiệu quả và thực sự an tòan.Ta chỉ cần lấy đuợc histogram của ảnh style,lấy ra các màu nhiều nhất trong đó rồi dùng option đổi màu trên để xử lý lại cũng là 1 phuơng án hay.
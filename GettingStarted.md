# Introduction #

Trang này giới thiệu cách thiết lập môi trường để lập trình


# Details #

## Cài đặt Eclipse ##
### Tải và cài Eclipse Classic ###
Link tải http://www.eclipse.org/downloads/
Sau khi tải về, xả nén vào 1 thư mục tự chọn. Chú ý trong máy phải có sẵn Java rồi.
### Cài PyDev ###
Link tải http://pydev.org/download.html
Sau khi tải về, vào help -> Install New Software trong Eclipse để cài
### Cài CDT để support C/C++ ###
Có sẵn trong Repository của Eclipse, chỉ cần vào Install New Software là cóe
### Cài GIT để làm việc với google code ###
Có sẵn trong Repository của Eclipse
## Cài các packages cần thiết trên Ubuntu ##
Các gói cần cài là:
  * build-essential
  * git
  * libmagick++4, libmagick++-dev
  * python-django
## Thiết lập Project trong Eclipse ##
Sau khi cài đầy đủ, ta có thể bắt đầu thiết lập project. Anh đã tạo sẵn 3 project trên Google Code (viết tắt GC).
  * phai - là thư viện động viết bằng C/C++
  * phais - là web server dựa trên Django, viết bằng Python
  * phaix - là chương trình dạng command-line, viêt băng C/C++
Để tải code về,
  * trươc hết chuyển qua Perspective Git bằng cách vào: Window -> Open Perspective -> Other -> Git Repository Exploring
  * Click nút Clone a Git Repository and add the clone to this view (Nút thứ 4 từ trái qua trong Git Repository Exploring)
  * 3 projects đã được đưa vào workspace. Nếu code Python thì chuyển qua PyDev Perspective. Nếu  code C/C++ thì chuyển qua C/C++ perspective. Có 2 cách chuyển là vào Window -> Open Perspective và Click vào các tab nằm bên góc trên-phải của màn hình Eclipse.
  * Sau khi sửa code, click chuột phải vào project chọn Team -> Commit. Các sửa đổi sẽ vào **Local Repository**, chứa trong máy của mình. Để đưa code mới lên Google Code, ta chọn Team -> Push to Upstream.

## Chuẩn viết code (Coding Standards) ##

Chúng ta dùng chuẩn code của Google. Tham khảo 2 links sau để biết viết code thế nào cho hiệu quả.
  * http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Nonmember,_Static_Member,_and_Global_Functions
  * http://google-styleguide.googlecode.com/svn/trunk/pyguide.html

## Các Tham khảo khác ##

  * http://www.imagemagick.org/Magick++/Image.html ví dụ về cách dùng Magick++
  * http://www.imagemagick.org/Magick++/Documentation.html trang để tra cứu các hàm của Magick++
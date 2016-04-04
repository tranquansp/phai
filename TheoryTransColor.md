# Lý thuyết cơ bản về việc transfer ảnh #

2 phương án đưa ra được trình bày trong 2 cuốn

http://www.cg.tuwien.ac.at/research/publications/2005/lneumann-2005-cst/

http://cgm.cs.ntust.edu.tw/kay/2007-01-04%20abstract/color%20transfer%20in%20correlated%20color%20space.pdf

## Cuốn thứ 1 ##
Đề cập đến phương án histogram matching.Đây là phương pháp khá kinh điển rồi.

Hàm Histogram của magick++ đưa về histogram màu của ảnh.Dựa vào phân bố màu của ảnh này ta biến đồi level color của ảnh của chúng ta

## Cuốn thứ 2 ##
Dùng phương pháp biến đổi màu sắc tương tự nhautrong không gian màu.

Cách làm :
Lấy màu R trung bình,màu G trung bình và B trung bình
Trừ từng pixel cho các màu trung bình để dc phương sai
Tính ma trận hiệp phương sai của ảnh nguồn và ảnh target
tính vector riêng và trị riêng của cov.

Về cơ bản,tính mean sẽ cho ta được trung bình về màu của từng pixel trong không gian màu,từ đó ma trận covariance sẽ chỉ ra được độ lệch chuẩn của màu với từng chiều của màu sắc,các trị riêng và vector riêng của ma trận covariance sẽ chỉ ra chiều dài và định hướng của 3 trục màu.
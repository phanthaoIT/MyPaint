------Lập trình Window-------
        -----My Paint------

Họ và tên: Phan Thị Thảo
MSSV: 1512518
link Git: https://github.com/phanthaoIT/MyPaint.git
link youtube:    https://youtu.be/vUtIxTp1Ovw
------------------------------------------------
Main flow:

- Tạo menu để chọn loại hình cần vẽ, có hiện check để biết đang vẽ loại hình nào.
- Vẽ các loại hình: Đường thẳng, Hình chữ nhật ( nhấn Shift để vẽ hình vuông), hình elip (Nhấn Shift để vẽ hình tròn).
-  Chỉ định nét vẽ,  màu vẽ
- Hỗ trợ New, Undo, Clear...

Yêu cầu nâng cao:

1. Bọc tất cả các đối tượng vẽ vào các lớp model. 
Sử dụng đa xạ (polymorphism) để cài đặt việc quản lý các đối tượng và vẽ hình. 
Sử dụng mẫu thiết kế prototypes để tạo ra hàng mẫu nhằm vẽ ở chế độ xem trước (preview),
 sử dụng mẫu thiết kế Factory để tạo mới đối tượng. 
2. Lưu và nạp các object (Lưu mảng các tọa độ ở dạng tập tin nhị phân) ( Save và Open)
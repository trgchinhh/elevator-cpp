## Demo Hệ Thống Điều Khiển Thang Máy C++

Chương trình mô phỏng thời gian thực hệ thống điều khiển và định tuyến thang máy di chuyển thông minh trong tòa nhà 10 tầng bằng ngôn ngữ C++ trên môi trường Windows Console.

<img width="1919" height="1022" alt="image" src="https://github.com/user-attachments/assets/d068c530-1a52-4f38-9b10-2dfc5893d7e5" />

## Thuật Toán Định Tuyến (SCAN / Elevator Algorithm)

Dự án áp dụng cấu trúc định tuyến **SCAN**, một thuật toán tối ưu thường được dùng trong các hệ thống thang máy thực tế:
* **Tính liên tục của hướng:** Thang máy giữ nguyên hướng di chuyển hiện tại (Lên hoặc Xuống) để xử lý tất cả các yêu cầu đón/trả khách ở phía trước trên lộ trình
* **Đổi chiều thông minh:** Thang máy chỉ đảo chiều khi và chỉ khi phía trước theo hướng đi cũ không còn bất kỳ hành khách nào đang đợi bên ngoài hoặc muốn dừng bên trong
* **Chống đói thuật toán (Starvation Prevention):** Đảm bảo phục vụ hành khách tuần tự, không bị nhảy cóc hỗn loạn, giúp tiết kiệm thời gian vận hành và năng lượng

---

## Các Tính Năng Trong Bản Mô Phỏng

* **Quản lý tải trọng:** Cabin giới hạn tối đa `10 người`. Thang máy sẽ tự động từ chối đón thêm các nhóm khách mới nếu tổng số người vượt quá tải trọng cho phép
* **Xử lý sự kiện thời gian thực:** Tự động mở cửa, trả đúng người, rước đúng tầng dựa trên dữ liệu đầu vào
* **Trạng thái nghỉ thông minh:** Khi toàn bộ hành khách đã được đưa đến đích an toàn, thang máy tự động hạ dần từng tầng về **Tầng 0** để trực
* **Giao diện trực quan:** Mô phỏng dạng trục tòa nhà đứng bằng ký tự bảng mã UTF-8 rõ ràng

---

## Cấu Trúc Khai Báo Dữ Liệu Khách (YeuCau)

Dữ liệu hành khách được truyền vào thông qua cấu trúc mảng Vector với định dạng: `{Tầng đón, Tầng đến, Số lượng người}`

```cpp
// Ví dụ cấu hình trong hàm main:
// {tầng rước, tầng đích, số lượng khách}
ds_yeu_cau.push_back({0, 3, 2});   // 2 người đi từ tầng 0 lên tầng 3
ds_yeu_cau.push_back({2, 7, 5});   // 5 người đi từ tầng 2 lên tầng 7
ds_yeu_cau.push_back({9, 1, 4});   // 4 người đi từ tầng 9 xuống tầng 1
```

## Cài đặt và biên dịch
```bash
g++ main.cpp -o main.exe
./main.exe
```

## Tác giả
**Nguyễn Trường Chinh (NTC++)**
GitHub: [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.

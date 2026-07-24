<p align="center">
  <img src="https://github.com/trgchinhh/elevator-cpp/blob/main/img/logo.png" alt="Elevator-logo" height="200">
</p>
<p align="center">
  <a href="https://github.com/trgchinhh/elevator-cpp">
    <img src="https://img.shields.io/badge/Language-C%2B%2B-orange.svg" alt="Language"/>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License"/>
  </a>
  <a href="https://github.com/trgchinhh">
    <img src="https://img.shields.io/badge/Author-Tr%C6%B0%E1%BB%9Dng%20Chinh-blueviolet" alt="Author"/>
  </a>
</p>

## Demo Hệ Thống Điều Khiển Thang Máy C++

Chương trình mô phỏng thời gian thực hệ thống điều khiển và định tuyến thang máy di chuyển thông minh trong tòa nhà 10 tầng bằng ngôn ngữ C++ trên môi trường Windows Console.

<img width="1919" height="1022" alt="image" src="https://github.com/user-attachments/assets/d068c530-1a52-4f38-9b10-2dfc5893d7e5" />

## Liên kết dự án 
**Bài viết trên FB:** [Bài viết chính thức trên Facebook](https://www.facebook.com/share/p/1F1rUUyLfL/)<br>

## Thuật Toán Định Tuyến (SCAN / Elevator Algorithm)

Dự án áp dụng cấu trúc định tuyến **SCAN**, một thuật toán tối ưu thường được dùng trong các hệ thống thang máy thực tế:
* **Tính liên tục của hướng:** Thang máy giữ nguyên hướng di chuyển hiện tại (Lên hoặc Xuống) để xử lý tất cả các yêu cầu đón/trả khách ở phía trước trên lộ trình
* **Đổi chiều thông minh:** Thang máy chỉ đảo chiều khi và chỉ khi phía trước theo hướng đi cũ không còn bất kỳ hành khách nào đang đợi bên ngoài hoặc muốn dừng bên trong
* **Chống đói thuật toán (Starvation Prevention):** Đảm bảo phục vụ hành khách tuần tự, không bị nhảy cóc hỗn loạn, giúp tiết kiệm thời gian vận hành và năng lượng

---

## Bảng Quy Trình Logic Điều Khiển

| Bước | Thành Phần Kiểm Tra | Điều Kiện / Trạng Thái | Hành Động Kích Hoạt | Trạng Thái Tiếp Theo |
| :---: | :--- | :--- | :--- | :--- |
| **1** | **Xử lý Hành khách tại Tầng** | Cabin có người muốn xuống **HOẶC** tầng có người đợi cùng hướng | • Mở cửa cabin<br>• Trả khách tại tầng đích<br>• Chuyển sang **Bước 2** (Kiểm tra tải trọng) | Kiểm tra hành khách |
| | | Không có ai cần xuống và không có ai đợi cùng hướng | • Bỏ qua, không mở cửa<br>• Nhảy thẳng sang **Bước 3** (Quét định tuyến) | Quét định tuyến |
| **2** | **Kiểm tra Tải trọng (Đón)** | Tải trọng hiện tại + Khách mới <= 10 người | • Đón khách mới vào cabin<br>• Đóng cửa và chuyển sang **Bước 3** | Quét định tuyến |
| | | Tải trọng hiện tại + Khách mới > 10 người | • Từ chối đón, để khách lại hàng chờ<br>• Đóng cửa và chuyển sang **Bước 3** | Quét định tuyến |
| **3** | **Quét hướng di chuyển cũ** | Còn yêu cầu cần xử lý ở phía trước trên lộ trình cũ | • Tiếp tục di chuyển theo hướng cũ (UP / DOWN) | Di chuyển tiếp |
| | | Hết yêu cầu ở phía trước trên lộ trình cũ | • Chuyển sang **Bước 4** (Kiểm tra hướng ngược lại) | Kiểm tra hướng ngược |
| **4** | **Quét hướng ngược lại** | Còn yêu cầu ở hướng ngược lại | • Kích hoạt đảo chiều trạng thái máy<br>• Di chuyển theo hướng mới | Đảo chiều di chuyển |
| | | Hết toàn bộ yêu cầu trong hệ thống | • Chuyển sang **Bước 5** (Kiểm tra trạng thái nghỉ) | Kiểm tra trạng thái nghỉ |
| **5** | **Trạng thái Nghỉ (Idle)** | Thang máy đang ở vị trí khác Tầng 0 | • Tự động hạ dần từng tầng về Tầng 0 để trực | Hạ tầng về Trệt |
| | | Thang máy đã ở sẵn Tầng 0 | • Kích hoạt chế độ Ngủ (Sleep) bảo toàn năng lượng | Kết thúc chu kỳ |

---

## Các Tính Năng Trong Bản Mô Phỏng

* **Quản lý tải trọng:** Cabin giới hạn tối đa `10 người`. Thang máy sẽ tự động từ chối đón thêm các nhóm khách mới nếu tổng số người vượt quá tải trọng cho phép
* **Xử lý sự kiện thời gian thực:** Tự động mở cửa, trả đúng người, rước đúng tầng dựa trên dữ liệu đầu vào
* **Trạng thái nghỉ thông minh:** Khi toàn bộ hành khách đã được đưa đến đích an toàn, thang máy tự động hạ dần từng tầng về **Tầng 0** để trực
* **Giao diện trực quan:** Mô phỏng dạng trục tòa nhà đứng bằng ký tự bảng mã UTF-8 rõ ràng

---

## Lõi thuật toán

### Kiểm tra sự kiện tại tầng (đón/trả khách)
Trước khi quyết định đi tiếp, thang máy phải kiểm tra xem tầng hiện tại có khách cần ra hoặc vào hay không

```cpp
for (int i = khach_trong_thang.size() - 1; i >= 0; i--) {
    if (khach_trong_thang[i].tang_den == tang_hien_tai) {
        khach_ra += khach_trong_thang[i].so_luong;
        so_khach_trong_thang -= khach_trong_thang[i].so_luong;
        khach_trong_thang.erase(khach_trong_thang.begin() + i);
        co_su_kien = true;
    }
}

for (auto& yc : ds_yeu_cau) {
    if (!yc.da_vao_thang && yc.tang_don == tang_hien_tai) {
        if (so_khach_trong_thang + yc.so_luong <= gioi_han_khach) {
            khach_vao += yc.so_luong;
            so_khach_trong_thang += yc.so_luong;
            yc.da_vao_thang = true; 
            khach_trong_thang.push_back(yc); 
            co_su_kien = true;
        }
    }
}
```
**Cơ chế**
- Ưu tiên trả trước, đón sau: Vòng lặp xóa khách ra (khach_trong_thang.erase) chạy trước để giải phóng không gian cabin, giúp thang máy tối ưu hóa tải trọng trống trước khi nạp thêm khách mới vào.

- An toàn tải trọng: Thang máy kiểm tra điều kiện so_khach_trong_thang + yc.so_luong <= 10. Nếu một nhóm khách quá đông làm nghẽn tải, họ sẽ bị giữ lại ở trạng thái da_vao_thang = false để đợi lượt sau.

### Quyết định hướng đi 
Thang máy sẽ không đổi chiều tùy tiện mà quét toàn bộ danh sách để xem phía trước còn việc hay không.

```cpp
bool tiep_tuc_huong_cu = false;

if (huong_di == 1) {
    for (auto& yc : ds_yeu_cau)
        if (!yc.da_vao_thang && yc.tang_don > tang_hien_tai)
            tiep_tuc_huong_cu = true;

    for (auto& yc : khach_trong_thang)
        if (yc.tang_den > tang_hien_tai)
            tiep_tuc_huong_cu = true;
}
else if (huong_di == -1) {
    for (auto& yc : ds_yeu_cau)
        if (!yc.da_vao_thang && yc.tang_don < tang_hien_tai)
            tiep_tuc_huong_cu = true;

    for (auto& yc : khach_trong_thang)
        if (yc.tang_den < tang_hien_tai)
            tiep_tuc_huong_cu = true;
}

if (!tiep_tuc_huong_cu && con_viec)
    huong_di = -huong_di;
```
**Cơ chế**
- Tính bảo toàn hướng: Biến tiep_tuc_huong_cu đóng vai trò chốt chặn. Nếu thang máy đang ở tầng 5 và hướng đi là LÊN, nó bắt buộc phải duyệt qua toàn bộ các tầng 6, 7, 8, 9, 10.

- Điều kiện đảo chiều: Chỉ khi cả 2 điều kiện: (1) Không còn khách bên ngoài ở phía trước, và (2) Không còn nút nhấn tầng phía trước bên trong cabin đồng thời thỏa mãn, phép toán huong_di = -huong_di mới được kích hoạt để lật ngược véc-tơ di chuyển.

### Tìm Mục Tiêu Gần Nhất Theo Hướng Đi
Sau khi đã chốt hướng đi, thang máy cần tìm ra tầng đích tiếp theo (tang_dich) bằng cách dò khoảng cách ngắn nhất (khoang_cach_min).
```cpp
int tang_dich = tang_hien_tai;
int khoang_cach_min = 999;

if (huong_di == 1) {
    for (const auto& yc : ds_yeu_cau)
        if (!yc.da_vao_thang && yc.tang_don > tang_hien_tai && yc.tang_don - tang_hien_tai < khoang_cach_min) {
            khoang_cach_min = yc.tang_don - tang_hien_tai;
            tang_dich = yc.tang_don;
        }

    for (const auto& yc : khach_trong_thang)
        if (yc.tang_den > tang_hien_tai && yc.tang_den - tang_hien_tai < khoang_cach_min) {
            khoang_cach_min = yc.tang_den - tang_hien_tai;
            tang_dich = yc.tang_den;
        }
}
```
**Cơ chế**
- Thuật toán tham lam cục bộ (Greedy): Khởi tạo khoang_cach_min = 999, thuật toán thực hiện phép trừ toán học giữa tầng yêu cầu và tang_hien_tai. Mục tiêu nào cho hiệu số nhỏ nhất sẽ được chọn làm điểm dừng chân tiếp theo.

- Đồng bộ đích đến: Hệ thống liên tục so sánh cả điểm đón (ngoại cabin) và điểm trả (nội cabin) để đảm bảo lộ trình mượt mà, không bỏ sót bất kỳ ga dừng nào trên đường đi.

### Cấu Trúc Khai Báo Dữ Liệu Khách (YeuCau)
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
git clone https://github.com/trgchinhh/elevator-cpp.git
cd elevator-cpp
g++ ./main.cpp -o ./main.exe
./main.exe
```

## Tác giả
**Nguyễn Trường Chinh (NTC++)**<br>
**GitHub:** [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.

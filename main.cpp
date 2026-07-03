//  ______ _                 _             
// |  ____| |               | |            
// | |__  | | _____   ____ _| |_ ___  _ __ 
// |  __| | |/ _ \ \ / / _` | __/ _ \| '__|   Demo hoạt động thang máy C++
// | |____| |  __/\ V / (_| | || (_) | |      Thuật toán Scan
// |______|_|\___| \_/ \__,_|\__\___/|_|      Tác giả: Nguyễn Trường Chinh
//                                         
// Bản quyền: MIT LICENSE 2026                                      

#include <windows.h>
#include <conio.h>
#include <bits/stdc++.h>
using namespace std;

void banner(){
    const string banner = 
R"(
MÔ PHỎNG HỆ THỐNG ĐIỀU KHIỂN THANG MÁY BẰNG C++

╔═════════════════════════════════╗
║  Tác giả : Trường Chinh         ║
║  Github  : Github.com/trgchinhh ║
╚═════════════════════════════════╝
)";
    cout << banner << endl;
}

struct YeuCau {
    int tang_don;
    int tang_den;
    int so_luong;
    bool da_vao_thang = false;
};

void cho_va_dong_thang_may(){
    cout << "\nNhấn Enter để tiếp tục di chuyển..." << endl;
    getch();
}

string in_tung_dong(int i, int tang_hien_tai) {
    string dong = "│ Tầng ";
    if (i < 10) {
        dong += to_string(i) + " : "; 
    } else {
        dong += to_string(i) + ": ";  
    }
    if (i == tang_hien_tai) {
        dong += "[Thang máy] ";
    } else if (i > tang_hien_tai) {
        if (i == 10) {
            dong += "     ●      ";
        } else {
            dong += "     ║      ";
        } 
    } else {
        dong += "            "; 
    }
    return dong += "│"; 
}

void hien_thi_toa_nha(int so_tang, int tang_hien_tai) {
    cout << "┌──────────────────────┐" << endl;
    for(int i = so_tang; i >= 0; i--){
        cout << in_tung_dong(i, tang_hien_tai) << endl;
    }
    cout << "└──────────────────────┘" << endl;
}

void ve_thang_may(vector<YeuCau>& ds_yeu_cau, int so_tang){
    int tang_hien_tai = 0;
    int so_khach_trong_thang = 0;
    int gioi_han_khach = 10;
    int huong_di = 1;
    string huong = "-";
    vector<YeuCau> khach_trong_thang;

    while(true){
        bool con_viec = false;
        for (const auto& yc : ds_yeu_cau) {
            if (!yc.da_vao_thang) {
                con_viec = true;
            }
        }
        if (!khach_trong_thang.empty()) {
            con_viec = true;
        }
        if (!con_viec) {
            break;
        }

        bool co_su_kien = false;
        int khach_ra = 0;
        int khach_vao = 0;

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

        if (co_su_kien) {
            system("cls");
            banner();
            hien_thi_toa_nha(so_tang, tang_hien_tai);
            cout << "\n[Trạng thái]: Thang máy mở cửa tại tầng " << tang_hien_tai << endl;
            if (khach_ra > 0) {
                cout << "Số khách ra khỏi thang: " << khach_ra << " người" << endl;
            }
            if (khach_vao > 0) {
                cout << "Số khách vào thang: " << khach_vao << " người" << endl;
            }
            cout << "Số khách trong thang hiện tại: " << so_khach_trong_thang << "/" << gioi_han_khach << " người" << endl;
            cout << "Danh sách khách đang đợi ở các tầng: " << endl;
            bool co_khach_doi = false;
            for (const auto& yc : ds_yeu_cau) {
                if (!yc.da_vao_thang) {
                    //cout << " - Tầng " << yc.tang_don << " có " << yc.so_luong << " người đang đợi đi tầng " << yc.tang_den << endl;
                    cout << " - Tầng " << yc.tang_don << " đến tầng " << yc.tang_den << ": " << yc.so_luong << " người chờ" << endl;
                    co_khach_doi = true;
                }
            }
            if (!co_khach_doi) {
                cout << " - Không còn ai đang đợi bên ngoài." << endl;
            }
            cho_va_dong_thang_may();
        }

        con_viec = false;
        for (const auto& yc : ds_yeu_cau) {
            if (!yc.da_vao_thang) {
                con_viec = true;
            }
        }
        if (!khach_trong_thang.empty()) {
            con_viec = true;
        }
        if (!con_viec) {
            break;
        }

        bool tiep_tuc_huong_cu = false;
        if (huong_di == 1) {
            for (auto& yc : ds_yeu_cau) {
                if (!yc.da_vao_thang && yc.tang_don > tang_hien_tai) {
                    tiep_tuc_huong_cu = true;
                }
            }
            for (auto& yc : khach_trong_thang) {
                if (yc.tang_den > tang_hien_tai) {
                    tiep_tuc_huong_cu = true;
                }
            }
        } else if (huong_di == -1) {
            for (auto& yc : ds_yeu_cau) {
                if (!yc.da_vao_thang && yc.tang_don < tang_hien_tai) {
                    tiep_tuc_huong_cu = true;
                }
            }
            for (auto& yc : khach_trong_thang) {
                if (yc.tang_den < tang_hien_tai) {
                    tiep_tuc_huong_cu = true;
                }
            }
        }
        if (!tiep_tuc_huong_cu && con_viec) {
            huong_di = -huong_di;
        }
        if (con_viec) {
            huong = (huong_di == 1) ? "Lên ⭡" : "Xuống ⭣";
            int tang_dich = tang_hien_tai;
            int khoang_cach_min = 999;
            if (huong_di == 1) {
                for (const auto& yc : ds_yeu_cau) {
                    if (!yc.da_vao_thang && yc.tang_don > tang_hien_tai && (yc.tang_don - tang_hien_tai) < khoang_cach_min) {
                        khoang_cach_min = yc.tang_don - tang_hien_tai;
                        tang_dich = yc.tang_don;
                    }
                }
                for (const auto& yc : khach_trong_thang) {
                    if (yc.tang_den > tang_hien_tai && (yc.tang_den - tang_hien_tai) < khoang_cach_min) {
                        khoang_cach_min = yc.tang_den - tang_hien_tai;
                        tang_dich = yc.tang_den;
                    }
                }
            } else {
                for (const auto& yc : ds_yeu_cau) {
                    if (!yc.da_vao_thang && yc.tang_don < tang_hien_tai && (tang_hien_tai - yc.tang_don) < khoang_cach_min) {
                        khoang_cach_min = tang_hien_tai - yc.tang_don;
                        tang_dich = yc.tang_don;
                    }
                }
                for (const auto& yc : khach_trong_thang) {
                    if (yc.tang_den < tang_hien_tai && (tang_hien_tai - yc.tang_den) < khoang_cach_min) {
                        khoang_cach_min = tang_hien_tai - yc.tang_den;
                        tang_dich = yc.tang_den;
                    }
                }
            }

            system("cls");
            banner();
            hien_thi_toa_nha(so_tang, tang_hien_tai);
            cout << "\n[Trạng thái]: Thang di chuyển" << endl;
            cout << "Tầng hiện tại: " << tang_hien_tai << " | Tầng đích tiếp theo: " << tang_dich << " | Hướng: " << huong << endl;
            cout << "Số khách trong thang: " << so_khach_trong_thang << "/" << gioi_han_khach << " người" << endl;
            cout << "Danh sách khách chưa rước ở các tầng: " << endl;
            bool co_khach_doi = false;
            for (const auto& yc : ds_yeu_cau) {
                if (!yc.da_vao_thang) {
                    cout << " - Tầng " << yc.tang_don << " có " << yc.so_luong << " người đang đợi" << endl;
                    co_khach_doi = true;
                }
            }
            if (!co_khach_doi) {
                cout << " - Không ai đợi bên ngoài" << endl;
            }
            Sleep(1000);
            tang_hien_tai += huong_di;
        }
    }

    while(tang_hien_tai >= 0){
        system("cls");
        banner();
        int tang_dich = 0;
        hien_thi_toa_nha(so_tang, tang_hien_tai);
        cout << "\n[Trạng thái]: Hết khách ! Quay về tầng 0" << endl;
        cout << "Tầng hiện tại: " << tang_hien_tai << " | Tầng đích tiếp theo: " << tang_dich << " | Hướng: Xuống ⭣" << endl;
        cout << "Số khách trong thang: " << so_khach_trong_thang << " người" << endl;
        if (tang_hien_tai == 0) {
            break; 
        }
        Sleep(1000);
        tang_hien_tai--;
    }
    
    cout << "\nKết thúc hành trình !" << endl;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    vector<YeuCau> ds_yeu_cau;
    int so_tang = 10;

    // {tầng rước, tầng đích, số lượng khách}
    ds_yeu_cau.push_back({0, 3, 2});  
    ds_yeu_cau.push_back({2, 7, 5});  
    ds_yeu_cau.push_back({9, 1, 4});  
    ds_yeu_cau.push_back({4, 10, 3});
    ds_yeu_cau.push_back({7, 3, 4});
    
    ve_thang_may(ds_yeu_cau, so_tang);
    return 0;
}

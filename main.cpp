#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Khai báo cấu trúc của mỗi File (Node dữ liệu)
struct F {
    string n;    // n: name 
    long s;      // s: size 
    time_t t;    // t: timestamp

    F(string name, long size, time_t time) : n(name), s(size), t(time) {}
};

struct Node {
    F d;         // d: data 
    Node* next;  // next: Con trỏ trỏ đến file kế tiếp

    Node(F file) : d(file), next(nullptr) {}
};

// Quản lý Danh sách liên kết
class FileList {
private:
    Node* h;     // h: head

public:
    FileList() : h(nullptr) {}

    // 2. Hàm chèn file theo thứ tự thời gian tăng dần
    void insert(F file) {
        Node* newNode = new Node(file);
        // Nếu danh sách trống hoặc file mới cũ hơn file đầu tiên
        if (!h || difftime(file.t, h->d.t) < 0) {
            newNode->next = h;
            h = newNode;
            return;
        }
        // Duyệt tìm vị trí chèn phù hợp
        Node* p = h; // p: pointer (con trỏ duyệt)
        while (p->next && difftime(file.t, p->next->d.t) > 0) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }

    // 3. Tính tổng kích thước các file
    long totalSize() {
        long sum = 0; // sum: tổng dung lượng
        Node* p = h;
        while (p) {
            sum += p->d.s;
            p = p->next;
        }
        return sum;
    }

    // 4. Loại bỏ các file có kích thước nhỏ nhất để vừa USB 32GB (32.000.000 KB)
    void backup() {
        const long limit = 32000000; // limit: giới hạn 32GB
        while (totalSize() > limit && h) {
            // Tìm file có size nhỏ nhất
            Node *minP = h, *curr = h, *prev = nullptr, *minPrev = nullptr;
            long minS = h->d.s; // minS: size nhỏ nhất hiện tại

            while (curr->next) {
                if (curr->next->d.s < minS) {
                    minS = curr->next->d.s;
                    minP = curr->next;
                    minPrev = curr;
                }
                curr = curr->next;
            }

            // Xóa file nhỏ nhất tìm được
            if (minP == h) h = h->next;
            else minPrev->next = minP->next;
            
            cout << "Da xoa file: " << minP->d.n << " (" << minP->d.s << " KB)" << endl;
            delete minP;
        }
    }
};

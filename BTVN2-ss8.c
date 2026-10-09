#include <stdio.h>
#include <math.h>
int main(){
	return 0;
}

#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
    int actual_fee;
};

int main() {
    struct UserAccount users[100];
    int N;
    int i;
    int total_revenue = 0;
    int downgraded_count = 0;
    int penalty;

    // Nhap so luong tai khoan
    do {
        printf("Nhap so luong tai khoan (1-100): ");
        if (scanf("%d", &N) != 1) {
            printf("Loi: Vui long nhap so nguyen.\n");
            return 1;
        }

        if (N < 1 || N > 100) {
            printf("So luong khong hop le. Vui long nhap lai.\n");
        }
    } while (N < 1 || N > 100);

    // Nhap va kiem tra du lieu
    for (i = 0; i < N; i++) {
        printf("\n--- Tai khoan %d ---\n", i + 1);

        printf("Nhap ma tai khoan: ");
        scanf("%d", &users[i].user_id);

        printf("Nhap ten tai khoan (khong dau cach): ");
        scanf("%49s", users[i].username);

        do {
            printf("Nhap loai goi (1-Free, 2-Personal, 3-Family): ");
            scanf("%d", &users[i].plan_type);

            if (users[i].plan_type < 1 ||
                users[i].plan_type > 3) {
                printf("Loi: Loai goi phai tu 1 den 3.\n");
            }
        } while (users[i].plan_type < 1 ||
                 users[i].plan_type > 3);

        do {
            printf("Nhap so ngay no cuoc: ");
            scanf("%d", &users[i].days_overdue);

            if (users[i].days_overdue < 0) {
                printf("Loi: So ngay no khong duoc am.\n");
            }
        } while (users[i].days_overdue < 0);

        do {
            printf("Nhap so thiet bi dang ket noi: ");
            scanf("%d", &users[i].active_devices);

            if (users[i].active_devices < 0) {
                printf("Loi: So thiet bi khong duoc am.\n");
            }
        } while (users[i].active_devices < 0);
    }

    // Xu ly tai khoan
    for (i = 0; i < N; i++) {
        // Tinh phi co ban theo goi
        if (users[i].plan_type == 1) {
            users[i].actual_fee = 0;
        } else if (users[i].plan_type == 2) {
            users[i].actual_fee = 120000;
        } else {
            users[i].actual_fee = 250000;
        }

        // Quy tac 1: Ha cap neu no tu 3 ngay tro len
        if (users[i].days_overdue >= 3) {
            if (users[i].plan_type != 1) {
                users[i].plan_type = 1;
                downgraded_count++;
            }

            users[i].actual_fee = 0;
        }

        // Quy tac 2: Phu thu chi ap dung cho goi Personal
        // sau khi da xu ly ha cap
        if (users[i].plan_type == 2 &&
            users[i].active_devices > 1) {

            penalty = (users[i].active_devices - 1) * 30000;
            users[i].actual_fee += penalty;
        }

        // Cong doanh thu
        total_revenue += users[i].actual_fee;
    }

    // In bao cao
    printf("\n");
    printf("========== BAO CAO DOI SOAT STREAMFLOW ==========\n");
    printf("%-10s %-20s %-8s %-12s %-12s %-18s\n",
           "Ma TK", "Ten TK", "Ma Goi",
           "So Thiet Bi", "So Ngay No", "Phi Thuc Thu");

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < N; i++) {
        printf("%-10d %-20s %-8d %-12d %-12d %-18d\n",
               users[i].user_id,
               users[i].username,
               users[i].plan_type,
               users[i].active_devices,
               users[i].days_overdue,
               users[i].actual_fee);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc te: %d VND\n", total_revenue);
    printf("So tai khoan bi ha cap: %d\n", downgraded_count);

    return 0;
}

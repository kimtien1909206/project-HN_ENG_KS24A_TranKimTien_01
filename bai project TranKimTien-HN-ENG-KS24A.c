#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[15];
    char password[15];
    char status[10];
} User;
User users[100];
int userCount = 0;
void show_main_menu() {
    printf("********** Bank Management system using c **********\n");
    printf("==================\n");
    printf("1. Admin\n");
    printf("2. Users\n");
    printf("3. Exit\n");
    printf("==================\n");
    printf("Moi ban chon: ");
   
}
int isValidPhoneNumber(const char *phone) {
	int i;
    int length = strlen(phone);
    if (length != 10 && length != 11) return 0;
    for (i = 0; i < length; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}
int isValidEmail(const char *email) {
    return strchr(email, '@') && strchr(email, '.');
}
int isUserNameExist(const char *userName) {
	int i;
    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, userName) == 0) {
            return 1;
        }
    }
    return 0;
}
int isEmailExist(const char *email) {
	int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}
int isPhoneExist(const char *phone) {
	int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}
void addUser() {
    if (userCount >= 100) {
        printf("Danh sach nguoi dung da day.\n");
        return;
    }
    User newUser;
    newUser.id = userCount + 1;
    printf("Nhap ten nguoi dung: ");
    getchar();
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';
    if (strlen(newUser.name) == 0) {
        printf("Ten nguoi dung khong duoc de trong.\n");
        return;
    }
    printf("Nhap email nguoi dung: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0';
    if (strlen(newUser.email) == 0 || !isValidEmail(newUser.email)) {
        printf("Email khong hop le.\n");
        return;
    }
    if (isEmailExist(newUser.email)) {
        printf("Email da ton tai.\n");
        return;
    }
    printf("Nhap so dien thoai: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = '\0';
    if (strlen(newUser.phone) == 0 || !isValidPhoneNumber(newUser.phone)) {
        printf("So dien thoai khong hop le.\n");
        return;
    }
    if (isPhoneExist(newUser.phone)) {
        printf("So dien thoai da ton tai.\n");
        return;
    }
    printf("Nhap mat khau: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0';
    if (strlen(newUser.password) == 0 || isUserNameExist(newUser.password)) {
        printf("Mat khau da ton tai.\n");
        return;
    }
    strcpy(newUser.status, "open");
    users[userCount] = newUser;
    userCount++;
    printf("Nguoi dung da duoc them thanh cong.\n");
}
void displayUsers() {
	int i;
    if (userCount == 0) {
        printf("Danh sach nguoi dung hien dang trong.\n");
        return;
    }
    printf("\n================ DANH SACH NGUOI DUNG ================\n");
    printf("| ID  | Ten                    | Email                        | SDT          | Trang thai |\n");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < userCount; i++) {
        printf("| %-4d | %-20s | %-30s | %-12s | %-10s |\n", 
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }
    printf("===============================================================\n");
}
void searchUserByName() {
	int i;
    char keyword[50];
    printf("Nhap ten hoac mot phan ten de tim kiem: ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    printf("\nKet qua tim kiem:\n");
    printf("| ID  | Ten                    | Email                        | SDT          | Trang thai |\n");
    printf("--------------------------------------------------------------------------------------\n");
    int found = 0;
    for (i = 0; i < userCount; i++) {
        if (strstr(users[i].name, keyword)) {
            printf("| %-4d | %-20s | %-30s | %-12s | %-10s |\n", 
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay nguoi dung nao phu hop.\n");
    }
}
void viewUserDetailsByID() {
	int i;
    int id;
    printf("Nhap ID nguoi dung: ");
    scanf("%d", &id);
    for (i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            printf("\nChi tiet nguoi dung:\n");
            printf("ID: %d\n", users[i].id);
            printf("Ten: %s\n", users[i].name);
            printf("Email: %s\n", users[i].email);
            printf("SDT: %s\n", users[i].phone);
            printf("Trang thai: %s\n", users[i].status);
            return;
        }
    }
    printf("Khong tim thay nguoi dung voi ID nay.\n");
}
void lockOrUnlockUser() {
	int i;
    int id;
    printf("Nhap ID nguoi dung: ");
    scanf("%d", &id);
    for (i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            if (strcmp(users[i].status, "open") == 0) {
                strcpy(users[i].status, "locked");
                printf("Nguoi dung da bi khoa.\n");
            } else {
                strcpy(users[i].status, "open");
                printf("Nguoi dung da duoc mo khoa.\n");
            }
            return;
        }
    }
    printf("Khong tim thay nguoi dung voi ID nay.\n");
}
void sortUsersByName() {
	int i,j;
    for (i = 0; i < userCount - 1; i++) {
        for (j = i + 1; j < userCount; j++) {
            if (strcmp(users[i].name, users[j].name) > 0) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
    printf("Danh sach nguoi dung da duoc sap xep theo ten.\n");
}
void saveUsersToFile() {
    FILE *file = fopen("users.bin", "wb");
    if (file == NULL) {
        printf("Loi khi mo file de luu du lieu.\n");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    printf("Du lieu nguoi dung da duoc luu.\n");
}
void loadUsersFromFile() {
    FILE *file = fopen("users.bin", "rb");
    if (file == NULL) {
        return;
    }
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}
int main() {
    loadUsersFromFile();
    int choice;
    while (1) {
        show_main_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            	printf("====================================\n");
    			printf("     HE THONG QUAN LY NGAN HANG     \n");
    			printf("====================================\n");
                printf("\n---------- MENU QUAN LY NGUOI DUNG ----------\n");
                printf("1. Them nguoi dung\n");
                printf("2. Hien thi nguoi dung\n");
                printf("3. Tim kiem nguoi dung theo ten\n");
                printf("4. Xem chi tiet nguoi dung theo ID\n");
                printf("5. Khoa/Mo khoa nguoi dung\n");
                printf("6. Sap xep danh sach nguoi dung\n");
                printf("7. Luu du lieu nguoi dung\n");
                printf("8. Quay lai menu chinh\n");
                printf("--------------------------------------------\n");
                printf("Chon mot tuy chon: ");
                int adminChoice;
                scanf("%d", &adminChoice);
                switch (adminChoice) {
                case 1: 
					addUser(); 
					break;
                case 2: 
					displayUsers(); 
					break;
                case 3: 
					searchUserByName(); 
					break;
                case 4: 
					viewUserDetailsByID(); 
					break;
                case 5: 
					lockOrUnlockUser(); 
					break;
                case 6: 
					sortUsersByName(); 
					break;
                case 7: 
					saveUsersToFile(); 
					break;
                case 8: 
					break;
                    default: printf("Lua chon khong hop le.\n"); break;
                }
                break;
            case 2:
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                saveUsersToFile();
                exit(0);
            default:
                printf("Lua chon khong hop le.\n");
        }
    }
    return 0;
}


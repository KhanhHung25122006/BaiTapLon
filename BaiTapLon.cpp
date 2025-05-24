#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];
    char name[50];
    int age;
    float gpa;
} Student;

Student* students = NULL;
int count = 0;

// Kiem tra MSSV da ton tai chua
int isDuplicateID(char id[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

// Them sinh vien moi
void addStudent() {
    Student temp;
    printf("Nhap MSSV: ");
    scanf("%9s", temp.id);

    if (isDuplicateID(temp.id)) {
        printf("MSSV da ton tai!\n");
        return;
    }

    while (getchar() != '\n');
    printf("Nhap ten: ");
    fgets(temp.name, sizeof(temp.name), stdin);
    size_t len = strlen(temp.name);
    if (len > 0 && temp.name[len - 1] == '\n') {
        temp.name[len - 1] = '\0';
    }

    printf("Nhap tuoi: ");
    scanf("%d", &temp.age);

    printf("Nhap GPA: ");
    scanf("%f", &temp.gpa);

    void* tmp = realloc(students, (count + 1) * sizeof(Student));
    if (tmp == NULL) {
        printf("Cap phat bo nho that bai!\n");
        exit(1);
    }
    students = (Student*)tmp;

    students[count++] = temp;
    printf("Da them sinh vien!\n");
}

// Hien thi danh sach sinh vien
void displayStudents() {
    if (count == 0) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }

    printf("\n%-10s %-30s %-5s %-5s\n", "MSSV", "Ho Ten", "Tuoi", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-30s %-5d %-5.2f\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

// Tim sinh vien theo MSSV
void searchByID() {
    char id[10];
    printf("Nhap MSSV can tim: ");
    scanf("%9s", id);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("Tim thay sinh vien:\n");
            printf("MSSV: %s\nTen: %s\nTuoi: %d\nGPA: %.2f\n",
                   students[i].id, students[i].name, students[i].age, students[i].gpa);
            return;
        }
    }
    printf("Khong tim thay MSSV!\n");
}

// Xoa sinh vien theo MSSV
void deleteByID() {
    char id[10];
    printf("Nhap MSSV can xoa: ");
    scanf("%9s", id);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            students[i] = students[count - 1]; // Ghi ри b?ng ph?n t? cu?i
            count--;
            if (count > 0) {
                void* tmp = realloc(students, count * sizeof(Student));
                if (tmp == NULL && count > 0) {
                    printf("Cap phat bo nho that bai sau khi xoa!\n");
                    exit(1);
                }
                students = (Student*)tmp;
            } else {
                free(students);
                students = NULL;
            }
            printf("Da xoa sinh vien co MSSV %s\n", id);
            return;
        }
    }
    printf("Khong tim thay MSSV de xoa!\n");
}

// Menu
void menu() {
    int choice;
    do {
        printf("\n===== MENU QUAN LY SINH VIEN =====\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Tim theo MSSV\n");
        printf("4. Xoa theo MSSV\n");
        printf("5. Thoat\n");
        printf("Chon chuc nang(1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByID(); break;
            case 4: deleteByID(); break;
            case 5: printf("==> Thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 5);
}

int main() {
    menu();
    free(students);
    return 0;
}


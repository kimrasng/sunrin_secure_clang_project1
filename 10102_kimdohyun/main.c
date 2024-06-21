#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

typedef struct music {
    char title[20];
    char artist[20];
    char genre[20];
} MUSIC;

enum choice { CREATE = 1, SELECT, UPDATE, DELETE, IN_, OUT_, EXIT };

int CNT = 0;
MUSIC mlist[MAX_RECORDS];

void menu();
MUSIC create_record();
void select_record();
void delete_record();
void update_record();
void import_records();
void export_records();

int main(void) {
    int choice;

    while (1) {
        menu();
        printf("메뉴 입력 : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case CREATE:
            mlist[CNT] = create_record();
            CNT++;
            break;
        case SELECT:
            select_record();
            break;
        case DELETE:
            delete_record();
            break;
        case UPDATE:
            update_record();
            break;
        case IN_:
            import_records();
            break;
        case OUT_:
            export_records();
            break;
        case EXIT:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }

    return 0;
}

void menu() {
    puts("========================");
    puts("1. 추가 2. 조회 3. 수정 4. 삭제 5. 데이터 불러오기 6. 데이터 내보내기 7. 종료");
    puts("========================");
}

MUSIC create_record() {
    MUSIC m;
    printf("=========생성=========\n");
    printf("제목 : ");
    fgets(m.title, sizeof(m.title), stdin);
    m.title[strcspn(m.title, "\n")] = '\0';
    printf("가수 : ");
    fgets(m.artist, sizeof(m.artist), stdin);
    m.artist[strcspn(m.artist, "\n")] = '\0';
    printf("장르 : ");
    fgets(m.genre, sizeof(m.genre), stdin);
    m.genre[strcspn(m.genre, "\n")] = '\0';

    return m;
}

void select_record() {
    printf("============조회============\n\n");
    if (CNT == 0) {
        printf("저장된 레코드가 없습니다.\n");
        return;
    }

    for (int i = 0; i < CNT; i++) {
        printf("============번호 : %d============\n", i + 1);
        printf("제목 : %s\n", mlist[i].title);
        printf("가수 : %s\n", mlist[i].artist);
        printf("장르 : %s\n", mlist[i].genre);
    }
}

void delete_record() {
    char title[20];
    int i, found = 0;

    printf("=========삭제=========\n");
    printf("삭제할 곡 제목: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; i < CNT; i++) {
        if (strcmp(title, mlist[i].title) == 0) {
            found = 1;
            printf("%s를 삭제 중...\n", title);
            break;
        }
    }

    if (!found) {
        printf("%s를 찾을 수 없습니다.\n", title);
        return;
    }

    for (int j = i; j < CNT - 1; j++) {
        strcpy(mlist[j].title, mlist[j + 1].title);
        strcpy(mlist[j].artist, mlist[j + 1].artist);
        strcpy(mlist[j].genre, mlist[j + 1].genre);
    }

    CNT--;
    printf("%s를 삭제 완료하였습니다.\n", title);
}

void update_record() {
    char title[20];
    int i, found = 0;

    printf("=========수정=========\n");
    printf("수정할 곡 제목: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; i < CNT; i++) {
        if (strcmp(title, mlist[i].title) == 0) {
            found = 1;
            printf("새로운 제목: ");
            fgets(mlist[i].title, sizeof(mlist[i].title), stdin);
            mlist[i].title[strcspn(mlist[i].title, "\n")] = '\0';
            printf("새로운 가수: ");
            fgets(mlist[i].artist, sizeof(mlist[i].artist), stdin);
            mlist[i].artist[strcspn(mlist[i].artist, "\n")] = '\0';
            printf("새로운 장르: ");
            fgets(mlist[i].genre, sizeof(mlist[i].genre), stdin);
            mlist[i].genre[strcspn(mlist[i].genre, "\n")] = '\0';
            printf("%s를 수정 완료하였습니다.\n", title);
            break;
        }
    }

    if (!found) {
        printf("%s를 찾을 수 없습니다.\n", title);
    }
}

void import_records() {
    FILE* fp;
    char filename[100];
    char line[100];
    char* token;
    int count = 0;

    printf("=========데이터 불러오기=========\n");
    printf("불러올 파일명을 입력하세요: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_RECORDS) {
        token = strtok(line, ",");
        if (token != NULL) {
            strncpy(mlist[count].title, token, sizeof(mlist[count].title) - 1);
            mlist[count].title[sizeof(mlist[count].title) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(mlist[count].artist, token, sizeof(mlist[count].artist) - 1);
            mlist[count].artist[sizeof(mlist[count].artist) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(mlist[count].genre, token, sizeof(mlist[count].genre) - 1);
            mlist[count].genre[sizeof(mlist[count].genre) - 1] = '\0';
        }

        count++;
    }

    fclose(fp);
    CNT = count;
    printf("데이터를 성공적으로 불러왔습니다.\n");
}

void export_records() {
    FILE* fp;
    char filename[100];

    printf("=========데이터 내보내기=========\n");
    printf("저장할 파일명을 입력하세요: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(fp, "제목,가수,장르\n");

    for (int i = 0; i < CNT; i++) {
        fprintf(fp, "%s,%s,%s\n", mlist[i].title, mlist[i].artist, mlist[i].genre);
    }

    fclose(fp);
    printf("데이터를 성공적으로 내보냈습니다.\n");
}
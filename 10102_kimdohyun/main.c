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
        printf("�޴� �Է� : ");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
            break;
        }
    }

    return 0;
}

void menu() {
    puts("========================");
    puts("1. �߰� 2. ��ȸ 3. ���� 4. ���� 5. ������ �ҷ����� 6. ������ �������� 7. ����");
    puts("========================");
}

MUSIC create_record() {
    MUSIC m;
    printf("=========����=========\n");
    printf("���� : ");
    fgets(m.title, sizeof(m.title), stdin);
    m.title[strcspn(m.title, "\n")] = '\0';
    printf("���� : ");
    fgets(m.artist, sizeof(m.artist), stdin);
    m.artist[strcspn(m.artist, "\n")] = '\0';
    printf("�帣 : ");
    fgets(m.genre, sizeof(m.genre), stdin);
    m.genre[strcspn(m.genre, "\n")] = '\0';

    return m;
}

void select_record() {
    printf("============��ȸ============\n\n");
    if (CNT == 0) {
        printf("����� ���ڵ尡 �����ϴ�.\n");
        return;
    }

    for (int i = 0; i < CNT; i++) {
        printf("============��ȣ : %d============\n", i + 1);
        printf("���� : %s\n", mlist[i].title);
        printf("���� : %s\n", mlist[i].artist);
        printf("�帣 : %s\n", mlist[i].genre);
    }
}

void delete_record() {
    char title[20];
    int i, found = 0;

    printf("=========����=========\n");
    printf("������ �� ����: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; i < CNT; i++) {
        if (strcmp(title, mlist[i].title) == 0) {
            found = 1;
            printf("%s�� ���� ��...\n", title);
            break;
        }
    }

    if (!found) {
        printf("%s�� ã�� �� �����ϴ�.\n", title);
        return;
    }

    for (int j = i; j < CNT - 1; j++) {
        strcpy(mlist[j].title, mlist[j + 1].title);
        strcpy(mlist[j].artist, mlist[j + 1].artist);
        strcpy(mlist[j].genre, mlist[j + 1].genre);
    }

    CNT--;
    printf("%s�� ���� �Ϸ��Ͽ����ϴ�.\n", title);
}

void update_record() {
    char title[20];
    int i, found = 0;

    printf("=========����=========\n");
    printf("������ �� ����: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; i < CNT; i++) {
        if (strcmp(title, mlist[i].title) == 0) {
            found = 1;
            printf("���ο� ����: ");
            fgets(mlist[i].title, sizeof(mlist[i].title), stdin);
            mlist[i].title[strcspn(mlist[i].title, "\n")] = '\0';
            printf("���ο� ����: ");
            fgets(mlist[i].artist, sizeof(mlist[i].artist), stdin);
            mlist[i].artist[strcspn(mlist[i].artist, "\n")] = '\0';
            printf("���ο� �帣: ");
            fgets(mlist[i].genre, sizeof(mlist[i].genre), stdin);
            mlist[i].genre[strcspn(mlist[i].genre, "\n")] = '\0';
            printf("%s�� ���� �Ϸ��Ͽ����ϴ�.\n", title);
            break;
        }
    }

    if (!found) {
        printf("%s�� ã�� �� �����ϴ�.\n", title);
    }
}

void import_records() {
    FILE* fp;
    char filename[100];
    char line[100];
    char* token;
    int count = 0;

    printf("=========������ �ҷ�����=========\n");
    printf("�ҷ��� ���ϸ��� �Է��ϼ���: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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
    printf("�����͸� ���������� �ҷ��Խ��ϴ�.\n");
}

void export_records() {
    FILE* fp;
    char filename[100];

    printf("=========������ ��������=========\n");
    printf("������ ���ϸ��� �Է��ϼ���: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(fp, "����,����,�帣\n");

    for (int i = 0; i < CNT; i++) {
        fprintf(fp, "%s,%s,%s\n", mlist[i].title, mlist[i].artist, mlist[i].genre);
    }

    fclose(fp);
    printf("�����͸� ���������� �����½��ϴ�.\n");
}
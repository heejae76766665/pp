#include <stdio.h>
#include <string.h>

#define TITLE_SIZE 50
#define NAME_SIZE 50
#define PUBLISHER_SIZE 50
#define MAX_BOOKS 30

typedef struct BOOK {
    char title[TITLE_SIZE];
    char author[NAME_SIZE];
    char publisher[PUBLISHER_SIZE];
} BOOK;

void add_record(BOOK library[], int *count);
void search_record(BOOK library[], int count);
void save_file(BOOK library[], int count);
void load_file(BOOK library[], int *count);
void menu(void);

int main(void)
{
    BOOK library[MAX_BOOKS];
    int count = 0;
    int menu_num;

    while (1)
    {
        menu();

        printf("선택 : ");
        scanf("%d", &menu_num);
        getchar();

        switch (menu_num)
        {
        case 1:
            add_record(library, &count);
            break;

        case 2:
            search_record(library, count);
            break;

        case 3:
            save_file(library, count);
            break;

        case 4:
            load_file(library, &count);
            break;

        case 5:
            printf("프로그램 종료\n");
            return 0;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}

void menu(void)
{
    printf("\n====================\n");
    printf("1. 추가\n");
    printf("2. 검색\n");
    printf("3. 파일로 저장\n");
    printf("4. 파일에서 읽기\n");
    printf("5. 종료\n");
    printf("====================\n");
}

void add_record(BOOK library[], int *count)
{
    if (*count >= MAX_BOOKS)
    {
        printf("저장 공간이 없습니다.\n");
        return;
    }

    printf("도서명 : ");
    fgets(library[*count].title, TITLE_SIZE, stdin);
    library[*count].title[strcspn(library[*count].title, "\n")] = '\0';

    printf("저자 : ");
    fgets(library[*count].author, NAME_SIZE, stdin);
    library[*count].author[strcspn(library[*count].author, "\n")] = '\0';

    printf("출판사 : ");
    fgets(library[*count].publisher, PUBLISHER_SIZE, stdin);
    library[*count].publisher[strcspn(library[*count].publisher, "\n")] = '\0';

    (*count)++;
}

void search_record(BOOK library[], int count)
{
    char title[TITLE_SIZE];
    int i;

    printf("검색할 제목 : ");
    fgets(title, TITLE_SIZE, stdin);
    title[strcspn(title, "\n")] = '\0';

    for (i = 0; i < count; i++)
    {
        if (strcmp(title, library[i].title) == 0)
        {
            printf("\n도서 발견\n");
            printf("제목 : %s\n", library[i].title);
            printf("저자 : %s\n", library[i].author);
            printf("출판사 : %s\n", library[i].publisher);
            return;
        }
    }

    printf("찾는 책이 없습니다.\n");
}

void save_file(BOOK library[], int count)
{
    FILE *fp;
    int i;

    fp = fopen("library.txt", "w");

    if (fp == NULL)
    {
        printf("파일 저장 실패\n");
        return;
    }

    fprintf(fp, "%d\n", count);

    for (i = 0; i < count; i++)
    {
        fprintf(fp, "%s\n", library[i].title);
        fprintf(fp, "%s\n", library[i].author);
        fprintf(fp, "%s\n", library[i].publisher);
    }

    fclose(fp);

    printf("파일 저장 완료\n");
}

void load_file(BOOK library[], int *count)
{
    FILE *fp;
    int i;

    fp = fopen("library.txt", "r");

    if (fp == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fscanf(fp, "%d\n", count);

    for (i = 0; i < *count; i++)
    {
        fgets(library[i].title, TITLE_SIZE, fp);
        library[i].title[strcspn(library[i].title, "\n")] = '\0';

        fgets(library[i].author, NAME_SIZE, fp);
        library[i].author[strcspn(library[i].author, "\n")] = '\0';

        fgets(library[i].publisher, PUBLISHER_SIZE, fp);
        library[i].publisher[strcspn(library[i].publisher, "\n")] = '\0';
    }

    fclose(fp);

    printf("파일 읽기 완료 (%d권)\n", *count);
}
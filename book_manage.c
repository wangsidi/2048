#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BOOK_NAME_LEN 20
#define FILE_NAME_LEN 20

long _road(char *);
void _write(char *);
void _change(void);
void _out(void);
void _add(void);
void _del(void);
char *s_gets(char *, int);

//书籍结构体
typedef struct
{
    int no;
    char name[20];
    double price;
} book;

//书籍库结构体
static struct
{
    long COUNT;
    book *BOOK;
} Library;

int main(void)
{
    char fname[FILE_NAME_LEN];

    printf("请输入文件名: ");
    s_gets(fname, FILE_NAME_LEN);

    char choose;

    printf("a.search                b.change\n");
    printf("c.add                   d.delete\n");
    printf("e.quit\n");
    printf("Please input your choose: ");
    while ((choose = getchar()) != 'e')
    {
        while (getchar() != '\n')
            continue;
        system("cls");
        switch (choose)
        {
        case 'a':
            _road(fname);
            _out();
            break;

        case 'b':
            _road(fname);
            _change();
            _write(fname);
            _out();
            break;

        case 'c':
            _road(fname);
            _add();
            _write(fname);
            _out();
            break;

        case 'd':
            _road(fname);
            _del();
            _write(fname);
            _out();
            break;

        default:
            break;
        }
        while (getchar() != '\n')
            continue;
        printf("a.search                b.change\n");
        printf("c.add                   d.delete\n");
        printf("e.quit\n");
        printf("Please input your choose: ");
    }

    system("pause");
    return 0;
}

char *s_gets(char *fname, int len)
{
    char *rs;
    char *find;

    rs = fgets(fname, len, stdin);
    if (rs)
    {
        find = strchr(fname, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }

    return rs;
}

long _road(char *fname)
{
    FILE *fp;
    long item;

    if ((fp = fopen(fname, "rb")) == NULL)
    {
        //创建文件
        fp = fopen(fname, "wb");
        if (fp)
            fprintf(stdout, "RAOD SUCCESS!\n");
        else
            fprintf(stderr, "CAN NOT CREATE %s! \n", fname);
        fclose(fp);
        return 0;
    }

    //读取文件
    fprintf(stdout, "RAODING!\n");
    fseek(fp, 0L, SEEK_END);
    Library.COUNT = ftell(fp) / sizeof(book);
    Library.BOOK = (book *)malloc(Library.COUNT * sizeof(book)); //分配内存
    rewind(fp);
    item = fread(Library.BOOK, sizeof(book), Library.COUNT, fp);

    fclose(fp);

    return item;
}

void _write(char *fname)
{
    FILE *fp;

    if ((fp = fopen(fname, "wb")) != NULL)
        printf("OPEN %s SUCCESS! \n", fname);
    fwrite(Library.BOOK, sizeof(book), Library.COUNT, fp);
    fclose(fp);

    return;
}

void _out(void)
{
    for (int i = 0; i < Library.COUNT; i++)
        printf("%03d\t%-20s%.2f\n", Library.BOOK[i].no, Library.BOOK[i].name, Library.BOOK[i].price);

    return;
}

void _add(void)
{
    book data;

    printf("Please input the number: ");
    scanf("%d", &data.no);
    for (int i = 0L; i < Library.COUNT; i++)
        if (Library.BOOK[i].no == data.no)
        {
            printf("THE NUMBER IS USED! \n");
            return;
        }

    while (getchar() != '\n')
        continue;
    printf("Please input the name: ");
    s_gets(data.name, BOOK_NAME_LEN);
    printf("Please input the price: ");
    scanf("%lf", &data.price);

    Library.BOOK = (book *)realloc((book *)Library.BOOK, ++Library.COUNT * sizeof(book));
    Library.BOOK[Library.COUNT - 1] = data;

    return;
}

void _del(void)
{
    char name[BOOK_NAME_LEN];

    printf("Please input the name what you want to delete: ");
    s_gets(name, BOOK_NAME_LEN);

    long i;

    for (i = 0L; i < Library.COUNT; i++)
        if (strcmp(Library.BOOK[i].name, name) == 0)
            break;
    if (i > Library.COUNT - 1)
        printf("CAN NOT FIND THE BOOK NAMED %s!", name);
    else
    {
        for (int j = i; j < Library.COUNT - 1; j++)
            Library.BOOK[j] = Library.BOOK[j + 1];
    }

    Library.BOOK = (book *)realloc((book *)Library.BOOK, --Library.COUNT * sizeof(book));

    return;
}

void _change(void)
{
    int no;
    char name_changed[BOOK_NAME_LEN];
    double price_changed;

    printf("请输入要修改的图书编号: ");
    scanf("%d", &no);

    long i;

    for (i = 0L; i < Library.COUNT; i++)
        if (Library.BOOK[i].no == no)
            break;
    if (i > Library.COUNT - 1)
        printf("CAN NOT FIND THE BOOK!");
    else
    {
        while (getchar() != '\n')
            continue;
        printf("Please input the name need changed: ");
        s_gets(name_changed, BOOK_NAME_LEN);
        strcpy(Library.BOOK[i].name, name_changed);
        printf("Please input the price need changed:");
        scanf("%lf", &price_changed);
        Library.BOOK[i].price = price_changed;
    }

    return;
}
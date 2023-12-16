#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN_NAME 15
#define MAX_LEN_ID 15
#define MAX_LEN_PASSWORD 15
#define TYPE_STUDENT 0
#define TYPE_TEACHER 1
#define LEN sizeof(Stu)
#define ATTEMPT_TIMES_LIMIT 5

typedef struct Student {
	char name[MAX_LEN_NAME];
	char id[MAX_LEN_ID];
	float score_alg;
	float score_cal;
	float score_prog;
	float score_aver;
	int rank;
	struct Student *next;
} Stu;

typedef struct User {
	char username[MAX_LEN_NAME];
	char userpassword[MAX_LEN_PASSWORD];
	int usertype;
	struct User *next;
} User;

int menu_User(void);
int menu_Student();
int menu_Teacher();
User* read_file_for_login(User *head);
User* read_file_for_info(User *head);
void watch_One_Info(char *id);
void watch_All_Info(User *head);
void record_Scores(User *head);
void modify_Scores(User *haed);
void delete_Scores(User *head);
void search_Student_By_Id();
User* auth(User *head, int attempts);
void sort_Info(User *head, int num);

int main() {
	User *head_info = NULL;
	head_info = (User *)malloc(LEN);
	head_info = read_file_for_info(head_info);

	User *head_login = NULL;
	head_login = (User *)malloc(LEN);
	head_login = read_file_for_login(head_login);

	User *user_login = auth(head_login, ATTEMPT_TIMES_LIMIT);
	if (user_login == NULL) {
		printf("输入错误次数过多，请稍后再试\n");
		return 0;
	}

	if (user_login->usertype == TYPE_TEACHER) {
		while (1) {
			int i = menu_Teacher();
			switch(i) {
				case 1: {
					int j = menu_Teacher();
					switch(j) {
						case 1:
							system("cls");
							record_Scores(head_info);
							break;
						case 2:
							system("cls");
							modify_Scores(head_info);
							break;
						case 3:
							system("cls");
							delete_Scores(head_info);
							break;
						case 0:
							system("cls");
							printf("\t\t\tgoodbye!");
							// sleep(1000);
							return 0;							
					}
				}
				case 2:
					system("cls");
					printf("\n\n\n");
					char id_to_search[MAX_LEN_ID];
					printf("\t\t\t请输入你要查找的学生姓名:");
					scanf("%s", id_to_search);
					watch_One_Info(id_to_search);
					break;
				case 3: {
					int k = menu_Teacher();
					if (k >= 1 && k <= 5) {
						system("cls");
						sort_Info(head_info, k);
					}
					else {
						system("cls");
						printf("\t\t\tgoodbye!");
						// sleep(1000);
						return 0;
					}
				}
					
		}
	}
	}
	else {
		int i = menu_Student();
		switch(i) {
			case 1: 
				watch_One_Info(user_login->username);
				break;
			case 0:
				system("cls");
				printf("\t\t\tgoodbye!");
				// sleep(1000);
				return 0;
		}
	}
	
	return 0;
}


int menu_Student() {
	system("title 学生成绩管理系统");
	printf("\n\n");
	printf("\t\t\t                         学生菜单\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  查看个人成绩信息                                      *\n");
	printf("\t\t\t*                0.  退出系统                                                 *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t				   输入你的操作:");
	int operation;
	scanf("%d", &operation);
	return operation;
}


int menu_Teacher() {
	system("title 学生成绩管理系统");
	printf("\n\n");
	printf("\t\t\t                         教师菜单\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  录入或修改学生成绩                                        *\n");
	printf("\t\t\t*                2.  查找单个学生成绩信息                                      *\n");
	printf("\t\t\t*                3.  查看总体学生成绩信息                                      *\n");
	printf("\t\t\t*                0.  退出系统                                                 *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t				   输入你的操作:");
	int operation;
	scanf("%d", &operation);
	return operation;
}

int menu_Teacher_Operation_1(int operation) {
	system("title 学生成绩管理系统");
	printf("\n\n");
	printf("\t\t\t                         教师菜单\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  录入学生成绩                                        *\n");
	printf("\t\t\t*                2.  修改学生成绩                                      *\n");
	printf("\t\t\t*                3.  删除学生成绩                                     *\n");
	printf("\t\t\t*                0.  退出系统                                                 *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t				   输入你的操作:");
	int operation_2;
	scanf("%d", &operation_2);
	return operation_2;
}

int menu_Teacher_Operation_3(int operation) {
	system("title 学生成绩管理系统");
	printf("\n\n");
	printf("\t\t\t                         教师菜单\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t*                1.  按学号排序                                               *\n");
	printf("\t\t\t*                2.  按均分排序                                               *\n");
	printf("\t\t\t*                3.  按线代成绩排序                                           *\n");
	printf("\t\t\t*                4.  按数分成绩排序                                           *\n");
	printf("\t\t\t*                5.  按C语言成绩排序                                          *\n");
	printf("\t\t\t*                0.  退出程序                                                 *\n");
	printf("\t\t\t******************************************************************************\n");
	printf("\t\t\t				   输入你的操作:");
	int operation_3;
	scanf("%d", &operation_3);
	return operation_3;
}

User* auth(User *head, int attempts) {
	if (attempts == 0) {
        printf("Exceeded maximum login attempts. Authentication failed.\n");
        return NULL;
    }
	char InputUsername[MAX_LEN_NAME];
    char InputPassword[MAX_LEN_PASSWORD];
    printf("Input your username here : ");scanf("%s", InputUsername);
	printf("Input your password here : ");scanf("%s", InputPassword);
    struct User *current = head;
    while (current != NULL) {
        if (strcmp(InputUsername, current->username) == 0 && strcmp(InputPassword, current->userpassword) == 0) {
            return current; // 返回指针
        }
        current = current->next;
    }
	printf("Invalid username or password. Remaining attempts: %d\n", attempts - 1);
    // return(auth(User *head, attempts - 1));
}

User* read_file_for_login(User *head) {
	User *nil=NULL, *s;
	s=head;
	nil=s;
	const char* filename="stuID.txt",*mode="r";
	FILE* fp = fopen(filename, mode);
	if (fp == NULL)
	{
		printf("文件不能正常打开\n");
		return (0);
	}
	while(1)
	{
	fgets(nil->username,15,fp);
	fgets(nil->userpassword,15,fp);
	for(int i=14;nil->username[i]==' ';i--)
	{
		nil->username[i]='\0';
	}
	for(int i=14;nil->userpassword[i]==' ';i--)
	{
		nil->userpassword[i]='\0';
	}
	s=(User*)malloc(sizeof(User));
	nil->next=s;
	nil=nil->next;
	if(!feof(fp))  // 终止符
	{
		if(fp)
			fclose(fp);
		nil=NULL;
		break; 
	}
	}
	return head;
}

User* read_file_for_info(User *head) {
	Stu *nil, * s;
	s = head;
	nil = s;
	const char *filename = "stuScores.txt", *mode = "r";
	FILE* fp = fopen(filename, mode);
	if (fp == NULL)
	{
		printf("文件不能正常打开\n");
		return (0);
	}
	while (1)
	{
		fgets(nil->name, 15, fp);
		fgets(nil->id, 15, fp);
		fread(&(nil->score_alg),6,1,fp);
		fread(&(nil->score_cal),6,1,fp);
		fread(&(nil->score_prog),6,1,fp);
		for (int i = 14; nil->name[i] == ' '; i--)
		{
			nil->name[i] = '\0';
		}
		for (int i = 14; nil->id[i] == ' '; i--)
		{
			nil->id[i] = '\0';
		}
		nil->score_aver=(nil->score_alg+nil->score_cal+nil->score_prog)/3;
		s = (Stu*)malloc(sizeof(Stu));
		nil->next = s;
		nil = nil->next;
		if (!feof(fp))
		{
			if (fp)
				fclose(fp);
			nil = NULL;
			break;
		}
	}
	return head;
}

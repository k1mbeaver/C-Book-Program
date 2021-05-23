#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define S_SIZE 100
#define F_SIZE 300

typedef struct BOOK
{
	char chInformation[F_SIZE];
	struct BOOK* link;
} BOOK;

void menu();
void Wait();
void BookInformation();
void ErrRestart();
void NoInformation();
void SearchResult();
void CantOpen(char* GetchTxtBook);
void MenuAllIndex(BOOK* GetBorrowHead, BOOK* GetnewNode);
void BookName();
void BookWriter();
void BookYear();
void Retry();
void AddComplete();
void DeleteComplete();
void MenuRewrite(BOOK* GetBorrowHead, FILE* GetFiletxt, char* GetchBookIndex);
void ReturnNode(BOOK* GetBorrowHead, BOOK* GetnewNode, BOOK* Gethead);
void SimilarList(BOOK* newNode, BOOK* BorrowHead, char* chTxtBook, FILE* Filetxt2, char* chBookIndex2);
int NoBook(int GetnCount, FILE* GetFiletxt, char* GetchBookIndex, char* GetchCount2, char* GetchBuffer);
void MakeBookInformation(char* GetchBuffer, char* GetchTxtBook, char* GetchTxtWriter, int GetnTxtYear);

int main()
{
	FILE* Filetxt = NULL; // 파일을 만들고, 수정하고, 불러오기 위해서
	FILE* Filetxt2 = NULL; // 파일을 만들고, 수정하고, 불러오기 위해서

	BOOK* BorrowHead = NULL;
	BOOK* head = NULL;
	BOOK* tail = NULL;
	BOOK* newNode = NULL;
	BOOK* delNode = NULL;
	BOOK* delNextNode = NULL;
	BOOK* befNode = NULL;
	BOOK* nextNode = NULL;

	BorrowHead = (BOOK*)malloc(sizeof(BOOK));

	BorrowHead->link = NULL;

	char chBookIndex[10] = "List";
	char chBookIndex2[10] = "Similar";
	char chBuffer[F_SIZE];
	char chTxtBook[S_SIZE];
	char chTxtWriter[S_SIZE];
	char chCount[S_SIZE];
	char chCount2[F_SIZE];
	int nIndex;
	int nCount = 0;
	int nTxtYear;
	int nYear;
	int nButton;
	int nLine = 1;
	int nResult = 0;


	printf("=====================================================================================================================\n");
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t환영합니다. 도서관리 프로그램입니다.\n");
	printf("=====================================================================================================================\n");

	//프로젝트 폴더에 List 텍스트 파일이 없는 경우
	if ((Filetxt = fopen(chBookIndex, "r")) == NULL)
	{
		Filetxt = fopen(chBookIndex, "w");
		fprintf(Filetxt, "\0");
		fclose(Filetxt);
	}
	//List 텍스트 파일에서 정보를 읽어온 다음에 연결리스트를 만들어 놓는다.

	//여기부터
	Filetxt = fopen(chBookIndex, "r"); // Index 파일을 읽기모드로 연다.

	while (fgets(chBuffer, F_SIZE, Filetxt) != NULL)
	{

		newNode = (BOOK*)malloc(sizeof(BOOK)); // 노드에 동적 메모리 할당

		strcpy(newNode->chInformation, chBuffer);// 노드안에 정보를 넣는다.

		if (BorrowHead->link == NULL) // 리스트가 비어있으면
		{
			BorrowHead->link = newNode; // 새로운 노드를 첫번쨰 노드로 만든다.
		}
		else // 리스트가 비어있지 않으면
		{
			tail->link = newNode;  // 새로운 노드를 이전 노드의 끝에 붙인다.
		}
		newNode->link = NULL; // 새로운 노드의 다음주소는 NULL;
		tail = newNode;
	}
	fclose(Filetxt);
	//여기까지

	while (1)
	{
		nButton = 0;

		//메뉴창 실행
		menu();

		//사용 할 기능 선택
		printf("사용할 기능의 번호를 입력하고 Enter를 눌러 주세요(5번을 누르거나 다른것을 누를시 프로그램이 종료됩니다) : ");
		scanf("%d", &nButton);

		// 전체 도서 목록 
		if (nButton == 1)
		{
			Wait();
			system("cls");
			MenuAllIndex(BorrowHead, newNode);//메인 함수 도입부분에서 만들어 졌던 리스트를 그대로 읽어온뒤 출력
			system("pause");
		}

		// 도서 추가하기 (현재 만들어진 연결리스트에다가 추가 후 저장하기에 가서 파일로 저장)
		else if (nButton == 2)
		{
			Wait();
			system("cls");
			BookName();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			if (chTxtBook[0] == ' ')//입력 받을때 맨 처음이 공백이면
			{
				Retry();
				continue;
			}

			BookWriter();
			getchar(); 
			scanf("%[^\n]", &chTxtWriter);

			if (chTxtWriter[0] == ' ')//입력 받을때 맨 처음이 공백이면
			{
				Retry();
				continue;
			}

			BookYear();
			scanf("%d", &nTxtYear);

			if (nTxtYear >= 0 && nTxtYear <= 9999)
			{
				MakeBookInformation(chBuffer, chTxtBook, chTxtWriter, nTxtYear);
			}
			

			else
			{
				Retry();
				continue;
			}
			
			//입력 받은 정보를 연결리스트에 추가 한 다음 텍스트 파일에 덮어씌우기
			//여기부터
			newNode = (BOOK*)malloc(sizeof(BOOK)); // 노드에 동적 메모리 할당

			strcpy(newNode->chInformation, chBuffer);// 노드안에 정보를 넣는다.

			if (BorrowHead->link == NULL) // 리스트가 비어있으면
			{
				BorrowHead->link = newNode; // 새로운 노드를 첫번쨰 노드로 만든다.
			}
			else // 리스트가 비어있지 않으면
			{
				tail->link = newNode;  // 새로운 노드를 이전 노드의 끝에 붙인다.
			}

			newNode->link = NULL; // 새로운 노드의 다음주소는 NULL;
			tail = newNode;

			// 텍스트 파일에 다시 뒤집어 씌우기

			MenuRewrite(BorrowHead, Filetxt, chBookIndex);

			AddComplete();
		}

		// 도서 정보 삭제
		else if (nButton == 3)
		{
			Wait();
			system("cls");
			BookName();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			if (chTxtBook[0] == ' ')//입력 받을때 맨 처음이 공백이면
			{
				Retry();
				continue;
			}

			BookWriter();
			getchar();
			scanf("%[^\n]", &chTxtWriter);
			if (chTxtWriter[0] == ' ')//입력 받을때 맨 처음이 공백이면
			{
				Retry();
				continue;
			}

			BookYear();
			scanf("%d", &nTxtYear);

			if (nTxtYear >= 0 && nTxtYear <= 9999)
			{
				MakeBookInformation(chBuffer, chTxtBook, chTxtWriter, nTxtYear);
			}

			else
			{
				Retry();
				continue;
			}

			//없는 값을 입력한 경우?

			nResult = NoBook(nCount, Filetxt, chBookIndex, chCount2, chBuffer);//함수 안에서 nCount 값을 구한뒤 nResult에 넣기 0이면 if문 들어가고 아니면 넘어가기

			if (nResult == 0) // 0이면
			{
				NoInformation();
				continue;
			}
			//여기부터
			delNode = (BOOK*)malloc(sizeof(BOOK));

			delNode = BorrowHead->link; // 맨 처음부터 노드를 찾아가야하니 삭제할 노드의 위치는 헤드의 다음
			befNode = BorrowHead; // 현재 처음이니 삭제할 노드의 전 노드의 주소는 헤드
			nextNode = delNode->link; // 삭제할 노드의 다음노드의 주소

			int nIndex = 0; // 처음을 표현

			while (delNode != NULL) // 노드가 NULL일때까지
			{
				if (strstr(delNode->chInformation, chBuffer) != NULL) // 노드안에 있는 chInformation안에 아까 입력한 chBuffer가 있을 때
				{
					if (delNode->link == NULL) // 다음 노드가 없을 때
					{
						if (nIndex == 0) // 노드가 하나만 있을 때
						{
							free(delNode);// 회수

							BorrowHead->link = NULL;
							tail = BorrowHead;

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
						else //맨 끝에 있을 때
						{
							befNode->link = NULL;// 이전 노드의 주소를 끝으로
							free(delNode);// 회수 후
							tail = befNode;

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
					}
					else // 다음 노드가 있을 때
					{
						if (nIndex == 0) // 처음 일 때
						{
							BorrowHead->link = nextNode; // 다음 노드를 처음으로
							free(delNode);// 회수

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);

							break;
						}
						else // 처음이 아닐 때
						{
							befNode->link = nextNode; // 이전 노드의 link를 현재 노드 다음 노드의 주소로
							free(delNode);// 회수

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
					}

				}

				befNode = delNode; // 이전노드와 현재노드가 같게
				delNode = delNode->link; // 그리고 현재노드는 다음노드로 넘어가기
				nextNode = delNode->link; // 그리고 삭제할 노드의 다음노드의 주소
				nIndex++;// 다음회수로 넘어가면 사용안함
			}
			//여기까지
		}

		// 책 검색하기
		else if (nButton == 4)
		{
		    Wait();
			system("cls");
			BookInformation();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			//맨앞에 공백이 있는경우

			if (chTxtBook[0] == ' ')
			{
				Retry();
				continue;
			}

			//없는 값을 입력한 경우?

			nResult = NoBook(nCount, Filetxt, chBookIndex, chCount2, chTxtBook);

			if (nResult == 0) // 0이면
			{
				NoInformation();
				continue;
			}

			// 중복되는 내용들이 있을 때

			Filetxt = fopen(chBookIndex, "r"); // List 파일을 읽기모드로 연다
			Filetxt2 = fopen(chBookIndex2, "w"); // SImilar 파일을 쓰기모드로 연다

			SimilarList(newNode, BorrowHead, chTxtBook, Filetxt2, chBookIndex2);

			while (fgets(chCount2, F_SIZE, Filetxt2)) // 파일의 맨 끝까지 갈 때 까지 진행
			{
				printf("=>\t%s\n", chCount2);
			}

			fclose(Filetxt2);
			fclose(Filetxt);

			system("pause");
		}
		// 종료
		else if (nButton == 5)
		{
			break;
		}
		// 오타
		else
		{
		    ErrRestart();
			break;
		}
	}

	ReturnNode(BorrowHead, newNode, head);
	return 0;
}

void menu()
{
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t\t메뉴\t\t\n");
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t1. 전체 도서 목록 불러오기\t\t\n"); // 연결리스트, 완료
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t2. 도서 추가하기\t\t\n"); // 연결리스트 사용 , 도서 추가, 추가 후 5번에 가서 연결리스트를 다시 파일로 재저장, 완료
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t3. 도서 삭제하기\t\t\n"); // 연결리스트 사용 , 완료, 근데 없는 책을 삭제할때는 어떤걸로 출력해야하는지?
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t4. 도서 정보를 검색\t\t\n"); // 파일 입출력 // 완료 
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t5. 종료\t\t\n"); // 완료
	printf("=====================================================================================================================\n");
}

void ErrRestart()
{
	printf("\n\t\t\t\t\t잘못 입력 하셨습니다. 다시 실행해주세요\n\n");
	printf("\n");
}

void Wait()
{
	printf("\n\t\t\t\t\t 잠시만 기다려 주세요....\n\n");
}

void SearchResult()
{
	printf("\n\t\t\t\t\t검색하신 책의 정보입니다.\n\n");
	printf("\n\t\t\t 제목\t/\t 작가\t/\t 출판년도 \n\n");
}

void CantOpen(char* GetchTxtBook)
{
	fprintf(stderr, "파일 %s를 열 수 없습니다.\n", GetchTxtBook);
}

void MenuAllIndex(BOOK* GetBorrowHead, BOOK* GetnewNode)
{
	int GetnCount = 1;
	if (GetBorrowHead->link == NULL)
	{
		printf("\n\t\t\t\t\t== 현재 대출한 책이 없습니다. ==\n\n");
	}
	else
	{
		GetnewNode = GetBorrowHead->link; //대출목록 리스트의 맨 처음으로
		printf("\n\t\t\t 제목\t/\t 작가\t/\t 출판년도 \n\n");
		while (GetnewNode != NULL) // 노드의 끝이 NULL이 아니면
		{
			printf("<%d>  %s\n\n", GetnCount, GetnewNode->chInformation); // 노드 안에 있는 책의 정보를 출력
			GetnewNode = GetnewNode->link; // 다음노드로 넘어간다.
			GetnCount++;
		}
	}
}

void BookName()
{
	printf("\n\t\t\t== 스페이스바를 누르고 엔터키 클릭시 메뉴로 다시 돌아갑니다. ==\n");
	printf("\n책의 이름(영문 100자 이내, 한글 30자 이내, 공백포함, 처음에 공백이 있으면 실행실패) : ");
}

void BookInformation()
{
	printf("\n\t\t\t== 스페이스바를 누르고 엔터키 클릭시 메뉴로 다시 돌아갑니다. ==\n");
	printf("\n책의 정보(이름, 작가, 출판년도 (영문 100자 이내, 한글 30자 이내, 공백포함, 처음에 공백이 있으면 실행실패)) : ");
}

void BookWriter()
{
	printf("\n\t\t\t== 스페이스바를 누르고 엔터키 클릭시 메뉴로 다시 돌아갑니다. ==\n");
	printf("\n책의 작가(영문 100자 이내, 한글 30자 이내, 공백포함, 처음에 공백이 있으면 실행실패) : ");
}

void BookYear()
{
	printf("\n출판 년도(0~9999까지의 숫자를 입력하여 주세요) : ");
}

void Retry()
{
	printf("\n\t\t\t\t\t== 다시 시도하여주세요 ==\n");
}

void AddComplete()
{
	printf("\n\t\t\t\t\t== 도서 추가가 완료 되었습니다!! ==\n\n");
}

void DeleteComplete()
{
	printf("\n\t\t\t\t\t== 삭제가 완료되었습니다. ==\n");
}

void NoInformation()
{
	printf("\n\t\t\t\t\t== 책의 정보가 없습니다. ==\n");
}

void MenuRewrite(BOOK* GetBorrowHead, FILE* GetFiletxt, char* GetchBookIndex)
{

	BOOK* newNode = (BOOK*)malloc(sizeof(BOOK)); // 노드에 동적 메모리 할당
	newNode = GetBorrowHead->link; //대출목록 리스트의 맨 처음으로

	GetFiletxt = fopen(GetchBookIndex, "w"); // 파일을 다시 쓰기 모드로 연다

	while (newNode != NULL)
	{
		fprintf(GetFiletxt, "%s", newNode->chInformation);
		newNode = newNode->link;
	}

	fclose(GetFiletxt);
}

void ReturnNode(BOOK* GetBorrowHead, BOOK* GetnewNode, BOOK* Gethead)
{
	GetnewNode = GetBorrowHead->link; //맨 처음노드부터 시작
	while (GetnewNode != NULL)//노드가 NULL이아니면
	{
		Gethead = GetnewNode->link;//head가 현재노드의 주소가 가리키는 값을 가지고
		free(GetnewNode); // 회수
		GetnewNode = Gethead; // 그리고 다시 돌려받기 = 계속 주소를 따라서 이동
	}
	free(GetBorrowHead);
}

void SimilarList(BOOK* GetnewNode, BOOK* GetBorrowHead, char* GetchTxtBook, FILE* GetFiletxt2, char* GetchBookIndex2)
{
	GetnewNode = GetBorrowHead->link; //대출목록 리스트의 맨 처음으로

	while (GetnewNode != NULL) // 노드의 끝이 NULL이 아니면
	{
		if (strstr(GetnewNode->chInformation, GetchTxtBook) != NULL)
		{
			fprintf(GetFiletxt2, "%s", GetnewNode->chInformation);
			GetnewNode = GetnewNode->link; // 다음노드로 넘어간다.
		}
		else
		{
			GetnewNode = GetnewNode->link; // 다음노드로 넘어간다.
		}
	}
	fclose(GetFiletxt2);

	GetFiletxt2 = fopen(GetchBookIndex2, "r");

	SearchResult();
}

int NoBook(int GetnCount, FILE* GetFiletxt, char* GetchBookIndex, char* GetchCount2, char* GetchBuffer)
{
	GetnCount = 0; //입력한 값과 같으면 숫자를 증가시키기만 함 다르면 계속 0
	GetFiletxt = fopen(GetchBookIndex, "r"); // 파일을 읽기 모드로 연다

	while (fgets(GetchCount2, F_SIZE, GetFiletxt)) // 파일의 맨 끝까지 갈 때 까지 진행
	{
		if (strstr(GetchCount2, GetchBuffer) != NULL)
		{
			GetnCount++;
		}

		else if (strstr(GetchCount2, GetchBuffer) == NULL)
		{
			continue;//계속 0으로 진행
		}
	}
	fclose(GetFiletxt);

	return GetnCount;

}

void MakeBookInformation(char *GetchBuffer, char *GetchTxtBook, char *GetchTxtWriter, int GetnTxtYear)
{
	sprintf(GetchBuffer, "%s / %s / %d\n", GetchTxtBook, GetchTxtWriter, GetnTxtYear);
}



//1. goto문은 사용하지 않는다.-> 완료
//2, 되도록 다 함수로 만들어서 사용
//3. system() 함수 이용해서 화면 클리어 -> 완료

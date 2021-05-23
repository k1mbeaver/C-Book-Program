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
	FILE* Filetxt = NULL; // ������ �����, �����ϰ�, �ҷ����� ���ؼ�
	FILE* Filetxt2 = NULL; // ������ �����, �����ϰ�, �ҷ����� ���ؼ�

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
	printf("\t\t\t\t\tȯ���մϴ�. �������� ���α׷��Դϴ�.\n");
	printf("=====================================================================================================================\n");

	//������Ʈ ������ List �ؽ�Ʈ ������ ���� ���
	if ((Filetxt = fopen(chBookIndex, "r")) == NULL)
	{
		Filetxt = fopen(chBookIndex, "w");
		fprintf(Filetxt, "\0");
		fclose(Filetxt);
	}
	//List �ؽ�Ʈ ���Ͽ��� ������ �о�� ������ ���Ḯ��Ʈ�� ����� ���´�.

	//�������
	Filetxt = fopen(chBookIndex, "r"); // Index ������ �б���� ����.

	while (fgets(chBuffer, F_SIZE, Filetxt) != NULL)
	{

		newNode = (BOOK*)malloc(sizeof(BOOK)); // ��忡 ���� �޸� �Ҵ�

		strcpy(newNode->chInformation, chBuffer);// ���ȿ� ������ �ִ´�.

		if (BorrowHead->link == NULL) // ����Ʈ�� ���������
		{
			BorrowHead->link = newNode; // ���ο� ��带 ù���� ���� �����.
		}
		else // ����Ʈ�� ������� ������
		{
			tail->link = newNode;  // ���ο� ��带 ���� ����� ���� ���δ�.
		}
		newNode->link = NULL; // ���ο� ����� �����ּҴ� NULL;
		tail = newNode;
	}
	fclose(Filetxt);
	//�������

	while (1)
	{
		nButton = 0;

		//�޴�â ����
		menu();

		//��� �� ��� ����
		printf("����� ����� ��ȣ�� �Է��ϰ� Enter�� ���� �ּ���(5���� �����ų� �ٸ����� ������ ���α׷��� ����˴ϴ�) : ");
		scanf("%d", &nButton);

		// ��ü ���� ��� 
		if (nButton == 1)
		{
			Wait();
			system("cls");
			MenuAllIndex(BorrowHead, newNode);//���� �Լ� ���Ժκп��� ����� ���� ����Ʈ�� �״�� �о�µ� ���
			system("pause");
		}

		// ���� �߰��ϱ� (���� ������� ���Ḯ��Ʈ���ٰ� �߰� �� �����ϱ⿡ ���� ���Ϸ� ����)
		else if (nButton == 2)
		{
			Wait();
			system("cls");
			BookName();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			if (chTxtBook[0] == ' ')//�Է� ������ �� ó���� �����̸�
			{
				Retry();
				continue;
			}

			BookWriter();
			getchar(); 
			scanf("%[^\n]", &chTxtWriter);

			if (chTxtWriter[0] == ' ')//�Է� ������ �� ó���� �����̸�
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
			
			//�Է� ���� ������ ���Ḯ��Ʈ�� �߰� �� ���� �ؽ�Ʈ ���Ͽ� ������
			//�������
			newNode = (BOOK*)malloc(sizeof(BOOK)); // ��忡 ���� �޸� �Ҵ�

			strcpy(newNode->chInformation, chBuffer);// ���ȿ� ������ �ִ´�.

			if (BorrowHead->link == NULL) // ����Ʈ�� ���������
			{
				BorrowHead->link = newNode; // ���ο� ��带 ù���� ���� �����.
			}
			else // ����Ʈ�� ������� ������
			{
				tail->link = newNode;  // ���ο� ��带 ���� ����� ���� ���δ�.
			}

			newNode->link = NULL; // ���ο� ����� �����ּҴ� NULL;
			tail = newNode;

			// �ؽ�Ʈ ���Ͽ� �ٽ� ������ �����

			MenuRewrite(BorrowHead, Filetxt, chBookIndex);

			AddComplete();
		}

		// ���� ���� ����
		else if (nButton == 3)
		{
			Wait();
			system("cls");
			BookName();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			if (chTxtBook[0] == ' ')//�Է� ������ �� ó���� �����̸�
			{
				Retry();
				continue;
			}

			BookWriter();
			getchar();
			scanf("%[^\n]", &chTxtWriter);
			if (chTxtWriter[0] == ' ')//�Է� ������ �� ó���� �����̸�
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

			//���� ���� �Է��� ���?

			nResult = NoBook(nCount, Filetxt, chBookIndex, chCount2, chBuffer);//�Լ� �ȿ��� nCount ���� ���ѵ� nResult�� �ֱ� 0�̸� if�� ���� �ƴϸ� �Ѿ��

			if (nResult == 0) // 0�̸�
			{
				NoInformation();
				continue;
			}
			//�������
			delNode = (BOOK*)malloc(sizeof(BOOK));

			delNode = BorrowHead->link; // �� ó������ ��带 ã�ư����ϴ� ������ ����� ��ġ�� ����� ����
			befNode = BorrowHead; // ���� ó���̴� ������ ����� �� ����� �ּҴ� ���
			nextNode = delNode->link; // ������ ����� ��������� �ּ�

			int nIndex = 0; // ó���� ǥ��

			while (delNode != NULL) // ��尡 NULL�϶�����
			{
				if (strstr(delNode->chInformation, chBuffer) != NULL) // ���ȿ� �ִ� chInformation�ȿ� �Ʊ� �Է��� chBuffer�� ���� ��
				{
					if (delNode->link == NULL) // ���� ��尡 ���� ��
					{
						if (nIndex == 0) // ��尡 �ϳ��� ���� ��
						{
							free(delNode);// ȸ��

							BorrowHead->link = NULL;
							tail = BorrowHead;

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
						else //�� ���� ���� ��
						{
							befNode->link = NULL;// ���� ����� �ּҸ� ������
							free(delNode);// ȸ�� ��
							tail = befNode;

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
					}
					else // ���� ��尡 ���� ��
					{
						if (nIndex == 0) // ó�� �� ��
						{
							BorrowHead->link = nextNode; // ���� ��带 ó������
							free(delNode);// ȸ��

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);

							break;
						}
						else // ó���� �ƴ� ��
						{
							befNode->link = nextNode; // ���� ����� link�� ���� ��� ���� ����� �ּҷ�
							free(delNode);// ȸ��

							DeleteComplete();
							MenuRewrite(BorrowHead, Filetxt, chBookIndex);
							break;
						}
					}

				}

				befNode = delNode; // �������� �����尡 ����
				delNode = delNode->link; // �׸��� ������� �������� �Ѿ��
				nextNode = delNode->link; // �׸��� ������ ����� ��������� �ּ�
				nIndex++;// ����ȸ���� �Ѿ�� ������
			}
			//�������
		}

		// å �˻��ϱ�
		else if (nButton == 4)
		{
		    Wait();
			system("cls");
			BookInformation();
			getchar();
			scanf("%[^\n]", &chTxtBook);

			//�Ǿտ� ������ �ִ°��

			if (chTxtBook[0] == ' ')
			{
				Retry();
				continue;
			}

			//���� ���� �Է��� ���?

			nResult = NoBook(nCount, Filetxt, chBookIndex, chCount2, chTxtBook);

			if (nResult == 0) // 0�̸�
			{
				NoInformation();
				continue;
			}

			// �ߺ��Ǵ� ������� ���� ��

			Filetxt = fopen(chBookIndex, "r"); // List ������ �б���� ����
			Filetxt2 = fopen(chBookIndex2, "w"); // SImilar ������ ������� ����

			SimilarList(newNode, BorrowHead, chTxtBook, Filetxt2, chBookIndex2);

			while (fgets(chCount2, F_SIZE, Filetxt2)) // ������ �� ������ �� �� ���� ����
			{
				printf("=>\t%s\n", chCount2);
			}

			fclose(Filetxt2);
			fclose(Filetxt);

			system("pause");
		}
		// ����
		else if (nButton == 5)
		{
			break;
		}
		// ��Ÿ
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
	printf("\t\t\t\t\t\t\t�޴�\t\t\n");
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t1. ��ü ���� ��� �ҷ�����\t\t\n"); // ���Ḯ��Ʈ, �Ϸ�
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t2. ���� �߰��ϱ�\t\t\n"); // ���Ḯ��Ʈ ��� , ���� �߰�, �߰� �� 5���� ���� ���Ḯ��Ʈ�� �ٽ� ���Ϸ� ������, �Ϸ�
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t3. ���� �����ϱ�\t\t\n"); // ���Ḯ��Ʈ ��� , �Ϸ�, �ٵ� ���� å�� �����Ҷ��� ��ɷ� ����ؾ��ϴ���?
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t4. ���� ������ �˻�\t\t\n"); // ���� ����� // �Ϸ� 
	printf("=====================================================================================================================\n");
	printf("\t\t\t\t\t\t5. ����\t\t\n"); // �Ϸ�
	printf("=====================================================================================================================\n");
}

void ErrRestart()
{
	printf("\n\t\t\t\t\t�߸� �Է� �ϼ̽��ϴ�. �ٽ� �������ּ���\n\n");
	printf("\n");
}

void Wait()
{
	printf("\n\t\t\t\t\t ��ø� ��ٷ� �ּ���....\n\n");
}

void SearchResult()
{
	printf("\n\t\t\t\t\t�˻��Ͻ� å�� �����Դϴ�.\n\n");
	printf("\n\t\t\t ����\t/\t �۰�\t/\t ���ǳ⵵ \n\n");
}

void CantOpen(char* GetchTxtBook)
{
	fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", GetchTxtBook);
}

void MenuAllIndex(BOOK* GetBorrowHead, BOOK* GetnewNode)
{
	int GetnCount = 1;
	if (GetBorrowHead->link == NULL)
	{
		printf("\n\t\t\t\t\t== ���� ������ å�� �����ϴ�. ==\n\n");
	}
	else
	{
		GetnewNode = GetBorrowHead->link; //������ ����Ʈ�� �� ó������
		printf("\n\t\t\t ����\t/\t �۰�\t/\t ���ǳ⵵ \n\n");
		while (GetnewNode != NULL) // ����� ���� NULL�� �ƴϸ�
		{
			printf("<%d>  %s\n\n", GetnCount, GetnewNode->chInformation); // ��� �ȿ� �ִ� å�� ������ ���
			GetnewNode = GetnewNode->link; // �������� �Ѿ��.
			GetnCount++;
		}
	}
}

void BookName()
{
	printf("\n\t\t\t== �����̽��ٸ� ������ ����Ű Ŭ���� �޴��� �ٽ� ���ư��ϴ�. ==\n");
	printf("\nå�� �̸�(���� 100�� �̳�, �ѱ� 30�� �̳�, ��������, ó���� ������ ������ �������) : ");
}

void BookInformation()
{
	printf("\n\t\t\t== �����̽��ٸ� ������ ����Ű Ŭ���� �޴��� �ٽ� ���ư��ϴ�. ==\n");
	printf("\nå�� ����(�̸�, �۰�, ���ǳ⵵ (���� 100�� �̳�, �ѱ� 30�� �̳�, ��������, ó���� ������ ������ �������)) : ");
}

void BookWriter()
{
	printf("\n\t\t\t== �����̽��ٸ� ������ ����Ű Ŭ���� �޴��� �ٽ� ���ư��ϴ�. ==\n");
	printf("\nå�� �۰�(���� 100�� �̳�, �ѱ� 30�� �̳�, ��������, ó���� ������ ������ �������) : ");
}

void BookYear()
{
	printf("\n���� �⵵(0~9999������ ���ڸ� �Է��Ͽ� �ּ���) : ");
}

void Retry()
{
	printf("\n\t\t\t\t\t== �ٽ� �õ��Ͽ��ּ��� ==\n");
}

void AddComplete()
{
	printf("\n\t\t\t\t\t== ���� �߰��� �Ϸ� �Ǿ����ϴ�!! ==\n\n");
}

void DeleteComplete()
{
	printf("\n\t\t\t\t\t== ������ �Ϸ�Ǿ����ϴ�. ==\n");
}

void NoInformation()
{
	printf("\n\t\t\t\t\t== å�� ������ �����ϴ�. ==\n");
}

void MenuRewrite(BOOK* GetBorrowHead, FILE* GetFiletxt, char* GetchBookIndex)
{

	BOOK* newNode = (BOOK*)malloc(sizeof(BOOK)); // ��忡 ���� �޸� �Ҵ�
	newNode = GetBorrowHead->link; //������ ����Ʈ�� �� ó������

	GetFiletxt = fopen(GetchBookIndex, "w"); // ������ �ٽ� ���� ���� ����

	while (newNode != NULL)
	{
		fprintf(GetFiletxt, "%s", newNode->chInformation);
		newNode = newNode->link;
	}

	fclose(GetFiletxt);
}

void ReturnNode(BOOK* GetBorrowHead, BOOK* GetnewNode, BOOK* Gethead)
{
	GetnewNode = GetBorrowHead->link; //�� ó�������� ����
	while (GetnewNode != NULL)//��尡 NULL�̾ƴϸ�
	{
		Gethead = GetnewNode->link;//head�� �������� �ּҰ� ����Ű�� ���� ������
		free(GetnewNode); // ȸ��
		GetnewNode = Gethead; // �׸��� �ٽ� �����ޱ� = ��� �ּҸ� ���� �̵�
	}
	free(GetBorrowHead);
}

void SimilarList(BOOK* GetnewNode, BOOK* GetBorrowHead, char* GetchTxtBook, FILE* GetFiletxt2, char* GetchBookIndex2)
{
	GetnewNode = GetBorrowHead->link; //������ ����Ʈ�� �� ó������

	while (GetnewNode != NULL) // ����� ���� NULL�� �ƴϸ�
	{
		if (strstr(GetnewNode->chInformation, GetchTxtBook) != NULL)
		{
			fprintf(GetFiletxt2, "%s", GetnewNode->chInformation);
			GetnewNode = GetnewNode->link; // �������� �Ѿ��.
		}
		else
		{
			GetnewNode = GetnewNode->link; // �������� �Ѿ��.
		}
	}
	fclose(GetFiletxt2);

	GetFiletxt2 = fopen(GetchBookIndex2, "r");

	SearchResult();
}

int NoBook(int GetnCount, FILE* GetFiletxt, char* GetchBookIndex, char* GetchCount2, char* GetchBuffer)
{
	GetnCount = 0; //�Է��� ���� ������ ���ڸ� ������Ű�⸸ �� �ٸ��� ��� 0
	GetFiletxt = fopen(GetchBookIndex, "r"); // ������ �б� ���� ����

	while (fgets(GetchCount2, F_SIZE, GetFiletxt)) // ������ �� ������ �� �� ���� ����
	{
		if (strstr(GetchCount2, GetchBuffer) != NULL)
		{
			GetnCount++;
		}

		else if (strstr(GetchCount2, GetchBuffer) == NULL)
		{
			continue;//��� 0���� ����
		}
	}
	fclose(GetFiletxt);

	return GetnCount;

}

void MakeBookInformation(char *GetchBuffer, char *GetchTxtBook, char *GetchTxtWriter, int GetnTxtYear)
{
	sprintf(GetchBuffer, "%s / %s / %d\n", GetchTxtBook, GetchTxtWriter, GetnTxtYear);
}



//1. goto���� ������� �ʴ´�.-> �Ϸ�
//2, �ǵ��� �� �Լ��� ���� ���
//3. system() �Լ� �̿��ؼ� ȭ�� Ŭ���� -> �Ϸ�

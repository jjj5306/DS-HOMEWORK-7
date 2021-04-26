/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	printf("2020039071 JoJunHwa\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {  //&headnode가 인수로 들어옴 headnode가 가리키는 주소를 변경 할 수 있다는 뜻
/* 리스트가 비어있지 않다면 freeList 함수를 호출해 리스트를 비움 */
	if (*h != NULL)
		freeList(*h);
	/* *h에 메모리를 할당하고 헤더노드를 NULL로 설정 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}


int freeList(headNode* h) {
	listNode* p;
	if (h->first == NULL)
	{
		free(h);
		return 0;
	}
	if (h->first->rlink == NULL) // 리스트에 값이 하나이면 그 값 free
		free(h->first);
	else // 아니라면 차례로 free
	{
		p = h->first->rlink;
		while (p != NULL)
		{
			free(p->llink);
			p = p->rlink;
		}
	}
	free(h); // 리스트의 값들을 다 free 한 후 headNode 도 free
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	if (h->first == NULL) //빈 리스트이면
	{
		node->key = key;
		node->rlink = NULL;
		h->first = node;
		node->llink = NULL;
	}
	else //리스트에 값이 한 개 이상이라면 
	{
		p = h->first;
		if (p->rlink == NULL)
		{
			p->rlink = node;
			node->llink = p;
			node->key = key;
			node->rlink = NULL;
			return 0;
		}
		while (p->rlink != NULL)
			p = p->rlink;
		// 반복문을 나왔으므로 p는 리스트의 가장 마지막 값을 가리키고 있다
		p->rlink = node;
		node->llink = p;
		node->key = key;
		node->rlink = NULL;
	}
	return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p = h->first;
	listNode* pre;
	if (p == NULL)
	{
		printf("Already empty list\n");
		return 0;
	}
	else if (p->rlink == NULL) //리스트에 원소가 하나라면
	{
		p->llink = NULL;
		free(p);
		h->first = NULL;
	}
	else
	{
		while (p->rlink != NULL)
			p = p->rlink;
		// 반복문을 나왔으므로 p는 리스트의 가장 마지막 값을 가리키고 있다
		pre = p->llink;
		p->llink = NULL;
		pre->rlink = NULL;
		free(p);
	}
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	if (h->first == NULL) //빈 리스트이면 
	{
		node->key = key;
		node->rlink = NULL;
		h->first = node;
		node->llink = NULL;
	}
	else
	{
		node->key = key;
		h->first->llink = node;
		node->rlink = h->first;
		h->first = node;
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first;
	if (p == NULL)
	{
		printf("Already empty list\n");
		return 0;
	}
	else if (p->rlink == NULL) //리스트에 원소가 하나라면
	{
		p->llink = NULL;
		free(p);
		h->first = NULL;
	}
	else
	{
		h->first = p->rlink;
		p->rlink->llink = NULL; //리스트의 두 번째 원소는 첫 원소이다
		p->rlink = NULL;
		p->llink = NULL;
		free(p);
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* p;
	listNode* pre;
	listNode* next;
	if (h->first == NULL || h->first->rlink == NULL) //리스트에 값이 없거나 하나라면 그냥 종료
		return 0;
	else if (h->first->rlink->rlink == NULL) //리스트에 값이 두 개라면 그 두개를 바꿈
	{
		p = h->first->rlink;
		p->llink = NULL;
		p->rlink = h->first;
		h->first->rlink = NULL;
		h->first->llink = p;
		h->first = p;
	}
	else //리스트에 값이 세 개 이상이라면
	{
		pre = h->first;
		p = pre->rlink;
		next = p->rlink;
		/* 맨 처음에는 이걸 한 번 실행한다*/
		p->rlink = pre;
		pre->llink = p;
		pre->rlink = NULL;
		if (next->rlink == NULL) //만약 리스트의 원소가 세 개이면 종료한다.
		{
			next->rlink = p;
			next->llink = NULL;
			h->first = next;
			return 0;
		}
		pre = p;
		p = next;
		next = next->rlink;
		while (next->rlink != NULL) // next가 리스트의 마지막 일 때 까지 반복
		{
			p->rlink = pre;
			pre->llink = p;
			pre = p;
			p = next;
			next = next->rlink;
		}
		/* 반복문을 나왔으므로 현재 상태는 h -> first 에서 p까지 invert 완료*/
		p->rlink = pre;
		pre->llink = p;
		p->llink = next;
		next->rlink = p;
		next->llink = NULL;
		h->first = next;
	}
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	node->key = key; //node에 memory allocation 후 key 값 저장
	if (h->first == NULL) //리스트에 값이 하나도 없다면
	{
		h->first = node;
		node->rlink = NULL;
		node->llink = NULL;
	}
	else if (h->first->rlink == NULL) //리스트에 값이 하나라면
	{
		if (h->first->key >= key) //그 값이 key보다 크거나 같다면 그 앞에 삽입
		{
			h->first->llink = node;
			node->rlink = h->first;
			h->first = node;
		}
		else //그 값이 key보다 작다면 그 뒤에 삽입
		{
			node->llink = h->first;
			h->first->rlink = node;
			node->rlink = NULL;
		}
	}
	else //리스트에 값이 두 개 이상이라면
	{
		if (h->first->key >= key) //리스트의 맨 앞에 삽입해야 한다면
		{
			h->first->llink = node;
			node->rlink = h->first;
			h->first = node;
		}
		else
		{
			p = h->first;
			while (p->key < key && p->rlink != NULL) //리스트의 값이 key보다 크거나 같거나 마지막에 도달 할 때 까지 p를 이동시킴
				p = p->rlink;
			// 반복문을 나왔으므로 리스트의 끝에 도달했거나 p의 전 위치에 삽입하면 된다.
			if (p->rlink == NULL) //리스트의 끝이면
			{
				p->rlink = node;
				node->llink = p;
				node->rlink = NULL;
			}
			else // 리스트의 끝이 아니라면 p 앞에 삽입
			{
				node->llink = p->llink;
				p->llink->rlink = node;
				node->rlink = p;
				p->llink = node;
			}
		}
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* p;
	listNode* pre;
	if (h->first == NULL) //리스트가 비어있다면
		printf("Already empty list\n");
	else if (h->first->rlink == NULL) //리스트에 원소가 하나이고
	{
		if (h->first->key == key) //그 원소가 key와 같다면
		{
			free(h->first); //그 원소를 free 한다
			h->first = NULL;
		}
		else
			printf("Not in list\n");
	}
	else //리스트에 원소가 두 개 이상이라면
	{
		if (h->first->key == key) //첫 번째 원소를 삭제해야 한다면
		{
			p = h->first->rlink;
			pre = h->first;
			p->llink = NULL;
			pre->rlink = NULL;
			h->first = p;
			free(pre);
		}
		else
		{
			p = h->first->rlink;
			pre = p->llink;
			while (p->rlink != NULL && p->key != key) //p가 key와 같거나 p가 리스트의 끝에 도달한다면 반복문 종료
			{
				p = p->rlink;
				pre = pre->rlink;
			}
			if (p->key == key) //p가 가리키는 key가 key와 같다면 그 부분 삭제, 그런데 그 부분이 리스트의 마지막 이면 다르게 처리
			{
				if (p->rlink == NULL)
				{
					pre->rlink = NULL;
					p->llink = NULL;
					free(p);
					return 1;
				}
				else
				{
					p->rlink->llink = pre;
					pre->rlink = p->rlink;
					p->rlink = NULL;
					p->llink = NULL;
					free(p);
					return 1;
				}
			}
			else
				printf("Not in list\n"); //아니라면 리스트에 없는 것
		}
	}
	return 1;
}

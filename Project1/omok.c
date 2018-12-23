// ���� �������̴�.
#define _CRT_SECURE_NO_WARNINGS
#define EMPTY 0
#define BLACK 1
#define WHITE 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <conio.h>
#include <windows.h>

void display_welcome(void);
void draw_board(void);
int check_omok(void);
void print_congratulation_msg(int);
void set_stone(int, int, int);
void scan_stone_position(int, int*, int*);

void AI_get_stone_position(int, int*, int*);

int board[15][15] = { 0, };

int main(void)
{
	int x, y,
		user_stone_color = 0,
		ai_stone_color = 0,
		winner = 0,
		now_turn = BLACK;

	//rand �õ� �ʱ�ȭ
	srand((unsigned)time(0));

	//�ܼ� ����� �Ķ���, �۾��� ������� �����Ѵ�.
	system("color 9f");

	//���� ȭ���� ����Ѵ�.
	display_welcome();

	//����ڿ��� �� ������ �����ϵ��� ��.
	while (1) {
		printf("�浹�� �鵹 �� �������� �Ͻðڽ��ϱ�?(��:%d, ��:%d) ", BLACK, WHITE);
		scanf("%d", &user_stone_color);
		if (user_stone_color == BLACK || user_stone_color == WHITE)
			break;
		printf("��ȿ�� ���� �ƴմϴ�. �ٽ� �Է����ֽʽÿ�.\n");
	}

	//�� ���� �ȳ��ϰ� 3�� ����ϱ�.
	if (user_stone_color == BLACK) {
		printf("3���� �浹�� ������ �����մϴ�...");
		ai_stone_color = WHITE;

	}
	else {
		printf("3���� �鵹�� ������ �����մϴ�...");
		ai_stone_color = BLACK;
	}
	for (int i = 0; i < 3; i++)
	{
		Sleep(500);
		printf("\n%d...\n", i + 1);
		Sleep(500);
	}

	//�ܼ� ����� ���, �۾��� ���������� �����Ѵ�.
	system("color f0");

	while (1) {
		//ȭ�� ����� (�̹� ��µƴ� ����ȭ�� �����)
		system("cls");

		//������ �׷�����
		draw_board();

		//������ �ϼ��Ǿ����� üũ�Ѵ�.
		if (winner = check_omok()) {
			print_congratulation_msg(winner);
			return 0;
		}

		//����ڿ��� ���� ��ġ �޾Ƴ���
		if (now_turn == user_stone_color)
			scan_stone_position(now_turn, &x, &y);
		else
			AI_get_stone_position(now_turn, &x, &y);

		set_stone(now_turn, x, y);

		switch (now_turn) {
		case WHITE:
			now_turn = BLACK; break;
		case BLACK:
			now_turn = WHITE; break;
		}
	}

	return 0;
}

//����ȭ�� ���
void display_welcome(void)
{
	int i;
	for (i = 0; i < 40; i++) printf("*");
	puts("\n");
	for (i = 0; i < 10; i++) printf(" ");
	printf("����\n\n");
	for (i = 0; i < 40; i++) printf("*");
	printf("\n\n!��üȭ������ �����ϼ���!\n");
	printf("�ƹ� Ű�� ���� ����...\n");
}

//������ ���
void draw_board(void)
{
	int i, row, col;
	printf("\n\n    ");
	for (i = 1; i < 16; i++) printf(" %2d  ", i);
	for (row = 0; row < 15; row++) {
		puts("");
		for (i = 0; i < 80; i++) {
			if ((i - 3) % 5) printf("-");
			else printf("+");
		}
		printf("\n%2d |", row + 1);
		for (col = 0; col < 15; col++) {
			switch (board[row][col]) {
			case EMPTY: printf("    "); break;
			case WHITE: printf(" �� "); break;
			case BLACK: printf(" �� "); break;
			}
			printf("|");
		}
	}
	puts("\n");
}

//���� üũ
int check_omok(void)
{
	int row, col, i, k, winner;
	for (row = 0; row < 11; row++) {
		for (col = 0; col < 11; col++) {
			if (!board[row][col]) continue;
			for (i = -1; i < 2; i++) {
				winner = board[row][col];
				for (k = 0; k < 5; k++) {
					if (winner != board[row + k][col + i * k]) {
						winner = EMPTY;
						break;
					}
				}
				if (winner) return winner;
			}
		}
	}

	return 0;
}

//�¸� ���� �޽��� ���
void print_congratulation_msg(int winner)
{
	int i;

	for (i = 0; i < 80; i++) printf("*");
	puts("");
	for (i = 0; i < 20; i++) printf(" ");
	printf("�����մϴ�!!! ");

	if (winner == BLACK)
		printf("��");
	else
		printf("��");

	printf("���� �¸��Դϴ�!!!");
	puts("");
	for (i = 0; i < 80; i++) printf("*");
	puts("\n\n");
}

//�ش� ��ǥ�� ���� ����.
void set_stone(int now_turn, int x, int y)
{
	board[x][y] = now_turn;
}

//����ڿ��� �Է��� �� ��ġ �Է��� �䱸.
void scan_stone_position(int now_turn, int * x, int * y)
{
	while (1) {
		if (now_turn == BLACK) printf("��");
		else printf("��");
		printf("���� �����Դϴ�. ���� ���� ���� ��ġ�� ��ǥ�� �Է����ֽʽÿ�. (��: 8 9) ");
		scanf("%d %d", x, y);
		if (*x > 15 || *x < 1 || *y > 15 || *y < 1) {
			printf("��ȿ�� ���ڰ� �ƴմϴ�. ��ǥ�� ���� 1~15 ������ �ڿ����̿��� �մϴ�.\n");
			continue;
		}

		--*x;
		--*y;

		if (board[*x][*y]) {
			printf("�̹� �װ����� ���� �����ֽ��ϴ�. �ٸ� ��ǥ�� �Է����ֽʽÿ�.\n");
			continue;
		}

		break;
	}
}


//�˰��� ���� ���� ���� ���� ����.
void AI_get_stone_position(int now_turn, int * x, int * y)
{
	int priority[15][15] = { 0, };
	int max_coord[15 * 15][2] = { 0, };

	int stone_amount = 0,
		max_amount = 0,
		max_val = INT_MIN,
		rand_key,
		row, col;

	//�̹� ���� �ִ� ���� �켱���� ���Ϸ�.
	for (row = 0; row < 15; row++)
		for (col = 0; col < 15; col++)
			if (board[row][col])
			{
				stone_amount++;
				priority[row][col] = INT_MIN;
			}

	//�����ǿ� ���� 2�� �̸��� ���, 
	//�ٵ��� �߾��� �켱���� 10000��ŭ �߰�.
	if (stone_amount < 2)
		priority[7][7] += 10000;

	//�̹� ������ ������ 8������ �켱���� 1��ŭ �߰�.
	for (row = 0; row < 15; row++)
		for (col = 0; col < 15; col++)
			if (board[row][col])
			{
				if (row)
					priority[row - 1][col]++;
				if (col)
					priority[row][col - 1]++;

				if (row != 14)
					priority[row + 1][col]++;
				if (col != 14)
					priority[row][col + 1]++;

				if (row * col)
					priority[col - 1][row - 1]++;
				if (row != 14 && col != 14)
					priority[col + 1][row + 1]++;

				if (col != 14 && row)
					priority[col + 1][row - 1]++;
				if (col && row != 14)
					priority[col - 1][row + 1]++;
			}

	//�켱���� ���� ���� �͵��� ã�� �迭�� ����.
	for (row = 0; row < 15; row++)
		for (col = 0; col < 15; col++) {
			if (max_val < priority[row][col]) {
				max_val = priority[row][col];
				max_amount = 0;
			}
			if (max_val == priority[row][col]) {
				max_coord[max_amount][0] = row;
				max_coord[max_amount][1] = col;
				max_amount++;
			}
		}

	rand_key = rand() % max_amount;

	*x = max_coord[rand_key][0];
	*y = max_coord[rand_key][1];
}

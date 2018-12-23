// 나는 이윤석이다.
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

	//rand 시드 초기화
	srand((unsigned)time(0));

	//콘솔 배경을 파란색, 글씨를 흰색으로 변경한다.
	system("color 9f");

	//메인 화면을 출력한다.
	display_welcome();

	//사용자에게 돌 색깔을 선택하도록 함.
	while (1) {
		printf("흑돌과 백돌 중 무엇으로 하시겠습니까?(흑:%d, 백:%d) ", BLACK, WHITE);
		scanf("%d", &user_stone_color);
		if (user_stone_color == BLACK || user_stone_color == WHITE)
			break;
		printf("유효한 값이 아닙니다. 다시 입력해주십시오.\n");
	}

	//돌 색을 안내하고 3초 대기하기.
	if (user_stone_color == BLACK) {
		printf("3초후 흑돌로 게임을 시작합니다...");
		ai_stone_color = WHITE;

	}
	else {
		printf("3초후 백돌로 게임을 시작합니다...");
		ai_stone_color = BLACK;
	}
	for (int i = 0; i < 3; i++)
	{
		Sleep(500);
		printf("\n%d...\n", i + 1);
		Sleep(500);
	}

	//콘솔 배경을 흰색, 글씨를 검은색으로 변경한다.
	system("color f0");

	while (1) {
		//화면 지우기 (이미 출력됐던 메인화면 지우기)
		system("cls");

		//오목판 그려내기
		draw_board();

		//오목이 완성되었는지 체크한다.
		if (winner = check_omok()) {
			print_congratulation_msg(winner);
			return 0;
		}

		//사용자에게 돌의 위치 받아내기
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

//메인화면 출력
void display_welcome(void)
{
	int i;
	for (i = 0; i < 40; i++) printf("*");
	puts("\n");
	for (i = 0; i < 10; i++) printf(" ");
	printf("오목\n\n");
	for (i = 0; i < 40; i++) printf("*");
	printf("\n\n!전체화면으로 실행하세요!\n");
	printf("아무 키나 눌러 시작...\n");
}

//오목판 출력
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
			case WHITE: printf(" ○ "); break;
			case BLACK: printf(" ● "); break;
			}
			printf("|");
		}
	}
	puts("\n");
}

//오목 체크
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

//승리 축하 메시지 출력
void print_congratulation_msg(int winner)
{
	int i;

	for (i = 0; i < 80; i++) printf("*");
	puts("");
	for (i = 0; i < 20; i++) printf(" ");
	printf("축하합니다!!! ");

	if (winner == BLACK)
		printf("흑");
	else
		printf("백");

	printf("돌의 승리입니다!!!");
	puts("");
	for (i = 0; i < 80; i++) printf("*");
	puts("\n\n");
}

//해당 좌표에 돌을 놓음.
void set_stone(int now_turn, int x, int y)
{
	board[x][y] = now_turn;
}

//사용자에게 입력을 돌 위치 입력을 요구.
void scan_stone_position(int now_turn, int * x, int * y)
{
	while (1) {
		if (now_turn == BLACK) printf("흑");
		else printf("백");
		printf("돌의 차례입니다. 돌을 놓고 싶은 위치의 좌표를 입력해주십시오. (예: 8 9) ");
		scanf("%d %d", x, y);
		if (*x > 15 || *x < 1 || *y > 15 || *y < 1) {
			printf("유효한 숫자가 아닙니다. 좌표의 값은 1~15 사이의 자연수이여야 합니다.\n");
			continue;
		}

		--*x;
		--*y;

		if (board[*x][*y]) {
			printf("이미 그곳에는 돌이 놓여있습니다. 다른 좌표를 입력해주십시오.\n");
			continue;
		}

		break;
	}
}


//알고리즘에 의해 돌을 놓을 곳을 선택.
void AI_get_stone_position(int now_turn, int * x, int * y)
{
	int priority[15][15] = { 0, };
	int max_coord[15 * 15][2] = { 0, };

	int stone_amount = 0,
		max_amount = 0,
		max_val = INT_MIN,
		rand_key,
		row, col;

	//이미 돌이 있는 곳의 우선도를 최하로.
	for (row = 0; row < 15; row++)
		for (col = 0; col < 15; col++)
			if (board[row][col])
			{
				stone_amount++;
				priority[row][col] = INT_MIN;
			}

	//오목판에 돌이 2개 미만일 경우, 
	//바둑판 중앙의 우선도를 10000만큼 추가.
	if (stone_amount < 2)
		priority[7][7] += 10000;

	//이미 놓여진 돌들의 8방향의 우선도를 1만큼 추가.
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

	//우선도가 가장 높은 것들을 찾아 배열에 삽입.
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

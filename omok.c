#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define EMPTY 0
#define BLACK 1
#define WHITE 2

int main(void) {
	int board[15][15] = {
		{0}, {0}, {0}, {0}, {0},
		{0}, {0}, {0}, {0}, {0},
		{0}, {0}, {0}, {0}, {0}
	};

	int user_x = 0, user_y = 0,
			winner = 0,
			i, k,
			row, col,
			now_turn = BLACK;

	//콘솔 배경을 파란색, 글씨를 흰색으로 변경한다.
	system("color 9f");

	//메인 화면을 출력한다.
	for (i = 0; i < 40; i++) printf("*");
	puts("\n");
	for (i = 0; i < 10; i++) printf(" ");
	printf("오목\n\n");
	for (i = 0; i < 40; i++) printf("*");
	printf("\n\n!전체화면으로 실행하세요!\n");
	printf("아무 키나 눌러 시작...\n");

	//키보드 입력을 받을 때까지 대기...
	while (!_kbhit());

	//콘솔 배경을 흰색, 글씨를 검은색으로 변경한다.
	system("color f0");

	while (1) {
		//바둑판 그려내기
		system("cls");
		printf("\n\n    ");
		for (i = 1; i < 16; i++) printf(" %2d  ", i);
		for (row = 0; row < 15; row++) {
			puts("");
			for (i = 0; i < 80; i++) {
				if ((i-3)%5) printf("-");
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

		//오목이 완성되었는지 체크한다.
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
					if (winner) {
						for (i = 0; i < 80; i++) printf("*");
						puts("");
						for (i = 0; i < 20; i++) printf(" ");
						printf("축하합니다!!! ");
						if (winner == BLACK) {
							printf("흑");
						} else {
							printf("백");
						}
						printf("돌의 승리입니다!!!");
						puts("");
						for (i = 0; i < 80; i++) printf("*");
						puts("\n\n");
						return 0;
					}
				}
			}
		}

		//사용자에게 돌의 위치 받아내기
		while (1) {
			if (now_turn == BLACK) printf("흑");
			else printf("백");
			printf("돌의 차례입니다. 돌을 놓고 싶은 위치의 좌표를 입력해주십시오. (예: 8 9) ");
			scanf("%d %d", &user_y, &user_x);
			if (user_x > 15 || user_x < 1 || user_y > 15 || user_y < 1) {
				printf("유효한 숫자가 아닙니다. 좌표의 값은 1~15 사이의 자연수이여야 합니다.\n");
				continue;
			}
			user_x--;
			user_y--;
			if (board[user_x][user_y]) {
				printf("이미 그곳에는 돌이 놓여있습니다. 다른 좌표를 입력해주십시오.\n");
				continue;
			}
			board[user_x][user_y] = now_turn;
			switch (now_turn) {
				case WHITE:
					now_turn = BLACK; break;
				case BLACK:
					now_turn = WHITE; break;
			}
			break;
		}

	}

	return 0;
}

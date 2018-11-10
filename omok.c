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

	//�ܼ� ����� �Ķ���, �۾��� ������� �����Ѵ�.
	system("color 9f");

	//���� ȭ���� ����Ѵ�.
	for (i = 0; i < 40; i++) printf("*");
	puts("\n");
	for (i = 0; i < 10; i++) printf(" ");
	printf("����\n\n");
	for (i = 0; i < 40; i++) printf("*");
	printf("\n\n!��üȭ������ �����ϼ���!\n");
	printf("�ƹ� Ű�� ���� ����...\n");

	//Ű���� �Է��� ���� ������ ���...
	while (!_kbhit());

	//�ܼ� ����� ���, �۾��� ���������� �����Ѵ�.
	system("color f0");

	while (1) {
		//�ٵ��� �׷�����
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
					case WHITE: printf(" �� "); break;
					case BLACK: printf(" �� "); break;
				}
				printf("|");
			}
		}
		puts("\n");

		//������ �ϼ��Ǿ����� üũ�Ѵ�.
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
						printf("�����մϴ�!!! ");
						if (winner == BLACK) {
							printf("��");
						} else {
							printf("��");
						}
						printf("���� �¸��Դϴ�!!!");
						puts("");
						for (i = 0; i < 80; i++) printf("*");
						puts("\n\n");
						return 0;
					}
				}
			}
		}

		//����ڿ��� ���� ��ġ �޾Ƴ���
		while (1) {
			if (now_turn == BLACK) printf("��");
			else printf("��");
			printf("���� �����Դϴ�. ���� ���� ���� ��ġ�� ��ǥ�� �Է����ֽʽÿ�. (��: 8 9) ");
			scanf("%d %d", &user_y, &user_x);
			if (user_x > 15 || user_x < 1 || user_y > 15 || user_y < 1) {
				printf("��ȿ�� ���ڰ� �ƴմϴ�. ��ǥ�� ���� 1~15 ������ �ڿ����̿��� �մϴ�.\n");
				continue;
			}
			user_x--;
			user_y--;
			if (board[user_x][user_y]) {
				printf("�̹� �װ����� ���� �����ֽ��ϴ�. �ٸ� ��ǥ�� �Է����ֽʽÿ�.\n");
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

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tate 15       //縦の広さ
#define yoko 15       //横の広さ
#define bombnumber 16 //爆弾の数

#define bomb -1 //いじるな(負の整数なら多分大丈夫かも。)

int BAN[10][tate+2][yoko+2];
int endflag;
int number;

void shokika(){
	int i, j, k;
	for (i = 0; i < 10; i++){
		for (j = 0; j < tate+2; j++){
			for (k = 0; k < yoko+2; k++){
				BAN[i][j][k] = 0;
			}
		}
	}
	endflag = 0;
	srand((unsigned)time(NULL));
}

void hyouzi(){
	int i, j;
	for (i = 0; i < tate + 2; i++){
		for (j = 0; j < yoko + 2; j++){
			if (i == 0){
				if (j == 0){
					printf("┏");
				}
				else if (j == yoko + 1){
					printf("┓");
				}
				else{
					printf("━");
				}
			}
			else if (i == tate + 1){
				if (j == 0){
					printf("┗");
				}
				else if (j == yoko + 1){
					printf("┛");
				}
				else{
					printf("━");

				}
			}
			else{
				if (j == 0 || j == yoko + 1){
					printf("┃");
				}
				else if(BAN[2][i][j]==1){
					printf("%d ", BAN[0][i][j]);
				}
				else{
					printf("  ");
				}
			}

		}
		puts("");
	}
}

void nyuuryoku(){
	do{
		printf("どこに置く？");
		scanf("%d", &number);
	} while (BAN[2][number % 10000 / 100][number % 100] != 0 || ((number % 10000) / 100) > tate || ((number % 10000) / 100)<=0 || (number % 100) > yoko || (number % 100)<=0);
	BAN[2][number % 10000 / 100][number % 100] = 1;
}

void hantei(){
	int i,j,n=0;
	if (BAN[0][number % 10000 / 100][number % 100] == bomb){
		endflag = 1;
	}
	else{
		for (i = 1; i <= tate; i++){
			for (j = 1; j <= yoko; j++){
				if (BAN[2][i][j] == 0){
					n++;
				}
			}
		}
		if (n == bombnumber){
			endflag = 2;
		}
	}
}

void haiti(){
	int i = 0,j;
	int x, y;
	int n;

	for (x = 1; x <= tate; x++){
		for (y = 1; y <= yoko; y++){
			BAN[0][x][y] = 0;
		}
	}
	while (i < bombnumber){
		x = rand() % tate+1;
		y = rand() % yoko+1;
		if (BAN[0][x][y] != 0||BAN[2][x][y]!=0){
			i--;
		}
		else{
			BAN[0][x][y] = bomb;
		}
		i++;
	}

	for (x = 1; x <= tate; x++){
		for (y = 1; y <= yoko;y++){
			if (BAN[0][x][y] != bomb){
				n = 0;
				for (i = -1; i <= 1; i++){
					for (j = -1; j <= 1; j++){
						if (!(i == 0 && j == 0)){
							if (BAN[0][x + i][y + j] == bomb){
								n++;
							}
						}
					}
				}
				BAN[0][x][y] = n;
			}

		}
	}
}

int main(){
	shokika();
	do{
		hyouzi();
		nyuuryoku();
		hantei();
		if (endflag == 0){ 
			haiti(); 
		}
	} while (endflag == 0);
	printf("おしまい\n");
	if (endflag == 1){
		printf("クリアー！");
	}
	else if (endflag == 2){
		printf("失敗・・・");
	}
	return 0;
}
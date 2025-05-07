#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
struct a {
	unsigned int n : 4;
};
struct q {
	unsigned int n : 7;
};
void dis();
void mp();  //Calculates cell number based on mouse postion in grid
UINT originalCP;
DWORD mode, written;
POINT cursorPos;
CONSOLE_CURSOR_INFO cursorInfo;
HANDLE hInput;
HANDLE hConsole;
HWND consoleWnd;
CONSOLE_FONT_INFOEX cfi;
RECT consoleRect;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;
int cond;
struct a c[81]; //stores generated grid
struct a p[81]; //stores which cell is writable and written value. If p[i].n== 10 represents its writable & blank,  if it has value less than 10 then it is the value wrote to cell and if it has value 11 then its non writable.
struct timespec spec;
long tm;
struct q hid = { 30 };
int ni = 0;
time_t t1;
time_t t2;
struct q v, f, y, j, k, i, pi, e;
struct q m = { 1 };
void dis() {
	j.n = 1;
	printf("   ");
	for (k.n = 1; k.n < 4; k.n++) {
		for (; j.n < (k.n * 3) + 1; j.n++)
			printf("%d  ", j.n);
		printf(" ");
	}
	printf("\n");
	printf(" ");
	printf("┌");
	for (j.n = 0; j.n < 2; j.n++) {
		for (k.n = 0; k.n < 9; k.n++)
			printf("─");
		printf("┬");
	}
	for (k.n = 0; k.n < 9; k.n++)
		printf("─");
	printf("┐");
	k.n = 0;
	printf("\n");
	for (j.n = 0; j.n < 2; j.n++) {
		printf("%d", k.n / 9 + 1);
		printf("│");
		for (y.n = 0; y.n < 2; y.n++) {
			if (k.n != i.n && k.n != m.n)
				printf(" ");
			for (v.n = 0; v.n < 3; v.n++) {
				for (f.n = 0; f.n < 3; f.n++) {
					if (k.n == i.n) {
						if (p[k.n].n == 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							if (k.n % 3 != 2)
								if (k.n + 1 == m.n)
									printf("[_]", c[k.n++].n);
								else
									printf("[_] ", c[k.n++].n);
							else
								printf("[_]", c[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else if (p[k.n].n < 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							if (k.n % 3 != 2)
								if (k.n + 1 == m.n)
									printf("[%d]", p[k.n++].n);
								else
									printf("[%d] ", p[k.n++].n);
							else
								printf("[%d]", p[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}

						else if (k.n % 3 != 2)
							if (k.n + 1 == m.n)
								printf("[%d]", c[k.n++].n);
							else
								printf("[%d] ", c[k.n++].n);
						else
							printf("[%d]", c[k.n++].n);
					}
					else if (k.n == m.n)
						if (p[k.n].n == 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							if (k.n % 3 != 2)
								if (k.n + 1 == i.n)
									printf("(_)", c[k.n++].n);
								else
									printf("(_) ", c[k.n++].n);
							else
								printf("(_)", c[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else if (p[k.n].n < 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							if (k.n % 3 != 2)
								if (k.n + 1 == i.n)
									printf("(%d)", p[k.n++].n);
								else
									printf("(%d) ", p[k.n++].n);
							else
								printf("(%d)", p[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else if (k.n % 3 != 2)
							if (k.n + 1 == i.n)
								printf("(%d)", c[k.n++].n);
							else
								printf("(%d) ", c[k.n++].n);
						else
							printf("(%d)", c[k.n++].n);

					else if (k.n + 1 == i.n || k.n + 1 == m.n ||
						k.n % 3 == 2)
						if (p[k.n].n == 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							printf("_ ", c[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else if (p[k.n].n < 10)
						{
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							//printf("%d ",c[k.n].n);
							printf("%d ", p[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else
							printf("%d ", c[k.n++].n);
					//printf("%s",doubleStruckUTF8[c[k.n++].n]);

					else
						if (p[k.n].n == 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							printf("_  ", c[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else if (p[k.n].n < 10) {
							if (ni == 1)
								SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
							else
								SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
							printf("%d  ", p[k.n++].n);
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
						else
							printf("%d  ", c[k.n++].n);
				}
				printf("│");
				if (k.n != i.n && k.n != m.n)
					printf(" ");
			}
			printf("\n");
			printf("%d│", k.n / 9 + 1);
		}
		for (v.n = 0; v.n < 3; v.n++) {
			if (k.n != i.n && k.n != m.n)
				printf(" ");
			for (f.n = 0; f.n < 3; f.n++) {
				if (k.n == i.n)
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == m.n)
								printf("[_]", c[k.n++].n);
							else
								printf("[_] ", c[k.n++].n);
						else
							printf("[_]", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == m.n)
								printf("[%d]", p[k.n++].n);
							else
								printf("[%d] ", p[k.n++].n);
						else
							printf("[%d]", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (k.n % 3 != 2)
						if (k.n + 1 == m.n)
							printf("[%d]", c[k.n++].n);
						else
							printf("[%d] ", c[k.n++].n);
					else
						printf("[%d]", c[k.n++].n);
				else if (k.n == m.n)
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == i.n)
								printf("(_)", c[k.n++].n);
							else
								printf("(_) ", c[k.n++].n);
						else
							printf("(_)", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == i.n)
								printf("(%d)", p[k.n++].n);
							else
								printf("(%d) ", p[k.n++].n);
						else
							printf("(%d)", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (k.n % 3 != 2)
						if (k.n + 1 == i.n)
							printf("(%d)", c[k.n++].n);
						else
							printf("(%d) ", c[k.n++].n);
					else
						printf("(%d)", c[k.n++].n);
				else if (k.n + 1 == i.n || k.n + 1 == m.n ||
					k.n % 3 == 2)
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("_ ", c[k.n++].n);

						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("%d ", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else
						printf("%d ", c[k.n++].n);
				//printf("%s",doubleStruckUTF8[c[k.n++].n]);
				else
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("_  ", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("%d  ", p[k.n++].n); SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else
						printf("%d  ", c[k.n++].n);
			}
			printf("│");
		}
		printf("\n");
		printf(" ├");
		for (f.n = 0; f.n < 2; f.n++) {
			for (v.n = 0; v.n < 9; v.n++)
				printf("─");
			printf("┼");
		}
		for (v.n = 0; v.n < 9; v.n++)
			printf("─");
		printf("┤");
		printf("\n");
	}
	printf("%d", k.n / 9 + 1);
	printf("│");
	for (y.n = 0; y.n < 2; y.n++) {
		for (v.n = 0; v.n < 3; v.n++) {
			if (k.n != i.n && k.n != m.n)
				printf(" ");
			for (f.n = 0; f.n < 3; f.n++) {
				if (k.n == i.n) {
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == m.n)
								printf("[_]", c[k.n++].n);
							else
								printf("[_] ", c[k.n++].n);
						else
							printf("[_]", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == m.n)
								printf("[%d]", p[k.n++].n);
							else
								printf("[%d] ", p[k.n++].n);
						else
							printf("[%d]", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}

					else if (k.n % 3 != 2)
						if (k.n + 1 == m.n)
							printf("[%d]", c[k.n++].n);
						else
							printf("[%d] ", c[k.n++].n);
					else
						printf("[%d]", c[k.n++].n);
				}
				else if (k.n == m.n)
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == i.n)
								printf("(_)", c[k.n++].n);
							else
								printf("(_) ", c[k.n++].n);
						else
							printf("(_)", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (k.n % 3 != 2)
							if (k.n + 1 == i.n)
								printf("(%d)", p[k.n++].n);
							else
								printf("(%d) ", p[k.n++].n);
						else
							printf("(%d)", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (k.n % 3 != 2)
						if (k.n + 1 == i.n)
							printf("(%d)", c[k.n++].n);
						else
							printf("(%d) ", c[k.n++].n);
					else
						printf("(%d)", c[k.n++].n);
				else if (k.n + 1 == i.n || k.n + 1 == m.n ||
					k.n % 3 == 2)
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("_ ", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("%d ", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else
						printf("%d ", c[k.n++].n);
				else
					if (p[k.n].n == 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("_  ", c[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if (p[k.n].n < 10) {
						if (ni == 1)
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
						printf("%d  ", p[k.n++].n);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else
						printf("%d  ", c[k.n++].n);
			}
			printf("│");
		}
		printf("\n");
		printf("%d│", k.n / 9 + 1);
	}
	for (v.n = 0; v.n < 3; v.n++) {
		if (k.n != i.n && k.n != m.n)
			printf(" ");
		for (f.n = 0; f.n < 3; f.n++) {
			if (k.n == i.n)
				if (p[k.n].n == 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					if (k.n % 3 != 2)
						if (k.n + 1 == m.n)
							printf("[_]", c[k.n++].n);
						else
							printf("[_] ", c[k.n++].n);
					else
						printf("[_]", c[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (p[k.n].n < 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					if (k.n % 3 != 2)
						if (k.n + 1 == m.n)
							printf("[%d]", p[k.n++].n);
						else -
							printf("[%d] ", p[k.n++].n);
					else
						printf("[%d]", p[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (k.n % 3 != 2)
					if (k.n + 1 == m.n)
						printf("[%d]", c[k.n++].n);
					else
						printf("[%d] ", c[k.n++].n);
				else
					printf("[%d]", c[k.n++].n);
			else if (k.n == m.n)
				if (p[k.n].n == 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					if (k.n % 3 != 2)
						if (k.n + 1 == i.n)
							printf("(_)", c[k.n++].n);
						else
							printf("(_) ", c[k.n++].n);
					else
						printf("(_)", c[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (p[k.n].n < 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					if (k.n % 3 != 2)
						if (k.n + 1 == i.n)
							printf("(%d)", p[k.n++].n);
						else
							printf("(%d) ", p[k.n++].n);
					else
						printf("(%d)", p[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (k.n % 3 != 2)
					if (k.n + 1 == i.n)
						printf("(%d)", c[k.n++].n);
					else
						printf("(%d) ", c[k.n++].n);
				else
					printf("(%d)", c[k.n++].n);
			else if (k.n + 1 == i.n || k.n + 1 == m.n || k.n % 3 == 2)
				if (p[k.n].n == 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("_ ", c[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (p[k.n].n < 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%d ", p[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else
					printf("%d ", c[k.n++].n);
			else
				if (p[k.n].n == 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("_  ", c[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if (p[k.n].n < 10) {
					if (ni == 1)
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE/*| FOREGROUND_INTENSITY */ | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					else
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%d  ", p[k.n++].n);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else
					printf("%d  ", c[k.n++].n);
		}
		printf("│");
	}
	printf("\n");
	printf(" └");
	for (f.n = 0; f.n < 2; f.n++) {
		for (v.n = 0; v.n < 9; v.n++)
			printf("─");
		printf("┴");
	}
	for (v.n = 0; v.n < 9; v.n++)
		printf("─");
	printf("┘");
	printf("\nSq no:%d", i.n + 1);
}
void mp() {
	if (GetCursorPos(&cursorPos)) {
		if (GetWindowRect(consoleWnd, &consoleRect)) {
			if (GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
				if (cond = cursorPos.x - consoleRect.left >
					(cfi.dwFontSize.X * 2) &&
					cursorPos.x - consoleRect.left <
					(cfi.dwFontSize.X * 32) &&
					cursorPos.y - consoleRect.top - 30 >
					(cfi.dwFontSize.Y * 3) &&
					cursorPos.y - consoleRect.top - 30 <
					(cfi.dwFontSize.Y * 15)) {
					if (cursorPos.x - consoleRect.left <
						(12 * cfi.dwFontSize.X))
						m.n =
						(cursorPos.x - consoleRect.left -
							2 * cfi.dwFontSize.X) /
						(cfi.dwFontSize.X *
							3); //+(9*(((cursorPos.y-consoleRect.top)/(cfi.dwFontSize.Y*2))-1));
					else if (cursorPos.x - consoleRect.left <
						(22 * cfi.dwFontSize.X))
						// printf("ooo");
						m.n = (cursorPos.x - consoleRect.left -
							12 * cfi.dwFontSize.X) /
						(cfi.dwFontSize.X * 3) +
						3;

					else if (cursorPos.x - consoleRect.left <
						(32 * cfi.dwFontSize.X))
						m.n = (cursorPos.x - consoleRect.left -
							22 * cfi.dwFontSize.X) /
						(cfi.dwFontSize.X * 3) +
						6;

					if (cursorPos.y - consoleRect.top - 30 <
						(7 * cfi.dwFontSize.Y)) {
						m.n += 9 * ((cursorPos.y - consoleRect.top - 30 -
							3 * cfi.dwFontSize.Y) /
							(cfi.dwFontSize.Y));
					} 
					else if (cursorPos.y - consoleRect.top - 30 <
						(11 * cfi.dwFontSize.Y))
						m.n += 9 * ((cursorPos.y - consoleRect.top - 30 -
							7 * cfi.dwFontSize.Y) /
							(cfi.dwFontSize.Y) +
							3);

					else if (cursorPos.y - consoleRect.top - 30 <
						(15 * cfi.dwFontSize.Y))
						m.n += 9 * ((cursorPos.y - consoleRect.top - 30 -
							11 * cfi.dwFontSize.Y) /
							(cfi.dwFontSize.Y) +
							6);
				}
			}
		}
	}

}
void main() {
	for (v.n = 0; v.n < 81; v.n++)
		p[v.n].n = 10;
	struct a g[729];
	tm = spec.tv_nsec;
	t1 = time(NULL);
	originalCP = GetConsoleOutputCP();
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode |= ENABLE_EXTENDED_FLAGS;
	SetConsoleOutputCP(CP_UTF8);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	consoleWnd = GetConsoleWindow();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	int r;
	int ch = 1, pch;
	int width;
	int height;
	COORD bufferSize;
	SMALL_RECT windowSize;
	if (consoleWnd == NULL) {
		fprintf(stderr, "Error: Unable to get console window handle.\n");
	}
	if (!SetConsoleMode(hInput, mode))
		printf("Error: Unable to set console mode.\n");
	if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
		cursorInfo.bVisible = FALSE; // Hide the cursor
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}
	if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
		printf("Error getting console font: %ld\n", GetLastError());
		return;
	}
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas");
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
		printf("Error setting console font: %ld\n", GetLastError());
	}
m:
	ch = 0;
	while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	SetConsoleOutputCP(CP_UTF8);
	cfi.dwFontSize.Y = 60;
	cfi.dwFontSize.X = 30;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
		printf("zoom not set");
	width = 24;
	height = 14;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
		printf("Failed to set console window size.\n");
	if (!GetWindowRect(consoleWnd, &consoleRect)) {
		fprintf(stderr, "Error: Unable to get window rectangle.\n");
	}
	pch = 100;
	while (1) {
		if (GetCursorPos(&cursorPos)) {
			if (GetWindowRect(consoleWnd, &consoleRect)) {
				if (cursorPos.x > consoleRect.left > 0 &&
					cursorPos.x < consoleRect.right - 40 &&
					cursorPos.y - cfi.dwFontSize.Y > consoleRect.top &&
					cursorPos.y < consoleRect.bottom - 40) {
					if (m.n == 1) {
						if (cursorPos.y - consoleRect.top - 30 <
							3 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							2 * cfi.dwFontSize.Y) {
							ch = 1;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								goto ch1;
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							5 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							4 * cfi.dwFontSize.Y) {
							if (cursorPos.x - consoleRect.left <
								16 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								13 * cfi.dwFontSize.X) {
								ch = 2;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									if (hid.n > 0) {
										hid.n--;
										pch++;
										Sleep(85);
									}
								}
								goto lp;
							}
							else if (cursorPos.x - consoleRect.left <
								23 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								20 * cfi.dwFontSize.X) {
								ch = 3;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									if (hid.n < 81) {
										hid.n++;
										pch++;
										Sleep(85);
									}
								}
								goto lp;
							}
							else
								ch = 12;
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							7 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							6 * cfi.dwFontSize.Y) {
							ch = 4;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								goto ch4;
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							9 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							8 * cfi.dwFontSize.Y) {
							ch = 5;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								exit(0);
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							11 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							10 * cfi.dwFontSize.Y) {
							//printf("aaa");
							if (cursorPos.x - consoleRect.left <
								110 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								7 * cfi.dwFontSize.X) {
								ch = 6;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									system("color 0F");
									ni = 0; pch++;
								}
							}
							if (cursorPos.x - consoleRect.left <
								14 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								10 * cfi.dwFontSize.X) {
								ch = 7;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									system("color F0");
									ni = 1; pch++;
								}

							}
							while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
							GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
							saved_attributes = consoleInfo.wAttributes;
						}
					}
					else {
						if (cursorPos.y - consoleRect.top - 30 <
							3 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							2 * cfi.dwFontSize.Y) {
							ch = 0;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								goto ch0;
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							5 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							4 * cfi.dwFontSize.Y) {
							ch = 1;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								goto ch1;
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							7 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							6 * cfi.dwFontSize.Y)
							if (cursorPos.x - consoleRect.left <
								16 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								13 * cfi.dwFontSize.X) {
								ch = 2;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									if (hid.n > 0) {
										hid.n--;
										pch++;
										Sleep(85);
									}
								}
								goto lp;
							}
							else if (cursorPos.x - consoleRect.left <
								23 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								20 * cfi.dwFontSize.X) {
								ch = 3;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									if (hid.n < 81) {
										hid.n++;
										pch++;
										Sleep(85);
									}
								}
								goto lp;
							}
							else
								ch = 12;
						else if (cursorPos.y - consoleRect.top - 30 <
							9 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							8 * cfi.dwFontSize.Y) {
							ch = 4;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								goto ch4;
							}
						}
						else if (cursorPos.y - consoleRect.top - 30 <
							11 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							10 * cfi.dwFontSize.Y) {
							ch = 5;
							if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								exit(0);
							}
						}


						else if (cursorPos.y - consoleRect.top - 30 <
							13 * cfi.dwFontSize.Y &&
							cursorPos.y - consoleRect.top - 30 >
							12 * cfi.dwFontSize.Y) {
							if (cursorPos.x - consoleRect.left <
								10 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								7 * cfi.dwFontSize.X) {
								ch = 6;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									system("color 0F");
									ni = 0; pch++;
								}
							}
							if (cursorPos.x - consoleRect.left <
								14 * cfi.dwFontSize.X &&
								cursorPos.x - consoleRect.left >
								10 * cfi.dwFontSize.X) {
								ch = 7;
								if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									system("color F0");
									ni = 1; pch++;
								}

							}
							while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
							GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
							saved_attributes = consoleInfo.wAttributes;
						}
					}
				}
				else {
				}
			}
			else {
				printf("Failed to get cursor position.\n");
			}
		lp:

			if (ch != pch) {
				wchar_t text[] = L"\t "
					L"\U0001D564\U0001D566\U0001D555\U0001D560"
					L"\U0001D55C\U0001D566";
				system("cls");
				WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);

				if (m.n == 1) {
					if (ch == 1)
						printf("\n\n\t [Play]");
					else
						printf("\n\n\t  Play");
					if (ch == 2)
						if (hid.n % 10 == hid.n % 100)
							printf("\n\n   Hide cells:[<] 0%d  >", hid.n);
						else
							printf("\n\n   Hide cells:[<] %d  > ", hid.n);
					else if (ch == 3)
						if (hid.n % 10 == hid.n % 100)
							printf("\n\n   Hide cells: <  0%d [>]", hid.n);
						else
							printf("\n\n   Hide cells: <  %d [>]", hid.n);
					else if (hid.n % 10 == hid.n % 100)
						printf("\n\n   Hide cells: <  0%d  > ", hid.n);
					else
						printf("\n\n   Hide cells: <  %d  > ", hid.n);
					if (ch == 4)
						printf("\n\n\t[Solve]");
					else
						printf("\n\n\t Solve");
					if (ch == 5)
						printf("\n\n\t[Exit]");
					else
						printf("\n\n\t Exit");
					if (ni == 0)
						printf("\n\n       [🌙]");
					else if (ch == 6)
						printf("\n\n       (🌙)");
					else
						printf("\n\n\t🌙 ");
					if (ni == 1)
						printf("[🌞]");
					else if (ch == 7)
						printf("(🌞)");
					else
						printf(" 🌞");
				}
				else {
					if (ch == 0)
						printf("\n\n       [Continue]");
					else
						printf("\n\n\tContinue");
					if (ch == 1)
						printf("\n\n\t [Play]");
					else
						printf("\n\n\t  Play");
					if (ch == 2)
						if (hid.n % 10 == hid.n % 100)
							printf("\n\n   Hide cells:[<] 0%d  > ", hid.n);
						else
							printf("\n\n   Hide cells:[<] %d  > ", hid.n);
					else if (ch == 3)
						if (hid.n % 10 == hid.n % 100)
							printf("\n\n   Hide cells: <  0%d [>]", hid.n);
						else
							printf("\n\n   Hide cells: <  %d [>]", hid.n);
					else if (hid.n % 10 == hid.n % 100)
						printf("\n\n   Hide cells: <  0%d  > ", hid.n);
					else
						printf("\n\n   Hide cells: <  %d  > ", hid.n);
					if (ch == 4)
						printf("\n\n\t[Solve]");
					else
						printf("\n\n\t Solve");
					if (ch == 5)
						printf("\n\n\t[Exit]");
					else
						printf("\n\n\t Exit");
					if (ni == 0)
						printf("\n\n       [🌙]");
					else if (ch == 6)
						printf("\n\n       (🌙)");
					else
						printf("\n\n\t🌙 ");
					if (ni == 1)
						printf("[🌞]");
					else if (ch == 7)
						printf("(🌞)");
					else
						printf(" 🌞");
				}
			}
			pch = ch;
		}
	}
cho:
	while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000));
	
	//Sudoku generation
	
ch1:
	system("cls");
	printf("\n");
	printf("Generating ");
	r = time(NULL) % 249455;
	for (j.n = 0; j.n < 81; j.n++)
		c[j.n].n = 0;
	for (i.n = 0; i.n < 81; i.n++) {
		for (k.n = 0; k.n < 9; k.n++) {
			g[9 * i.n + k.n].n = k.n + 1;
		}
	}
	for (i.n = 0; i.n < 81; i.n++) {
		for (v.n = 0; v.n < 9; v.n++) {
			k.n = (r = ((589 * r + 742) % 7864)) % 9;
			f.n = g[9 * i.n + v.n].n;
			g[9 * i.n + v.n].n = g[9 * i.n + k.n].n;
			g[9 * i.n + k.n].n = f.n;
		}
		p[i.n].n = 15;
	ni:	if (p[i.n].n == 9) {
			if (i.n == 0) {
				//printf("caught");getch();
			}
			//goto ch1;}
			//c[i.n].n=0;
			else { i.n--; c[i.n].n = 0; }
		}
		p[i.n].n++;
		f.n = i.n / 9;
		v.n = f.n / 3;
		k.n = i.n % 9;
		pi.n = k.n / 3;
		for (y.n = f.n - 3 * v.n; y.n > 0; y.n--)
			for (j.n = 0; j.n < 3; j.n++)
				if (c[v.n * 27 + 3 * pi.n + 9 * (y.n - 1) + j.n].n ==
					g[9 * i.n + p[i.n].n].n)
				{/*printf("q %d",i.n); Sleep(2)*/; goto ni;
				}
		for (; k.n > 0; k.n--)
			if (c[i.n - k.n].n == g[9 * i.n + p[i.n].n].n) {
				/*	printf("r %d",i.n);Sleep(2);*/
				goto ni;
			}
		for (; f.n > 0; f.n--)
			if (c[i.n - f.n * 9].n == g[9 * i.n + p[i.n].n].n) {
				/* printf("c %d",i.n); Sleep(2);*/
				goto ni;
			}
		c[i.n].n = g[9 * i.n + p[i.n].n].n;
	}
	for (v.n = 0; v.n < 81; v.n++)
		p[v.n].n = 11;
	v.n = hid.n;
	while (v.n > 0) {
		k.n = (r = ((589 * r + 742) % 7864)) % (81);
		if (p[k.n].n != 10) {
			p[k.n].n = 10;
			v.n--;
		}
	}
ch0: t2 = time(NULL);
	i.n = 0;
	m.n = 0;
	pi.n = 100;
	SetConsoleOutputCP(CP_UTF8);
	cfi.dwFontSize.Y = 32;
	cfi.dwFontSize.X = 16;
	width = 34;
	height = 15;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
		printf("zoom not set");
	width = 34;
	height = 16;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
		printf("Failed to set console window size.\n");
	if (!GetWindowRect(consoleWnd, &consoleRect)) {
		fprintf(stderr, "Error: Unable to get window rectangle.\n");
	}
	i.n = 0;
	m.n = 0;
	pi.n = 100;
	SetConsoleOutputCP(CP_UTF8);
	cfi.dwFontSize.Y = 32;
	cfi.dwFontSize.X = 16;
	saved_attributes = consoleInfo.wAttributes;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
		printf("zoom not set");
	clock_gettime(CLOCK_REALTIME, &spec);
	while (1) {
		clock_gettime(CLOCK_REALTIME, &spec);
		if ((m.n != pi.n &&
			(tm - spec.tv_nsec > 40000000 || tm - spec.tv_nsec < -40000000)) || t1 != time(NULL) - t2) {
			tm = spec.tv_nsec;
			// display
		disp:
			system("cls");
			t1 = time(NULL) - t2;
			printf("🕑 %ld:%ld:%ld", (t1 / 3600) % 24, (t1 / 60) % 60, t1 % 60);
			if (m.n == 94) {
				printf("   [check]\n");
			}
			else
				printf("    check \n");

			dis();

			if (m.n == 93) {
				if (i.n + 1 < 10)
					printf("\t\t [Reveal]");
				else
					printf("\t [Reveal]");
				printf("  Menu");
			}
			else if (m.n == 92) {
				if (i.n + 1 < 10)
					printf("\t\t  Reveal");
				else
					printf("\t  Reveal");
				printf("  [Menu]");
			}
			else {
				if (i.n + 1 < 10)
					printf("\t\t  Reveal");
				else
					printf("\t  Reveal");
				printf("   Menu");
			}


		}
		pi.n = m.n;
		mp();
		if (cond < 1)
			if (cursorPos.y - consoleRect.top - 30 <
				16 * cfi.dwFontSize.Y &&
				cursorPos.y - consoleRect.top - 30 >
				15 * cfi.dwFontSize.Y &&
				cursorPos.x - consoleRect.left >
				27 * cfi.dwFontSize.X &&
				cursorPos.x - consoleRect.left <
				32 * cfi.dwFontSize.X) {
				m.n = 92;
			}
			else if (cursorPos.y - consoleRect.top - 30 <
				16 * cfi.dwFontSize.Y &&
				cursorPos.y - consoleRect.top - 30 >
				15 * cfi.dwFontSize.Y &&
				cursorPos.x - consoleRect.left >
				16 * cfi.dwFontSize.X &&
				cursorPos.x - consoleRect.left <
				24 * cfi.dwFontSize.X) {
				m.n = 93;
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					for (v.n = 0; v.n < 81; v.n++)
						if (p[v.n].n < 11)
							p[v.n].n = c[v.n].n;
			}
			else if (cursorPos.y - consoleRect.top - 30 <
				cfi.dwFontSize.Y &&
				cursorPos.y - consoleRect.top - 30 >
				0 &&
				cursorPos.x - consoleRect.left >
				11 * cfi.dwFontSize.X &&
				cursorPos.x - consoleRect.left <
				21 * cfi.dwFontSize.X) {
				m.n = 94;
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

					printf("\n__________📝 Violations___________\n");
					e.n = 0;
					for (m.n = 0; m.n < 81; m.n++) {
						if (p[m.n].n < 10) {
							v.n = m.n / 27;
							pi.n = (m.n % 9) / 3;
							for (y.n = 0; y.n < 3; y.n++)
								for (j.n = 0; j.n < 3; j.n++)
									if ((v.n * 27 + 3 * pi.n + 9 * y.n + j.n) != m.n) {
										if (p[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n == 11) {
											if (c[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n ==
												p[m.n].n)
											{
												e.n++; printf("•Cell %d violates subgrid  \n", m.n + 1);
											}
										}
										else {
											if (p[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n ==
												p[m.n].n)
											{
												e.n++; printf("•Cell %d violates subgrid  \n", m.n + 1);
											}
										}
									}
							for (k.n = 0; k.n < 9; k.n++)
								if (9 * ((int)m.n / 9) + k.n != m.n)
									if (p[9 * ((int)m.n / 9) + k.n].n == 11) {
										if (c[9 * ((int)m.n / 9) + k.n].n == p[m.n].n) {
											e.n++;
											printf("•Cell %d violates row \n", m.n + 1);
										}
									}
									else
										if (p[9 * ((int)m.n / 9) + k.n].n == p[m.n].n) {
											e.n++;
											printf("•Cell %d violates row \n", m.n + 1);
										}
							for (f.n = 0; f.n < 9; f.n++)
								if ((m.n % 9) + f.n * 9 != m.n)
									if (p[(m.n % 9) + f.n * 9].n == 11) {
										if (c[(m.n % 9) + f.n * 9].n == p[m.n].n) {
											e.n++;
											printf("•Cell %d violates column \n", m.n + 1);
										}
									}
									else
										if (p[(m.n % 9) + f.n * 9].n == p[m.n].n) {
											e.n++;
											printf("•Cell %d violates column \n", m.n + 1);
										}
						}
					}
					if (e.n == 0)
						printf("•No violations found!");
					printf("\n--Press any key to go to sudoku--"); while (GetAsyncKeyState(VK_LBUTTON) & 0x8000); while (!kbhit() && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)); while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
				}
			}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button
			if (i.n != m.n) {
				i.n = m.n;
				goto disp;
			}
		}
		if (kbhit()) {
			e.n = getch();
			if (e.n > 48 && e.n < 58 && p[i.n].n < 11 && i.n < 81)
				p[i.n].n = e.n - 48;
			goto disp;
		}


		if (i.n == 92) {
			i.n = 0;
			goto m;
		}
	}
		
ch4: while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
	i.n = 0;
	m.n = 0;
	pi.n = 100;
	SetConsoleOutputCP(CP_UTF8);
	cfi.dwFontSize.Y = 32;
	cfi.dwFontSize.X = 16;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
		printf("zoom not set");
	width = 34;
	height = 16;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
		printf("Failed to set console window size.\n");
	if (!GetWindowRect(consoleWnd, &consoleRect)) {
		fprintf(stderr, "Error: Unable to get window rectangle.\n");
	}
	i.n = 0;
	m.n = 0;
	pi.n = 100;
	SetConsoleOutputCP(CP_UTF8);
	cfi.dwFontSize.Y = 32;
	cfi.dwFontSize.X = 16;
	saved_attributes = consoleInfo.wAttributes;
	if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
		printf("zoom not set");
	for (y.n = 0; y.n < 81; y.n++)
		if (p[y.n].n < 11)
			c[y.n].n = 0;
	while (1) {
		if (m.n != pi.n) {
		re:	system("cls");
			printf("Enter the numbers or 0 for blank\n");
			dis();

			if (m.n == 93) {
				if (i.n + 1 < 10)
					printf("\t\t [Solve]");
				else
					printf("\t [Solve]");
				printf("  Menu");
			}
			else if (m.n == 92) {
				if (i.n + 1 < 10)
					printf("\t\t  Solve");
				else
					printf("\t  Solve");
				printf("  [Menu]");
			}
			else {
				if (i.n + 1 < 10)
					printf("\t\t  Solve");
				else
					printf("\t  Solve");
				printf("   Menu");
			}
		}
		pi.n = m.n;
		mp();
		if (cond < 1)
			if (cursorPos.y - consoleRect.top - 30 <
				16 * cfi.dwFontSize.Y &&
				cursorPos.y - consoleRect.top - 30 >
				15 * cfi.dwFontSize.Y &&
				cursorPos.x - consoleRect.left >
				27 * cfi.dwFontSize.X &&
				cursorPos.x - consoleRect.left <
				32 * cfi.dwFontSize.X) {
				m.n = 92;
			}
			else if (cursorPos.y - consoleRect.top - 30 <
				16 * cfi.dwFontSize.Y &&
				cursorPos.y - consoleRect.top - 30 >
				15 * cfi.dwFontSize.Y &&
				cursorPos.x - consoleRect.left >
				16 * cfi.dwFontSize.X &&
				cursorPos.x - consoleRect.left <
				24 * cfi.dwFontSize.X) {
				m.n = 93;
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					for (y.n = 1; y.n < 10; y.n++)
						g[y.n - 1].n = y.n;
					//printf("\n");
					
					
					// Sudoku solving

					
					
					for (m.n = 0; m.n < 81; m.n++) {
						//printf("%d ",m.n);
						//getch();
						if (c[m.n].n == 0) {
							//printf(" %d ",m.n);
							//getch();
							g[m.n].n = 1;
						tp:	v.n = m.n / 27;
							pi.n = (m.n % 9) / 3;
							for (y.n = 0; y.n < 3; y.n++)
								for (j.n = 0; j.n < 3; j.n++)
									if ((v.n * 27 + 3 * pi.n + 9 * y.n + j.n) != m.n) {
										if (p[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n == 11) {
											if (c[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n ==
												g[m.n].n)
											{ //printf(" i1");
												goto en;
											}
										}
										else {
											if (p[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n ==
												g[m.n].n)
											{//printf(" i2"); /*%d %d=%d ",v.n * 27 + 3 * pi.n + 9 * y.n + j.n, g[g[9+m.n].n].n,p[v.n * 27 + 3 * pi.n + 9 * y.n + j.n].n);*/
												goto en;
											}
										}
									}
							//printf(" r");//getch();
							for (k.n = 0; k.n < 9; k.n++)
								if (9 * ((int)m.n / 9) + k.n != m.n)
									if (p[9 * ((int)m.n / 9) + k.n].n == 11) {
										if (c[9 * ((int)m.n / 9) + k.n].n == g[m.n].n) {
											//printf(" j1");
											goto en;
										}
									}
									else
										if (p[9 * ((int)m.n / 9) + k.n].n == g[m.n].n) {
											//printf(" j2");
											goto en;
										}
							for (f.n = 0; f.n < 9; f.n++)
								if ((m.n % 9) + f.n * 9 != m.n)
									if (p[(m.n % 9) + f.n * 9].n == 11) {
										if (c[(m.n % 9) + f.n * 9].n == g[m.n].n) {
											//printf(" u1");
											goto en;
										}
									}
									else
										if (p[(m.n % 9) + f.n * 9].n == g[m.n].n) {
											//printf(" u2");
											goto en;
										}
							p[m.n].n = g[m.n].n;
							//printf(" qq");//getch();
							//system("cls");printf("\n");dis();Sleep(0);//getch();
						}
					}continue;

				en:	if (g[m.n].n < 9) {
					//printf(" ll");
					g[m.n].n++;
					goto tp;
				}
				else {
					//printf(" hh");//getch();
					p[m.n].n = 10;
					while (m.n < 127 && c[--m.n].n != 0);
					//system("cls");printf("\n");dis();Sleep(0);
					if (m.n == 127) {
						system("cls");
						printf("Failed to solve.\nThe grid may be mistaken or wrong\nor maybe solution doesn't exist.\n\nPress any key to go back");
						while (GetAsyncKeyState(VK_LBUTTON) & 0x8000); while (!kbhit() && !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)); while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
						goto ch4;
					}
					else
						goto en;
				}
				}

			}



		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left mouse button
			if (i.n != m.n) {
				i.n = m.n;
				goto re;
			}
		}
		if (kbhit()) {
			e.n = getch();
			if (e.n > 48 && e.n < 58 && i.n < 81)
			{
				c[i.n].n = e.n - 48;
				p[i.n].n = 11;
			}
			else if (e.n == 48)
			{
				c[i.n].n = 0;
				p[i.n].n = 10;
			}
			goto re;
		}


		if (i.n == 92) {
			i.n = 0;
			goto m;
		}
	}
}

#include <windows.h>
#include <stdio.h>

void main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
	system("conhost sudoku.exe");
}

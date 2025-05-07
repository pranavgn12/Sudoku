#include <windows.h>
#include <stdio.h>

void main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
	system("conhost sudoku.exe");  //conhost command brings up legcay or old cmd that existed before newer windows terminal.
}

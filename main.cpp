#include <iostream>
#include <windows.h>

int main() {
    const int MY_HOTKEY_DOWN = 1;
    const int MY_HOTKEY_UP = 2;
    const int MY_HOTKEY_MUTE = 3;
    const int MY_MOD_CONTROL = MOD_CONTROL   | MOD_NOREPEAT;
    const int MY_MOD_CONTROL2 = MOD_SHIFT    | MOD_NOREPEAT;
    const int MY_MOD_CONTROL3 = MOD_ALT      | MOD_NOREPEAT;

    ShowWindow(GetConsoleWindow(), SW_HIDE); // Скрываем окно командной строки

    // Регистрируем горячие клавиши Ctrl+Down и Ctrl+Up
    if (!RegisterHotKey(NULL, MY_HOTKEY_DOWN, MY_MOD_CONTROL, VK_LEFT)) {
        std::cerr << "Не удалось зарегистрировать горячую клавишу Ctrl+Down!" << std::endl;
        return 1;
    }
    if (!RegisterHotKey(NULL, MY_HOTKEY_UP, MY_MOD_CONTROL, VK_RIGHT)) {
        std::cerr << "Не удалось зарегистрировать горячую клавишу Ctrl+Up!" << std::endl;
        return 1;
    }
    if (!RegisterHotKey(NULL, MY_HOTKEY_MUTE, MY_MOD_CONTROL, VK_DOWN)) {
        std::cerr << "Не удалось зарегистрировать горячую клавишу Ctrl+Up!" << std::endl;
        return 1;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == MY_HOTKEY_DOWN) {
                keybd_event(VK_VOLUME_DOWN, 0, KEYEVENTF_KEYUP, 0); // Сначала отпустим клавишу (если она уже нажата)
                keybd_event(VK_VOLUME_DOWN, 0, 0, 0); // Затем нажмем клавишу
                keybd_event(VK_VOLUME_DOWN, 0, KEYEVENTF_KEYUP, 0); // И отпустим снова
            }
            else if (msg.wParam == MY_HOTKEY_UP) {
                keybd_event(VK_VOLUME_UP, 0, KEYEVENTF_KEYUP, 0); // Сначала отпустим клавишу (если она уже нажата)
                keybd_event(VK_VOLUME_UP, 0, 0, 0); // Затем нажмем клавишу
                keybd_event(VK_VOLUME_UP, 0, KEYEVENTF_KEYUP, 0); // И отпустим снова
            }
            else if (msg.wParam == MY_HOTKEY_MUTE) {
                keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0); // Сначала отпустим клавишу (если она уже нажата)
                keybd_event(VK_VOLUME_MUTE, 0, 0, 0); // Затем нажмем клавишу
                keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0); // И отпустим снова
            }
        }
    }

    // Отменяем регистрацию горячих клавиш перед завершением программы
    UnregisterHotKey(NULL, MY_HOTKEY_DOWN);
    UnregisterHotKey(NULL, MY_HOTKEY_UP);

    return 0;
}

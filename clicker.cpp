#include "framework.h"

clicker* AutoClicker;

DWORD clicker::event_clicker(void) {
    while (true) {
        if (this->g_bThreadRunning) {
            if (is_left_down() && this->g_bLeftClick) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(
                    this->own_wait ? this->own_int[0] : 30
                ));
            }
            if (is_right_down() && this->g_bRightClick) {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, 0, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(
                    this->own_wait ? this->own_int[1] : 20
                ));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}

void clicker::change_state(bool state) {
    this->g_bThreadRunning = state;
    config->write_state(state);
}

void clicker::change_own(bool state) {
    this->own_wait = state;
    config->write_own_state(state);
}

void clicker::set_left_wait(int value) {
    this->own_int[0] = value;
}

void clicker::set_right_wait(int value) {
    this->own_int[1] = value;
}

void clicker::set_keys_available(bool left, bool right) {
    this->g_bLeftClick = left;
    this->g_bRightClick = right;
    config->write_buttons(left, right);
}

bool clicker::is_left_down() {
    return ((GetKeyState(VK_XBUTTON2) & 0x8000));
}

bool clicker::is_right_down() {
    return ((GetKeyState(VK_XBUTTON1) & 0x8000));
}
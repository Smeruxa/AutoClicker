#pragma once

class clicker {
private:
	bool g_bThreadRunning = false;
	bool g_bRightClick = false;
	bool g_bLeftClick = false;

	bool own_wait = false;
	int own_int[2] = {-1, -1};

	HWND hWnd;

	HANDLE hThread;
	Config* config;
public:

	bool is_left_down();
	bool is_right_down();

	void set_keys_available(bool left, bool right);
	void change_state(bool state);

	void change_own(bool state);
	void set_left_wait(int value);
	void set_right_wait(int value);

	DWORD event_clicker(void);

	// Inizialization thread

	static DWORD WINAPI _iniz(void* Param)
	{
		clicker* This = (clicker*)Param;
		return This->event_clicker();
	}

	clicker(HWND hWnd, Config* config) {
		this->hWnd = hWnd;
		this->config = config;

		this->g_bLeftClick = config->get_left_button();
		this->g_bRightClick = config->get_right_button();
		this->g_bThreadRunning = config->get_state();
		this->own_wait = config->get_own_wait();
		this->own_int[0] = config->get_left_wait();
		this->own_int[1] = config->get_right_wait();

		DWORD ThreadID;
		CreateThread(NULL, 0, _iniz, (void*)this, 0, &ThreadID);
	}
};


extern clicker* AutoClicker;
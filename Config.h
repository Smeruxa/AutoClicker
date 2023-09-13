#pragma once

class Config {
private:
	std::string NAME = "config.json";
public:
	nlohmann::json data;
	DWORD calculate_value_checkbox(std::string key);

	void write_state(bool state);
	void write_buttons(bool lbutton, bool rbutton);
	void write_own_state(bool state);

	bool get_left_button();
	bool get_right_button();
	bool get_own_wait();
	bool get_state();

	int get_left_wait();
	int get_right_wait(); 

	void set_left_wait(int value);
	void set_right_wait(int value);

	void load();
	void save();
};

extern Config* config;
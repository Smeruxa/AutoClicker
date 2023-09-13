#include "framework.h"

Config* config;

void Config::save() {
    std::ofstream output(this->NAME);

    if (output.is_open()) {
        output << std::setw(4) << this->data << std::endl;
        output.close();
    }
}

void Config::load() {
    std::ifstream input(this->NAME);

    if (input.is_open()) {
        nlohmann::json read;
        input >> read;
        input.close();

        if (read.is_object()) {
            this->data["state"] = read["state"];
            this->data["own_wait"] = read["own_wait"];

            this->data["lbutton"] = read["lbutton"];
            this->data["rbutton"] = read["rbutton"];

            this->data["wait_lbutton"] = read["wait_lbutton"];
            this->data["wait_rbutton"] = read["wait_rbutton"];
        }
    }
    else {
        this->data["state"] = false;
        this->data["own_wait"] = false;

        this->data["lbutton"] = false;
        this->data["rbutton"] = false;

        this->data["wait_lbutton"] = 30;
        this->data["wait_rbutton"] = 20;

        this->save();
    }
}

DWORD Config::calculate_value_checkbox(std::string key) {
    if (this->data[key])
        return BST_CHECKED;
    else
        return BST_UNCHECKED;
    return 0xfff;
}

void Config::set_left_wait(int value) {
    this->data["wait_lbutton"] = value;
    this->save();
}

void Config::set_right_wait(int value) {
    this->data["wait_rbutton"] = value;
    this->save();
}

int Config::get_left_wait() {
    return this->data["wait_lbutton"];
}

int Config::get_right_wait() {
    return this->data["wait_rbutton"];
}

bool Config::get_own_wait() {
    return this->data["own_wait"];
}

bool Config::get_state() {
    return this->data["state"];
}

bool Config::get_left_button() {
    return this->data["lbutton"];
}

bool Config::get_right_button() {
    return this->data["rbutton"];
}

void Config::write_buttons(bool lbutton, bool rbutton) {
    this->data["lbutton"] = lbutton;
    this->data["rbutton"] = rbutton;
    this->save();
}

void Config::write_own_state(bool state) {
    this->data["own_wait"] = state;
    this->save();
}

void Config::write_state(bool state) {
    this->data["state"] = state;
    this->save();
}
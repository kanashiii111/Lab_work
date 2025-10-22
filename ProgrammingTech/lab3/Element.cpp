#include <iostream>
#include "Element.h"

Element::Element(std::string p_url, std::string p_login, std::string p_password, std::string p_notes) {
	url = p_url;
	login = p_login;
	password = p_password;
	notes = p_notes;
	std::cout << "Element created: " << url << ", " << login << ", " << password << ", " << notes << std::endl;
}

std::string Element::gen_password(int length) {
	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"!@#$%^&*()_+";
	const size_t max_index = (sizeof(charset) - 1);
	std::string str(length, 0);
	for (int i = 0; i < length; ++i) {
		str[i] = charset[rand() % max_index];
	}
	return str;
}

std::string Element::get_encrypted_password(std::string password) {
	// Simple XOR encryption for demonstration purposes
	std::string encrypted = password;
	char key = 'K'; // Simple key
	for (size_t i = 0; i < encrypted.size(); ++i) {
		encrypted[i] ^= key;
	}
	return encrypted;
}

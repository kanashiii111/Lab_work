#pragma once
class Element {
	public:
		Element(std::string p_url, std::string p_login, std::string p_password, std::string p_notes);

		std::string get_url() const { return url; }
		std::string get_login() const { return login; }
		std::string get_password() const { return password; }
		std::string get_notes() const { return notes; }

		std::string gen_password(int length);
		std::string get_encrypted_password(std::string password);
	private:
		std::string url;
		std::string login;
		std::string password;
		std::string notes;
};


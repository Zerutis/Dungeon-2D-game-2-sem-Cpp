#pragma once
#include <sstream>

class init_window_failure : public std::runtime_error {
	std::string m_message;
public:
	init_window_failure(const char* message) : runtime_error("Failed to create window") {
		std::stringstream ss;
		ss << "Failed to create window: " << message;
		m_message = ss.str();
	}

	const char* what() const noexcept {
		return m_message.c_str();
	}
};

class init_renderer_failure : public std::runtime_error {
	std::string m_message;
public:
	init_renderer_failure(const char* message) : runtime_error("Failed to create window") {
		std::stringstream ss;
		ss << "Failed to create renderer: " << message;
		m_message = ss.str();
	}

	const char* what() const noexcept {
		return m_message.c_str();
	}
};

class load_image_failure : public std::runtime_error {
	std::string m_message;
public:
	load_image_failure(const char* image) : runtime_error("Failed to load image") {
		std::stringstream ss;
		ss << "Failed to load image: " << image;
		m_message = ss.str();
	}

	const char* what() const noexcept {
		return m_message.c_str();
	}
};

class open_file_failure : public std::runtime_error {
	std::string m_message;
public:
	open_file_failure(const char* filename) : runtime_error("Failed to open file") {
		std::stringstream ss;
		ss << "Failed to open file: " << filename;
		m_message = ss.str();
	}

	const char* what() const noexcept {
		return m_message.c_str();
	}
};

class undefined_character_type : public std::runtime_error {
	std::string m_message;
public:
	undefined_character_type(const std::string& type) : runtime_error("Failed to identify character type") {
		std::stringstream ss;
		ss << "Failed to identify character type: " << type;
		m_message = ss.str();
	}

	const char* what() const noexcept {
		return m_message.c_str();
	}
};
#pragma once

#include <exception>
#include <string>

class NoSuchFileException : public std::exception {
    std::string message;

public:
    NoSuchFileException(const std::string &file_path) {
        message =
                "ERROR: TextureManager: something went wrong while reading file " +
                file_path;
    };

    const char *what() const noexcept override { return message.c_str(); }
};

class NoSuchTextureWithNameException : public std::exception {
    std::string message;

public:
    NoSuchTextureWithNameException(const std::string &name) {
        message = "ERROR: TextureManager: no texture with name '" + name + "'";
    };

    const char *what() const noexcept override { return message.c_str(); }
};

class NameAlreadyTakenForTextureException : public std::exception {
    std::string message;

public:
    NameAlreadyTakenForTextureException(const std::string &name) {
        message = "ERROR: TextureManager: name '" + name + "' was already taken";
    };

    const char *what() const noexcept override { return message.c_str(); }
};
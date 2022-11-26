#pragma once

#include <string>

class Scanner
{
private:
    std::string _input;
    std::string::size_type _pos = 0;
    const std::vector<std::string> _tokens = {
        "Circle",
        "Rectangle",
        "Triangle",
        "CompoundShape",
        "Vector",
        "(",
        ")",
        ","};

    void _skipWhiteSpace()
    {
        while (_input[_pos] == ' ' || _input[_pos] == '\n')
            _pos++;
    }

    bool _isNumber(char c)
    {
        return c >= '0' && c <= '9';
    }

public:
    Scanner(std::string input = "") : _input{input} {}

    std::string next()
    {
        _skipWhiteSpace();
        if (isDone())
            throw std::string("Scanner has navigated to the end of the input.");

        for (std::string token : _tokens)
        {
            if (_input.compare(_pos, token.length(), token) == 0)
            {
                _pos += token.length();
                return token;
            }
        }

        // token not found
        return "";
    }

    double nextDouble()
    {
        _skipWhiteSpace();
        if (isDone())
            throw std::string("Scanner has navigated to the end of the input.");

        std::string s = "";
        if (_input[_pos] == '-')
            s += _input[_pos++];

        while (_isNumber(_input[_pos]))
            s += _input[_pos++];

        if (_input[_pos] == '.')
            s += _input[_pos++];

        while (_isNumber(_input[_pos]))
            s += _input[_pos++];

        return std::stod(s);
    }

    bool isDone()
    {
        _skipWhiteSpace();
        return _pos == _input.length();
    }
};

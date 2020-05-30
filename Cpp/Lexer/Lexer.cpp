//
//
//
//  Made by Joonas Lehto at 10/5/2020 0:47AM
//  Few fixes by Gabe at 10/5/2020 0:47:00001AM
//
//
//
#include "../../H/Lexer/Lexer.h"
#include <stdexcept>
#include <sstream>
#include <optional>
#include <algorithm>
#include <fstream>

constexpr char LineEnding = '\n';


char Lexer::SingleLineCommentIdentifier = 0;
char Lexer::StringIdentifier = 0;
char Lexer::DecimalSeparator = 0;
char Lexer::ExponentSeparator = 0;

vector<string> Lexer::Operators;
vector<string> Lexer::Keywords;

enum class Type
{
    UNSPECIFIED,
    TEXT,
    COMMENT,
    NUMBER,
    PARENTHESIS,
    OPERATOR,
    STRING,
    END
};

struct Area
{
    Type Type;

    string Text;

    Position Start;
    Position End;
};

template <typename T>
bool Exists(const vector<T> &source, const T &value)
{
    return find(source.begin(), source.end(), value) != source.end();
}

char GetParenthesisClosing(char opening)
{
    if (opening == '(')
    {
        return ')';
    }
    else if (opening == '[')
    {
        return ']';
    }
    else if (opening == '{')
    {
        return '}';
    }

    stringstream error;
    error << "Unrecognized parenthesis opening '" << opening << "'";

    throw runtime_error(error.str().c_str());
}

string GetError(const Position &position, const char *message)
{
    stringstream error;
    error << "Line: " << position.GetFriendlyLine() << ", Character: " << position.GetFriendlyCharacter() << " | " << message;
    return error.str();
}

bool IsOperator(char c)
{
    return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || c == '^' || c == '|') && c != Lexer::SingleLineCommentIdentifier && c != Lexer::StringIdentifier;
}

bool IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool IsText(char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_';
}

bool IsParenthesis(char c)
{
    return c == '(' || c == '[' || c == '{' || c == ')' || c == ']' || c == '}';
}

bool IsComment(char c)
{
    return c == Lexer::SingleLineCommentIdentifier;
}

bool IsString(char c)
{
    return c == Lexer::StringIdentifier;
}

Type GetType(char c)
{
    if (IsText(c))
    {
        return Type::TEXT;
    }
    else if (IsDigit(c))
    {
        return Type::NUMBER;
    }
    else if (IsParenthesis(c))
    {
        return Type::PARENTHESIS;
    }
    else if (IsOperator(c))
    {
        return Type::OPERATOR;
    }
    else if (IsComment(c))
    {
        return Type::COMMENT;
    }
    else if (IsString(c))
    {
        return Type::STRING;
    }
    else if (c == LineEnding)
    {
        return Type::END;
    }

    return Type::UNSPECIFIED;
}

bool IsPartOf(Type previous, Type current, char previous_symbol, char current_symbol)
{
    if (current == previous || previous == Type::UNSPECIFIED)
    {
        return true;
    }

    switch (previous)
    {

    case Type::TEXT:
    {
        return current == Type::NUMBER;
    }

    case Type::NUMBER:
    {
        return current_symbol == Lexer::DecimalSeparator ||                                                       // Example: 7.0
               current_symbol == Lexer::ExponentSeparator ||                                                      // Example: 100e0
               (previous_symbol == Lexer::ExponentSeparator && (current_symbol == '+' || current_symbol == '-')); // Examples: 3.14159e+10, 10e-10
    }

    default:
        return false;
    }
}

Position SkipSpaces(const string &text, Position &position)
{
    while (position.GetAbsolute() < text.size())
    {
        char c = text[position.GetAbsolute()];

        if (c != ' ')
        {
            break;
        }
        else
        {
            position.NextCharacter();
        }
    }

    return position;
}

Position SkipParenthesis(const string &text, const Position &start)
{
    Position position = start.Clone();

    char opening = text[position.GetAbsolute()];
    char closing = GetParenthesisClosing(opening);

    int count = 0;

    while (position.GetAbsolute() < text.size())
    {
        char c = text[position.GetAbsolute()];

        if (c == LineEnding)
        {
            position.NextLine();
        }
        else
        {
            if (c == opening)
            {
                count++;
            }
            else if (c == closing)
            {
                count--;
            }

            position.NextCharacter();
        }

        if (count == 0)
        {
            return position;
        }
    }

    throw runtime_error(GetError(start, "Couldn't find closing parenthesis").c_str());
}

Position SkipComment(const string &text, const Position &start)
{
    int i = text.find(LineEnding, start.GetAbsolute());

    if (i != -1)
    {
        int length = i - start.GetAbsolute();
        return Position(start.GetLine(), start.GetCharacter() + length, i).NextLine();
    }
    else
    {
        int length = text.size() - start.GetAbsolute();
        return Position(start.GetLine(), start.GetCharacter() + length, text.size());
    }
}

Position SkipString(const string &text, const Position &start)
{
    int i = text.find(Lexer::StringIdentifier, start.GetAbsolute() + 1);
    int j = text.find(LineEnding, start.GetAbsolute() + 1);

    if (i == -1 || j != -1 && j < i)
    {
        throw runtime_error(GetError(start, "Couldn't find the end of the string").c_str());
    }

    int length = i - start.GetAbsolute();

    return Position(start.GetLine(), start.GetCharacter() + length, i + 1);
}

optional<Area> GetNextComponent(const string &text, Position start)
{
    // Firsly the spaces must be skipped to find the next token
    Position position = SkipSpaces(text, start);

    // Verify there's text to iterate
    if (position.GetAbsolute() == text.size())
    {
        return nullopt;
    }

    Area area;
    area.Start = position.Clone();
    area.Type = GetType(text[position.GetAbsolute()]);

    switch (area.Type)
    {

    case Type::COMMENT:
    {
        area.End = SkipComment(text, area.Start);
        area.Text = text.substr(area.Start.GetAbsolute(), area.End.GetAbsolute() - area.Start.GetAbsolute());
        return area;
    }

    case Type::PARENTHESIS:
    {
        area.End = SkipParenthesis(text, area.Start);
        area.Text = text.substr(area.Start.GetAbsolute(), area.End.GetAbsolute() - area.Start.GetAbsolute());
        return area;
    }

    case Type::END:
    {
        area.End = position.Clone().NextLine();
        area.Text = "\n";
        return area;
    }

    case Type::STRING:
    {
        area.End = SkipString(text, area.Start);
        area.Text = text.substr(area.Start.GetAbsolute(), area.End.GetAbsolute() - area.Start.GetAbsolute());
        return area;
    }

    default:
        break;
    }

    // Possible types are now: TEXT, NUMBER, OPERATOR
    while (position.GetAbsolute() < text.size())
    {
        char current_symbol = text[position.GetAbsolute()];

        if (IsParenthesis(current_symbol))
        {
            // There cannot be number and content tokens side by side
            if (area.Type == Type::NUMBER)
            {
                throw runtime_error(GetError(position, "Missing operator between number and parenthesis").c_str());
            }

            break;
        }

        Type type = GetType(current_symbol);
        char previous_symbol = position.GetAbsolute() == 0 ? (char)0 : text[position.GetAbsolute() - 1];

        if (!IsPartOf(area.Type, type, previous_symbol, current_symbol))
        {
            break;
        }

        position.NextCharacter();
    }

    area.End = position;
    area.Text = text.substr(area.Start.GetAbsolute(), area.End.GetAbsolute() - area.Start.GetAbsolute());

    return area;
}

Component ParseTextComponent(string text)
{
    if (Exists(Lexer::Operators, text))
    {
        return Component(text, OPERATOR_COMPONENT);
    }
    else if (Exists(Lexer::Keywords, text))
    {
        return Component(text, KEYWORD_COMPONENT);
    }
    else
    {
        return Component(text, TEXT_COMPONENT);
    }
}

optional<int> TryParseInt(string text)
{
    try
    {
        return stoi(text);
    }
    catch (...)
    {
        return nullopt;
    }
}

optional<int64_t> TryParseLong(string text)
{
    try
    {
        return stoll(text);
    }
    catch (...)
    {
        return nullopt;
    }
}

optional<double> TryParseDouble(string text)
{
    try
    {
        return stod(text);
    }
    catch (...)
    {
        return nullopt;
    }
}

string GetNumberPart(string text)
{
    int end = 0;

    for (; end < text.size() && (IsDigit(text[end]) || text[end] == Lexer::DecimalSeparator); end++);

    return text.substr(0, end);
}

int GetExponent(const string& text)
{
    int exponent_start = text.find(Lexer::ExponentSeparator);

    if (exponent_start == -1)
    {
        return 0;
    }
    else
    {
        exponent_start++;

        int index = exponent_start;

        // Ensure that there's the exponent value
        if (index == text.size())
        {
            stringstream message;
            message << "Invalid number exponent '" << text << "'";

            throw runtime_error(message.str().c_str());
        }

        // Skip the potential exponent sign
        if (text[index + 1] == '+' || text[index + 1] == '-')
        {
            index++;

            // Ensure that there's the exponent value
            if (index == text.size())
            {
                stringstream message;
                message << "Invalid number exponent '" << text << "'";

                throw runtime_error(message.str().c_str());
            }
        }

        int exponent_end = index;

        // Get the exponent value's end index
        for (; exponent_end < text.size() && IsDigit(text[exponent_end]); exponent_end++);

        if (auto exponent = TryParseInt(text.substr(exponent_start, exponent_end)))
        {
            return exponent.value();
        }
        else
        {
            stringstream message;
            message << "Invalid number exponent '" << text << "'";

            throw runtime_error(message.str().c_str());
        }
    }
}

bool IsDecimal(string text)
{
    return text.find(Lexer::DecimalSeparator) != -1;
}

Component CreateNumberComponent(string text, const Position& position)
{
    int exponent = GetExponent(text);
    string number_part = GetNumberPart(text);

    if (IsDecimal(text))
    {
        if (auto number = TryParseDouble(number_part))
        {
            double value = number.value() * pow(10.0, exponent);

            return Component(to_string(value), NUMBER_COMPONENT);
        }
        else
        {
            stringstream message;
            message << "Invalid decimal number '" << text << "'";

            throw runtime_error(GetError(position, message.str().c_str()).c_str());
        }
    }
    else
    {
        if (auto number = TryParseLong(number_part))
        {
            int64_t value = number.value() * (int64_t)pow(10.0, exponent);

            return Component(to_string(value), NUMBER_COMPONENT);
        }
        else
        {
            stringstream message;
            message << "Invalid integer number '" << text << "'";

            throw runtime_error(GetError(position, message.str().c_str()).c_str());
        }
    }
}

Component CreateParenthesisComponent(string text, const Position& position)
{
    Component component(text, PAREHTHESIS_COMPONENT);
    component.Components = Lexer::GetComponents(text.substr(1, text.size() - 2));

    return component;
}

Component ParseComponent(const Area& area, Position& anchor)
{
    switch (area.Type)
    {
    case Type::TEXT:
        return ParseTextComponent(area.Text);
    case Type::NUMBER:
        return CreateNumberComponent(area.Text, area.Start);
    case Type::OPERATOR:
        return Component(area.Text, OPERATOR_COMPONENT);
    case Type::PARENTHESIS:
        return CreateParenthesisComponent(area.Text, anchor += area.Start);
    case Type::END:
        return Component("\n", END_COMPONENT);
    case Type::STRING:
        return Component(area.Text, STRING_COMPONENT);
    case Type::COMMENT:
        return Component(area.Text, COMMENT_COMPONENT);
    default:
    {
        anchor += area.Start;

        stringstream message;
        message << "Unrecognized token '" << area.Text << "'";

        throw runtime_error(GetError(anchor += area.Start, message.str().c_str()).c_str());
    }

    }
}

vector<Component> GetComponents(string text, Position anchor)
{
    vector<Component> components;
    Position position;

    while (position.GetAbsolute() < text.size())
    {
        optional<Area> area = GetNextComponent(text, position);

        if (!area)
        {
            break;
        }

        Component component = ParseComponent(area.value(), anchor);
        component.Location = (anchor += area->Start);
        components.push_back(component);

        position = area->End;
    }

    return components;
}

vector<Component> Lexer::GetComponents(string text)
{
    return GetComponents(text, Position());
}

vector<Component> Lexer::GetComponentsFromFile(string file)
{
    if (Lexer::SingleLineCommentIdentifier == 0 || Lexer::StringIdentifier == 0 || Lexer::DecimalSeparator == 0 || Lexer::ExponentSeparator == 0)
    {
        throw runtime_error("Please configure all the identifiers and separators needed by the lexer");
    }

    ifstream stream(file);

    if (!stream.is_open())
    {
        stringstream message;
        message << "Couldn't find or open file '" << file << "'";

        throw runtime_error(message.str().c_str());
    }

    string text;
    string line;

    while (getline(stream, line))
    {
        replace(line.begin(), line.end(), '\t', ' ');
        text += line + LineEnding;
    }

    stream.close();

    return GetComponents(text);
}
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
#include <cmath>
#include "../../H/UI/Safe.h"
#include "../../H/UI/Usr.h"

constexpr char LineEnding = '\n';
constexpr char BITWISE_XOR = '\xa4';

extern Usr* sys;

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
    HEXADECIMAL,
    END
};

struct Area
{
    Type Type = Type::UNSPECIFIED;

    string Text;

    Position Start;
    Position End;
};

template <typename T>
bool Exists(const vector<T> &source, const T &value)
{
    return find(source.begin(), source.end(), value) != source.end();
}

char GetParenthesisClosing(char opening, Position p)
{
    if (opening == '(')
    {
        return ')';
    }
    if (opening == '[')
    {
        return ']';
    }
    if (opening == '{')
    {
        return '}';
    }

    Report(Observation(ERROR, (string)"'" + opening + (string)"'", p, "Unrecognized parenthesis opening"));
}

/// <summary>
/// Returns all the characters which can mix with the specified character.
/// If this function returns null, it means the specified character can mix with any character.
/// </summary>
const char* GetMixingCharacters(char c)
{
    switch (c)
    {
        case '.': return ".0123456789";
        case ',': return "";
        case ':': return "";
        case '<': return "=";
        case '>': return "=-";
        default: return nullptr;
    }
}

/// <summary>
/// Returns whether the two specified characters can mix
/// </summary>
bool Mixes(char a, char b)
{
    auto x = GetMixingCharacters(a);
    if (x != nullptr) return strchr(x, b) != nullptr;

    auto y = GetMixingCharacters(b);
    if (y != nullptr) return strchr(y, a) != nullptr;

    return true;
}

bool IsOperator(char c)
{
    return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || c == '^' || c == '|' || c == BITWISE_XOR) && c != Lexer::SingleLineCommentIdentifier && c != Lexer::StringIdentifier ;
}

bool IsStartOfHexadecimal(char current, char next)
{
    return current == '0' && next == 'x';
}

bool IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool IsText(char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' || c == '@';
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

Type GetType(char current, char next)
{
    if (IsText(current)) return Type::TEXT;
    if (IsStartOfHexadecimal(current, next)) return Type::HEXADECIMAL;
    if (IsDigit(current))  return Type::NUMBER;
    if (IsParenthesis(current)) return Type::PARENTHESIS;
    if (IsOperator(current)) return Type::OPERATOR;
    if (IsComment(current)) return Type::COMMENT;
    if (IsString(current)) return Type::STRING;
    if (current == LineEnding) return Type::END;

    return Type::UNSPECIFIED;
}

bool IsPartOf(Type previous_type, Type current_type, char previous, char current, char next)
{
    // Ensure the previous and the current character mix
    if (!Mixes(previous, current)) return false;

    if (current_type == previous_type || previous_type == Type::UNSPECIFIED) return true;

    switch (previous_type)
    {

    case Type::TEXT: return current_type == Type::NUMBER;

    case Type::HEXADECIMAL: return current_type == Type::NUMBER || 
            (previous == '0' && current == 'x') ||
            (current >= 'a' && current <= 'f') || (current >= 'A' && current <= 'F');

    case Type::NUMBER:
    {
        return (current == Lexer::DecimalSeparator && IsDigit(next)) || // Example: 7.0
               current == Lexer::ExponentSeparator || // Example: 100e0
               (previous == Lexer::ExponentSeparator && (current == '+' || current == '-')); // Examples: 3.14159e+10, 10e-10
    }

    default:
        return false;
    }
}

Position SkipSpaces(const string &text, Position &position)
{
    while (position.GetLocal() < text.size())
    {
        char current = text[position.GetLocal()];
        if (current != ' ') break;

        position.NextCharacter();
    }

    return position;
}

Position SkipComment(const string& text, const Position& start)
{
    int i = (int)text.find(LineEnding, start.GetLocal());

    if (i != -1)
    {
        int length = i - start.GetLocal();
        return Position(start.GetLine(), start.GetCharacter() + length, start.GetLocal() + length, i).NextLine();
    }
    int length = (int)text.size() - start.GetLocal();
    return Position(start.GetLine(), start.GetCharacter() + length, start.GetLocal() + length, (int)text.size());
}

Position SkipString(const string &text, const Position &start)
{
    int i = (int)text.find(Lexer::StringIdentifier, (size_t)start.GetLocal() + 1);
    int j = (int)text.find(LineEnding, (size_t)start.GetLocal() + 1);

    if (i == -1 || j != -1 && j < i)
    {
        Report(Observation(ERROR, "Couldn't find the end of the string", start, ""));
    }

    int length = i + 1 - start.GetLocal();

    return Position(start.GetLine(), start.GetCharacter() + length, start.GetLocal() + length, i + 1);
}

Position SkipParenthesis(const string &text, const Position &start)
{
    Position position = start.Clone();

    char opening = text[position.GetLocal()];
    char closing = GetParenthesisClosing(opening, start);

    int count = 0;

    while (position.GetLocal() < text.size())
    {
        char current = text[position.GetLocal()];

        if (current == LineEnding)
        {
            position.NextLine();
        }
        else if (current == Lexer::SingleLineCommentIdentifier)
        {
            position = SkipComment(text, position);
        }
        else if (current == Lexer::StringIdentifier)
        {
            position = SkipString(text, position);
        }
        else
        {
            if (current == opening) { count++; }
            else if (current == closing) { count--; }

            position.NextCharacter();
        }

        if (count == 0) return position;
    }

    Report(Observation(ERROR, (string)"'" + closing + (string)"'", start, "Couldn't find closing parenthesis"));
}

optional<Area> GetNextComponent(const string &text, Position start)
{
    // Firsly the spaces must be skipped to find the next token
    Position position = SkipSpaces(text, start);

    // Verify there's text to iterate
    if (position.GetLocal() == text.size()) return nullopt;

    char current = text[position.GetLocal()];
    char next = position.Local + 1 < text.size() ? text[position.GetLocal() + 1] : (char)0;

    Area area;
    area.Start = position.Clone();
    area.Type = GetType(current, next);

    switch (area.Type)
    {

    case Type::COMMENT:
    {
        area.End = SkipComment(text, area.Start);
        area.Text = text.substr(area.Start.GetLocal(), (size_t)area.End.GetLocal() - area.Start.GetLocal());
        return area;
    }

    case Type::PARENTHESIS:
    {
        area.End = SkipParenthesis(text, area.Start);
        area.Text = text.substr(area.Start.GetLocal(), (size_t)area.End.GetLocal() - area.Start.GetLocal());
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
        area.Text = text.substr(area.Start.GetLocal(), (size_t)area.End.GetLocal() - area.Start.GetLocal());
        return area;
    }

    default:
        break;
    }

    position.NextCharacter();

    // Possible types are now: TEXT, NUMBER, OPERATOR
    while (position.GetLocal() < text.size())
    {
        char previous = current;
        current = next;
        next = position.GetLocal() + 1 < text.size() ? text[position.GetLocal() + 1] : (char)0;

        if (IsParenthesis(current)) break;

        // Determine what area type the current character represents
        Type type = GetType(current, next);

        if (!IsPartOf(area.Type, type, previous, current, next)) break;

        position.NextCharacter();
    }

    area.End = position;
    area.Text = text.substr(area.Start.GetLocal(), (size_t)area.End.GetLocal() - area.Start.GetLocal());

    return area;
}

Component ParseTextComponent(string text)
{
    if (Exists(Lexer::Operators, text))
    {
        return Component(text, Flags::OPERATOR_COMPONENT);
    }
    if (Exists(Lexer::Keywords, text))
    {
        return Component(text, Flags::KEYWORD_COMPONENT);
    }
    return Component(text, Flags::TEXT_COMPONENT);
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

int GetExponent(const string& text, Position p)
{
    int exponent_start = (int)text.find(Lexer::ExponentSeparator);

    if (exponent_start == -1)
    {
        return 0;
    }
    exponent_start++;

    int index = exponent_start;

    // Ensure that there's the exponent value
    if (index == text.size())
    {
        Report(Observation(ERROR, text, p, "Invalid number exponent"));
    }

    // Skip the potential exponent sign
    if (text[(size_t)index + 1] == '+' || text[(size_t)index + 1] == '-')
    {
        index++;

        // Ensure that there's the exponent value
        if (index == text.size())
        {
            MSG_Type Terminate = ERROR;

            if (sys->Info.Is_Service) Terminate = WARNING;
            Report(Observation(Terminate, "Invalid number exponent '" + text + "'", p, "Invalid number exponent"));
        }
    }

    int exponent_end = index;

    // Get the exponent value's end index
    for (; exponent_end < text.size() && IsDigit(text[exponent_end]); exponent_end++);

    if (auto exponent = TryParseInt(text.substr(exponent_start, exponent_end)))
    {
        return exponent.value();
    }
    Report(Observation(ERROR, "'" + text + "'", p, "Invalid number exponent"));
}

bool IsDecimal(string text)
{
    return text.find(Lexer::DecimalSeparator) != -1;
}

Component CreateNumberComponent(string text, const Position& position)
{
    int exponent = GetExponent(text, position);
    string number_part = GetNumberPart(text);

    if (IsDecimal(text))
    {
        if (auto number = TryParseDouble(number_part))
        {
            double value = number.value() * pow((long double)10.0, (long double)exponent);

            return Component(to_string(value), Flags::NUMBER_COMPONENT);
        }
        Report(Observation(ERROR, "'" + text + "'", position, "Invalid decimal number"));
    }
    else
    {
        if (auto number = TryParseLong(number_part))
        {
            int64_t value = number.value() * (int64_t)pow(10.0, exponent);

            return Component(to_string(value), Flags::NUMBER_COMPONENT);
        }
        Report(Observation(ERROR, "'" + text + "'", position, "Invalid integer number"));
    }
}

vector<Component> GetComponents(string text, Position anc);

Component CreateParenthesisComponent(string text, Position position)
{
    Component component(text, Flags::PAREHTHESIS_COMPONENT);
    component.Components = GetComponents(text.substr(1, text.size() - 2), position.NextCharacter());

    return component;
}

unsigned long long ParseHexadecimal(const Area& area)
{
    char* end;
    auto text = area.Text.c_str() + 2;
    auto value = strtoull(text, &end, 16);

    if (*end != 0)
    {
        Report(Observation(ERROR, "'" + area.Text + "'", area.Start, "Invalid hexadecimal number"));
    }

    return value;
}

Component ParseComponent(const Area& area)
{
    switch (area.Type)
    {
        case Type::TEXT:
            return ParseTextComponent(area.Text);
        case Type::NUMBER:
            return CreateNumberComponent(area.Text, area.Start);
        case Type::OPERATOR:
            return Component(area.Text, Flags::OPERATOR_COMPONENT);
        case Type::PARENTHESIS:
            return CreateParenthesisComponent(area.Text, area.Start);
        case Type::END:
            return Component("\n", Flags::END_COMPONENT);
        case Type::STRING:
            return Component(area.Text, Flags::STRING_COMPONENT);
        case Type::COMMENT:
            return Component(area.Text, Flags::COMMENT_COMPONENT);
        case Type::HEXADECIMAL:
            return Component(to_string(ParseHexadecimal(area)), Flags::NUMBER_COMPONENT);
        default:
        {
            Report(Observation(ERROR, "'" + area.Text + "'", area.Start, "Unrecognized token"));
        }

    }
}

vector<Component> GetComponents(string text, Position anchor)
{
    vector<Component> components;
    Position position(anchor.GetLine(), anchor.GetCharacter(), 0, anchor.GetAbsolute());

    replace(text.begin(), text.end(), '\t', ' ');
    replace(text.begin(), text.end(), '\r', ' ');

    while (position.GetLocal() < text.size())
    {
        optional<Area> area = GetNextComponent(text, position);

        if (!area) break;

        Component component = ParseComponent(area.value());
        component.Location = area->Start;
        components.push_back(component);
        
        position = area->End;
    }

    return components;
}

vector<Component> Lexer::GetComponents(string text)
{
    return GetComponents(text, Position());
}

Component Lexer::GetComponent(string text)
{
    Position position(0, 0, 0, 0);

    replace(text.begin(), text.end(), '\t', ' ');
    replace(text.begin(), text.end(), '\r', ' ');

    optional<Area> area = GetNextComponent(text, position);

    if (!area)
    {
        Report(Observation(ERROR, "Could not generate component from string '" + text + "'.", position, ""));
    }

    Component component = ParseComponent(area.value());
    component.Location = area->Start;

    return component;
}

vector<Component> Lexer::GetComponentsFromFile(string file)
{
    if (Lexer::SingleLineCommentIdentifier == 0 || Lexer::StringIdentifier == 0 || Lexer::DecimalSeparator == 0 || Lexer::ExponentSeparator == 0)
    {
        Report(Observation(ERROR, "Please configure all the identifiers and separators needed by the lexer", Position(), ""));
    }

    ifstream stream(file);

    if (!stream.is_open())
    {
        stringstream message;
        Report(Observation(ERROR, "Couldn't find or open file '" + file + "'", Position(), ""));
    }

    string text;
    string line;

    while (getline(stream, line))
    {
        replace(line.begin(), line.end(), '\t', ' ');
        replace(text.begin(), text.end(), '\r', ' ');
        text += line + LineEnding;
    }

    stream.close();

    return GetComponents(text);
}
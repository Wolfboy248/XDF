#pragma once

#include "node.h"

#include <cctype>
#include <istream>
#include <stdexcept>
#include <string>
#include <iostream>

namespace xdf {

enum class TokenType {
  LBrace,
  RBrace,
  String,
  Identifier,
  End
};

static std::string GetTokenTypeName(TokenType type) {
  switch (type) {
    case TokenType::LBrace:
      return "Left Brace ";
    case TokenType::RBrace:
      return "Right Brace";
    case TokenType::End:
      return "End        ";
    case TokenType::Identifier:
      return "Identifier ";
    case TokenType::String:
      return "String     ";

    default:
      return "unknown";
  }
}

struct Token {
  TokenType type;
  std::string text;
};

class Tokenizer {
public:
  explicit Tokenizer(std::istream& in) : m_in(in) {}

  Token next() {
    skipWhitespace();

    if (!m_in) {
      return { TokenType::End, "" };
    }

    char c = m_in.peek();

    if (c == '{') {
      m_in.get();
      return { TokenType::LBrace, "{" };
    }

    if (c == '}') {
      m_in.get();
      return { TokenType::RBrace, "}" };
    }

    if (c == '"') return readQuoted();

    return readIdentifier();
  }

private:
  std::istream& m_in;

  void skipWhitespace() {
    while (m_in && std::isspace(m_in.peek())) {
      m_in.get();
    }
  }

  Token readQuoted() {
    m_in.get();
    std::string s;
    char c;

    while (m_in.get(c)) {
      if (c == '"')
        break;
      s += c;
    }

    return { TokenType::String, s };
  }

  Token readIdentifier() {
    std::string s;
    while (m_in && !std::isspace(m_in.peek()) && m_in.peek() != '{' && m_in.peek() != '}') {
      s += m_in.get();
    }
    if (s != "") {
      return { TokenType::Identifier, s };
    } else {
      return { TokenType::End, s };
    }
  }
};

static void parseNode(Tokenizer& tz, XDFNode& node) {
  for (;;) {
    Token t = tz.next();

    if (t.type == TokenType::RBrace || t.type == TokenType::End)
      return;

    if (t.type == TokenType::String) {
      // TODO: Make it so that it also supports identifers that are strings
      Token next = tz.next();

      if (next.type == TokenType::LBrace)

        std::cout << "Adding value: " << next.text << " to var: " << t.text << std::endl;
      node.addValue(t.text, next.text);
      continue;
    }

    if (t.type == TokenType::Identifier) {
      Token brace = tz.next();

      std::cout << "Going into identifier: " << t.text << std::endl;

      if (brace.type != TokenType::LBrace)
        throw std::runtime_error("Expected { after identifier");

      XDFNode child{t.text};
      parseNode(tz, child);
      node.append(std::move(child));
      continue;
    }

  }
}

}


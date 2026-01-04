#include <fstream>
#include <iostream>
#include <stdexcept>
#include <xdf/node.h>

#include <xdf/tokenizer.h>

#include <iostream>

#define INDENT std::string(indent * numSpaces, ' ')

namespace xdf {

XDFNode::XDFNode(const std::string& name) : m_name(name) {

}

void XDFNode::append(XDFNode node) {
  m_children.emplace(node.getName(), node);
}

void XDFNode::addValue(const std::string& name, const std::string& value) {
  m_values.emplace(name, value);
}


void XDFNode::writeToFile(std::ofstream& f, uint8_t& indent, const int numSpaces) {
  if (m_name != "" && m_name != "__root__") {
    if (m_name.find_first_of(" ") == std::string::npos) {
      f << "\n" << INDENT << m_name << " {";
    } else {
      throw std::runtime_error("Can't have identifier with spaces!");
      // f << "\n" << INDENT << '"' << m_name << '"' << " {";
    }
  } else {
    f << "{";
  }
  
  indent++;
  for (auto& it : m_values) {
    f << "\n" << INDENT << '"' << it.first << '"' << " " << '"' << it.second << '"';
  }

  if (m_children.size() > 0) {
    f << INDENT << "\n";
  } else {
    f << "\n";
  }

  for (auto& it : m_children) {
    it.second.writeToFile(f, indent, numSpaces);
  }
  // for (int i = 0; i < m_children.size(); i++) {
  // }
  indent--;

  f << INDENT << "}\n";
}

XDFRoot::XDFRoot() : XDFNode("__root__") {};

XDFRoot::XDFRoot(const std::string& name) : XDFNode(name) {}

void XDFRoot::write(const std::string& filename) {
  std::ofstream f;
  f.open(filename);

  uint8_t indent = 0;
  int numSpaces = 2;

  writeToFile(f, indent, numSpaces);

  f.close();
}

bool XDFRoot::read(const std::string& filename) {
  std::ifstream f;
  // std::ifstream testF;

  f.open(filename);
  // testF.open(filename);

  // Tokenizer testTz(testF);
  // Token t = testTz.next();

  // while (t.type != TokenType::End) {
  //   std::cout << "Type: " << GetTokenTypeName(t.type) << " | Text: " << '"' << t.text << '"' << std::endl;
  //
  //   t = testTz.next();
  // }
  //
  // testF.close();

  Tokenizer tz(f);

  Token first = tz.next();

  if (first.type == TokenType::LBrace) {
    std::cout << "No root name\n";

    parseNode(tz, *this);

    return true;
  }

  if (first.type == TokenType::Identifier || first.type == TokenType::String) {
    Token brace = tz.next();
    if (brace.type != TokenType::LBrace)
      return false;

    m_name = first.text;
    parseNode(tz, *this);

    return true;
  }

  return false;
}

}


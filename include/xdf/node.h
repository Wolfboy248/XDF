#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstdint>

namespace xdf {

class XDFNode {
public:
  XDFNode(const std::string& name);

  void append(XDFNode node);
  void addValue(const std::string& name, const std::string& value);

  std::string& getName() { return m_name; }
  std::map<std::string, XDFNode>& getChildren() { return m_children; }
  std::map<std::string, std::string>& getValues() { return m_values; }


  ~XDFNode() = default;

protected:
  void writeToFile(std::ofstream& f, uint8_t& indent, const int numSpaces);

  std::string m_name;
  std::map<std::string, std::string> m_values;
  std::map<std::string, XDFNode> m_children;

};

class XDFRoot : public XDFNode {
public:
  XDFRoot();
  XDFRoot(const std::string& name);

  void write(const std::string& filename);
  bool read(const std::string& filename);

private:

};

}


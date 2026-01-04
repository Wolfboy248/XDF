# XDF
XDF is a simple and versatile static C++ library for handling data with minimal overhead.
## Usage
The format requires you to have an XDFRoot object as the root, as that has the write function. The root does not require a name, however XDFNode does.
[^1]
```cpp
// node.h
class XDFRoot : public XDFNode {
public:
  ...

  void write(const std::string& filename);
  bool read(const std::string& filename);
};
```
Syntax could look something like this:
```cpp
XDFRoot root;
root.addValue("version", "0.1.0");

XDFNode child {"list"};
for (int i = 0; i < 20; i++) {
  XDFNode entry{std::to_string(i)};
  child.append(entry);
}

root.append(child);

root.write("file.xdf");

// root.read() returns true if the read was successful
if (root.read("file.xdf") {
  std::string version = root.getValues().find("version")->second;
  int listSize = root.getChildren().find("list")->second.getChildren().getSize();
}
```

[^1]: [include/xdf/node.h](https://github.com/Wolfboy248/XDF/blob/main/include/xdf/node.h)

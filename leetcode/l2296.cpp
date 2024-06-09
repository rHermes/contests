#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class TextEditor
{
  std::string m_left;
  std::string m_right;

public:
  void addText(const std::string& text) { m_left += text; }

  int deleteText(int k)
  {
    auto del = std::min(k, static_cast<int>(m_left.size()));
    m_left.resize(m_left.size() - del);
    return del;
  }

  std::string cursorLeft(int k)
  {
    for (int i = 0; i < k; i++) {
      if (m_left.empty())
        break;

      m_right.push_back(m_left.back());
      m_left.pop_back();
    }

    int pos = std::max(0, static_cast<int>(m_left.size()) - 10);
    return m_left.substr(pos);
  }

  std::string cursorRight(int k)
  {
    for (int i = 0; i < k; i++) {
      if (m_right.empty())
        break;

      m_left.push_back(m_right.back());
      m_right.pop_back();
    }

    int pos = std::max(0, static_cast<int>(m_left.size()) - 10);
    return m_left.substr(pos);
  }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */

/*
 * p1067 - Disk Tree
 *
 * So I could have done this in C, but the problem is just with the sorting.
 * C++ is going to be faster at this, so I'll just use their utilities.
 *
 * This could go faster, if I preallocate all the dirs. Otrebus has as usual
 * scored high on this too:
 *
 * https://github.com/Otrebus/timus/blob/master/1067.cpp
 */
#include <cstdio>
#include <cinttypes>
#include <map>
#include <list>
#include <tuple>

class Node {
private:
  std::map<std::string,Node> children_;

public:
  void print(int level) const {
    // First we print the indent that we need.

    // Now we print the name of the child and each of it's children
    for (const auto& child : children_) {
      // TODO(rHermes): This could really be optimized.
      for (int i = 0; i < level; i++) {
        printf(" ");
      }
      printf("%s\n", child.first.c_str());

      // we try to print for the child too.
      child.second.print(level+1);
    }
  }

  void addNode(std::list<std::string> paths) {
    // in C++17 I could have done the structured bindings but since we only have
    // C++14 we will make do with this.
    decltype(children_)::iterator iter;
    std::tie(iter, std::ignore) = children_.emplace(paths.front(), Node());
    paths.pop_front();

    if (!paths.empty()) {
      iter->second.addNode(paths);
    }
  }
};

int main() {
  Node root;

  int32_t N;
  scanf("%" SCNd32, &N);

  char buff[81];
  for (int32_t i = 0; i < N; i++) {
    scanf("%s\n", buff);

    std::string pth(buff);

    std::list<std::string> path_split;

    std::string delimiter = "\\";
    size_t pos = 0;
    std::string token;
    while ((pos = pth.find(delimiter)) != std::string::npos) {
      token = pth.substr(0, pos);
      path_split.push_back(std::move(token));
      pth.erase(0, pos + delimiter.length());
    }
    if (!pth.empty()) {
      path_split.push_back(std::move(pth));
    }

    root.addNode(path_split);
  }

  root.print(0);

	return 0;
}

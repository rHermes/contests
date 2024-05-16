#include <string>
#include <vector>

class Solution
{
public:
  static std::vector<std::string> fullJustify(const std::vector<std::string>& words, int maxWidth)
  {
    std::vector<std::string> lines;

    // The idea is to work on this line by line, as we are doing this as greedly as we can. There will
    // essentially be two steps. The first is to pick out the words that we can fit on this line.
    // then we have to distribute the spaces.
    //
    // Let's try to be smart about this.

    // We will optimize for speed here, so we will not be modifying the vector. Instead we will me moving
    // the strings out of it. This way, we are avoiding the pops from the front.
    auto front = words.begin();
    while (front != words.end()) {
      int currentWidth = front->size();

      auto cutOff = std::next(front);
      for (; cutOff != words.end(); cutOff++) {
        if (maxWidth < (currentWidth + static_cast<int>(cutOff->size()) + 1))
          break;

        currentWidth += cutOff->size() + 1;
      }

      // there are now 3 possibilities:
      // Either cutOff == words.end() and we are on the last line. -> just add spaces until we end.
      // The distance between front and cutOff == 1, which means there is only one word. We add spaces until the end.
      // We have an uneven amount of text.

      std::string currentLine(maxWidth, ' ');

      auto curIt = currentLine.begin();

      curIt = std::copy(front->begin(), front->end(), curIt);
      front++;

      if (cutOff == words.end() || front == cutOff) {
        for (; front != cutOff; front++) {
          curIt++;
          curIt = std::copy(front->begin(), front->end(), curIt);
        }
      } else {
        // This is the harder case. Now, we know how many elements we have.
        const auto numWords = std::distance(front, cutOff) + 1;

        // It's always more than 2. So the number of gaps is N-1
        const auto numberOfGaps = numWords - 1;

        // We know how much leftover space there is.
        const auto leftOverSpace = maxWidth - currentWidth;

        // Ok, so there are two scenarios here, either it lines up perfectly, or we
        // will have two halves.
        const auto average = leftOverSpace / numberOfGaps;
        const auto oneExtra = (leftOverSpace % numberOfGaps);

        for (int i = 0; i < oneExtra; i++) {
          curIt += average + 2;
          curIt = std::copy(front->begin(), front->end(), curIt);
          front++;
        }

        // Now for the rest of them we just apply the normal amount.
        for (; front != cutOff; front++) {
          curIt += average + 1;
          curIt = std::copy(front->begin(), front->end(), curIt);
        }
      }

      lines.emplace_back(std::move(currentLine));
    }

    return lines;
  }
};

int
main()
{
  return 0;
}

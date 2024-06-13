class Solution
{
public:
  static constexpr bool reachingPoints(int sx, int sy, int tx, int ty)
  {
    if (tx < sx || ty < sy)
      return false;

    while (sx <= tx && sy <= ty) {
      if (ty < tx)
        tx %= ty;
      else
        ty %= tx;
    }

    if (sx == tx && sy == ty)
      return true;
    else if (sx == tx) {
      return (ty < sy) && ((sy - ty) % tx == 0);
    } else if (sy == ty) {
      return (tx < sx) && ((sx - tx) % ty == 0);
    }

    return false;
  }
};

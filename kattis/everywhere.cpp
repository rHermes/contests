#include <unordered_set>
#include <cstdio>
#include <string>

int main(void) {
	char buffer[21];
	int cases;
	scanf("%d", &cases);
	for (int i = 0; i < cases; i++) {
		int lines;
		scanf("%d", &lines);
		std::unordered_set<std::string> seen;
		for (int j = 0; j < lines; j++) {
			scanf("%s", buffer);
			seen.insert(buffer);
		}
		printf("%ld\n", seen.size());
	}
	return 0;
}

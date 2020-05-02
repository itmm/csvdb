# Sorting rows

```
@Def(file: cd-sort.cpp)
	@put(globals);
	int main(
		int argc, const char *argv[]
	) {
		@put(main);
	}
@End(file: cd-sort.cpp)
```

```
@inc(ranges.md)
```

```
@inc(file.md)
```

```
@def(globals)
	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <string>
	#include <vector>
@end(globals)
```

```
@def(main)
	File in { std::cin };
	Ranges rngs { parse_ranges(
		in, argv + 1, argc - 1
	) };
@end(main)
```

```
@add(globals)
	void write_line(
		const Entries &entries
	) {
		bool first { true };
		for (int i { 1 }; i <= entries.columns(); ++i) {
			if (first) { 
				first = false;
			} else {
				std::cout << '\t';
			}
			std::cout << entries[i];
		}
		std::cout << '\n';
	}
@end(globals)
```

```
@add(globals)
	#include <algorithm>
@end(globals)
```

```
@add(main)
	write_line(in.header());
	std::vector<Entries> data;
	while (in.next_line()) {
		data.push_back(in.entries());
	}
	std::sort(data.begin(), data.end(), [&](const Entries &a, const Entries &b) -> bool {
		for (const auto &r : rngs) {
			for (int i { r.from() };
				i <= r.to() &&
					i <= in.columns();
				++i
			) {
				if (a[i] < b[i]) {
					return true;
				}
				if (a[i] > b[i]) {
					return false;
				}
			}
		}
		return false;
	});
	for (const Entries &e : data) {
		write_line(e);
	}
@end(main)
```


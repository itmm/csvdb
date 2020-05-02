# Projecting Columns

```
@Def(file: cd-cut.cpp)
	@put(globals);
	int main(
		int argc, const char *argv[]
	) {
		@put(main);
	}
@End(file: cd-cut.cpp)
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
		const File &f, const Ranges &rngs,
		const Entries &entries
	) {
		bool first { true };
		for (const auto &r : rngs) {
			for (int i { r.from() };
				i <= r.to() &&
					i <= entries.columns();
				++i
			) {
				if (first) { 
					first = false;
				} else {
					std::cout << '\t';
				}
				std::cout << entries[i];
			}
		}
		std::cout << '\n';
	}
@end(globals)
```

```
@add(main)
	write_line(in, rngs, in.header());
	while (in.next_line()) {
		write_line(in, rngs, in.entries());
	}
@end(main)
```


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
	Ranges rngs { parse_ranges(
		argv + 1, argc - 1
	) };
@end(main)
```

```
@add(globals)
	void write_line(
		const File &f, const Ranges &rngs,
		const std::string &(File::*fn)(int) const
	) {
		bool first { true };
		for (const auto &r : rngs) {
			for (int i { r.from() };
				i <= r.to() &&
					i <= f.columns();
				++i
			) {
				if (first) { 
					first = false;
				} else {
					std::cout << '\t';
				}
				std::cout << (f.*fn)(i);
			}
		}
		std::cout << '\n';
	}
@end(globals)
```

```
@add(main)
	File in { std::cin };
	write_line(in, rngs, &File::header);
	while (in.next_line()) {
		write_line(in, rngs, &File::entry);
	}
@end(main)
```


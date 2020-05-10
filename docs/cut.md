# Projecting Columns

```
@Def(file: ../src/csv-cut.cpp)
	@put(globals)
	int main(
		int argc, const char *argv[]
	) {
		@put(main)
	}
@End(file: ../src/csv-cut.cpp)
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
@add(main)
	in.header().write(rngs);
	while (in.next_line()) {
		in.entries().write(rngs);
	}
@end(main)
```


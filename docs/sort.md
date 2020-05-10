# Sorting rows

```
@Def(file: ../src/csv-sort.cpp)
	@put(globals)
	int main(
		int argc, const char *argv[]
	) {
		@put(main)
	}
@End(file: ../src/csv-sort.cpp)
```

```
@inc(ranges.md)
```

```
@inc(file.md)
```

```
@inc(cmp.md)
```

```
@def(globals)
	#include "libs/cmp.h"
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
	#include <algorithm>
@end(globals)
```

```
@add(main)
	in.header().write();
	std::vector<Entries> data;
	while (in.next_line()) {
		data.push_back(in.entries());
	}
	std::sort(data.begin(), data.end(),
		[&](
			const Entries &a,
			const Entries &b
		) -> bool {
			return compare(
				a, rngs, in.header(),
				b, rngs, in.header()
			) < 0;
		}
	);
	for (const Entries &e : data) {
		e.write();
	}
@end(main)
```


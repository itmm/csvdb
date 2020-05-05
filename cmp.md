# Comparing entries

```
@Def(file: libs/cmp.h)
	#pragma once
	@put(includes)
	@put(globals)
@End(file: libs/cmp.h)
```

```
@Def(file: libs/cmp.cpp)
	#define cmp_IMPL 1
	#include "cmp.h"
@End(file: libs/cmp.cpp)
```

```
@inc(entries.md)
```

```
@def(includes)
	#include "entries.h"
@end(includes)
```

```
@inc(ranges.md)
```

```
@add(includes)
	#include "ranges.h"
@end(includes)
```

```
@def(globals)
	int compare(
		const Entries &en1,
		const Ranges &rn1,
		const Entries &en2,
		const Ranges &rn2
	)
	#if cmp_IMPL
		{
			@put(compare);
		}
	#else
		;
	#endif
@end(globals)
```

```
@def(compare)
	auto r1 { rn1.begin() };
	int f1, t1;
	auto r2 { rn2.begin() };
	int f2, t2;
@end(compare)
```

```
@add(compare)
	if (r1 != rn1.end()) {
		f1 = r1->from();
		t1 = r1->to();
	}
	if (r2 != rn2.end()) {
		f2 = r2->from();
		t2 = r2->to();
	}
@end(compare)
```

```
@add(compare)
	while (
		r1 != rn1.end() &&
		r2 != rn2.end()
	) {
		@put(single compare);
	}
	return 0;
@end(compare)
```

```
@def(single compare)
	if (f1 > t1 || f1 > en1.columns()) {
		++r1;
		if (r1 != rn1.end()) {
			f1 = r1->from();
			t1 = r1->to();
		}
		continue;
	}
@end(single compare)
```

```
@add(single compare)
	if (f2 > t2 || f2 > en2.columns()) {
		++r2;
		if (r2 != rn2.end()) {
			f2 = r2->from();
			t2 = r2->to();
		}
		continue;
	}
@end(single compare)
```

```
@add(single compare)
	if (en1[f1] < en2[f2]) {
		return -1;
	}
	if (en1[f1] > en2[f2]) {
		return 1;
	}
@end(single compare)
```

```
@add(single compare)
	++f1; ++f2;
@end(single compare)
```


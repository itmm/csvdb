# Comparing entries

```
@Def(file: ../src/libs/cmp.h)
	#pragma once
	@put(includes)
	@put(globals)
@End(file: ../src/libs/cmp.h)
```

```
@Def(file: ../src/libs/cmp.cpp)
	#define cmp_IMPL 1
	#include "cmp.h"
@End(file: ../src/libs/cmp.cpp)
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
	@put(needed by compare)
	int compare(
		const Entries &en1,
		const Ranges &rn1,
		const Entries &header1,
		const Entries &en2,
		const Ranges &rn2,
		const Entries &header2
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
	int f1 { 1 }, t1 { 0 };
	auto r2 { rn2.begin() };
	int f2 { 2 }, t2 { 0 };
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
@def(needed by compare)
	#if cmp_IMPL
		static bool is_numeric(
			const std::string &hd
		) {
			return hd.size() && hd[hd.size() - 1] == '#';
		}
	#endif
@end(needed by compare)
```

```
@add(single compare)
	if (is_numeric(header1[f1]) && is_numeric(header2[f2])) {
		@put(numeric compare);
	} else {
		@put(string compare);
	}
@end(single compare)
```

```
@def(string compare)
	if (en1[f1] < en2[f2]) {
		return -1;
	}
	if (en1[f1] > en2[f2]) {
		return 1;
	}
@end(string compare)
```

```
@def(numeric compare)
	auto n1 { en1[f1] };
	auto n2 { en2[f2] };
	if (! n1.empty() && ! n2.empty()) {
		double d1 { std::stod(n1) };
		double d2 { std::stod(n2) };
		if (d1 < d2) {
			return -1;
		}
		if (d1 > d2) {
			return 1;
		}
	} else if (! n1.empty()) {
		return 1;
	} else if (! n2.empty()) {
		return -1;
	}
@end(numeric compare)
```

```
@add(single compare)
	++f1; ++f2;
@end(single compare)
```


# Handling files

```
@Def(file: libs/entries.cpp)
	#define entries_IMPL 1
	#include "entries.h"
@End(file: libs/entries.cpp)
```

```
@Def(file: libs/entries.h)
	#pragma once
	@put(includes);
	class Entries {
		private:
			@put(privates);
		public:
			@put(publics);
	};
	#if entries_IMPL
		@put(impl);
	#endif
@End(file: libs/entries.h)
```

```
@def(includes)
	#include <string>
@end(includes)
```

```
@def(publics)
	Entries() {}
	Entries(const std::string &line);
@end(publics)
```

```
@def(impl)
	Entries::Entries(
		const std::string &line
	) {
		@put(parse);
	}
@end(impl)
```

```
@add(includes)
	#include <vector>
@end(includes)
```

```
@def(privates)
	std::vector<std::string> entries_;
@end(privates)
```

```
@def(parse)
	size_t old { 0 };
	for (;;) {
		size_t pos { line.find(
			'\t', old
		) };
		if (pos == std::string::npos) {
			@put(push last entry);
			break;
		}
		@put(push entry);
		old = pos + 1;
	}
@end(parse)
```

```
@def(push last entry)
	entries_.push_back(
		line.substr(old)
	);
@end(push last entry)
```

```
@def(push entry)
	entries_.push_back(
		line.substr(old, pos - old)
	);
@end(push entry)
```

```
@add(privates)
	static std::string empty_;
@end(privates)
```

```
@add(impl)
	std::string Entries::empty_;
@end(impl)
```

```
@add(publics)
	const std::string &operator[](
		int i
	) const {
		@put(get);
		return empty_;
	}
@end(publics)
	
```

@def(get)
	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}
@end(get)
```

```
@add(publics)
	int columns() const {
		return entries_.size();
	}
@end(publics)
```


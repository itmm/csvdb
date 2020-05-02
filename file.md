# Handling files

```
@Def(file: libs/file.cpp)
	#define file_IMPL 1
	#include "file.h"
@End(file: libs/file.cpp)
```

```
@Def(file: libs/file.h)
	#pragma once
	@put(includes);
	class File {
		private:
			@put(privates);
		public:
			@put(publics);
	};
	#if file_IMPL
		@put(impl);
	#endif
@End(file: libs/file.h)
```

```
@def(publics)
	bool next_line();
@end(publics)
```

```
@def(impl)
	bool File::next_line() {
		@put(next line);
	}
@end(impl)
```

```
@def(includes)
	#include <string>
	#include <vector>
@end(includes)
```

```
@def(privates)
	using Entries =
		std::vector<std::string>;
	Entries header_;
	Entries entries_;
@end(privates)
```

```
@add(includes)
	#include <istream>
@end(includes)
```

```
@add(privates)
	std::istream &in_;
@end(privates)
@add(publics)
	File(std::istream &in): in_ { in } {
		if (next_line()) {
			header_ = entries_;
		}
	}
@end(publics)
```

```
@def(next line)
	std::string line;
	if (! std::getline(in_, line)) {
		return false;
	}
	entries_.clear();
	@put(fill entries);
	return true;
@end(next line)
```

```
@def(fill entries)
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
@end(fill entries)
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
	const std::string &get(
		int i, const Entries &entries
	) const {
		static std::string empty;
		@put(get);
		return empty;
	}
@end(privates)
```

```
@add(publics)
	const std::string &header(
		int i
	) const {
		return get(i, header_);
	}
@end(publics)
```

```
@add(publics)
	const std::string &entry(
		int i
	) const {
		return get(i, entries_);
	}
@end(publics)
```

```
@def(get)
	if (i > 0 && i <= static_cast<int>(
			entries.size()
	)) {
		return entries[i - 1];
	}
@end(get)
```

```
@add(publics)
	int columns() const {
		return header_.size();
	}
@end(publics)
```


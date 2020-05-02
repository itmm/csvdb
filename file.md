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
@inc(entries.md)
```

```
@def(includes)
	#include "entries.h"
@end(includes)
```

```
@def(privates)
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
@add(includes)
	#include <string>
@end(includes)
```

```
@def(next line)
	std::string line;
	if (! std::getline(in_, line)) {
		return false;
	}
	entries_ = Entries { line };
	return true;
@end(next line)
```

```
@add(publics)
	const Entries &header() const {
		return header_;
	}
@end(publics)
```

```
@add(publics)
	const Entries &entries() const {
		return entries_;
	}
@end(publics)
```

```
@add(publics)
	int columns() const {
		return header_.columns();
	}
@end(publics)
```


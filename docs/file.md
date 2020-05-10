# Handling files

```
@Def(file: ../src/libs/file.cpp)
	#define file_IMPL 1
	#include "file.h"
@End(file: ../src/libs/file.cpp)
```

```
@Def(file: ../src/libs/file.h)
	#pragma once
	@put(includes)
	class File {
		private:
			@put(privates)
		public:
			@put(publics)
	};
	#if file_IMPL
		@put(impl)
	#endif
@End(file: ../src/libs/file.h)
```

```
@def(publics)
	bool next_line();
@end(publics)
```

```
@def(impl)
	bool File::next_line() {
		@put(next line)
	}
@end(impl)
```

```
@inc(entries.md)
```

```
@def(includes)
	#include "entries.h"
	#include <iostream>
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
		} else {
			std::cerr << "no header found\n";
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
	return entries_.parse(in_);
@end(next line)
```

```
@add(publics)
	Entries &header() { return header_; }
	const Entries &header() const {
		return header_;
	}
@end(publics)
```

```
@add(publics)
	Entries &entries() { return entries_; }
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


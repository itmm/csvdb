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
	#include <vector>
	class Range;
	using Ranges = std::vector<Range>;
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
	#include <istream>
@end(includes)
```

```
@def(publics)
	bool parse(std::istream &in);
	void empty(int columns) {
		entries_.clear();
		for (int i { columns }; i; --i) {
			entries_.push_back("");
		}
	}

	static std::string escape(
		const std::string &value
	);
@end(publics)
```

```
@def(impl)
	bool Entries::parse(
		std::istream &in
	) {
		@put(parse);
	}
@end(impl)
```

```
@add(includes)
	#include <string>
	#include <vector>
	#include <iostream>
@end(includes)
```

```
@def(privates)
	std::vector<std::string> entries_;
@end(privates)
```

```
@def(parse)
	entries_.clear();
	std::string entry;
	int ch { in.get() };
	for (;;) {
		if (ch == EOF) {
			if (! entries_.empty() || ! entry.empty()) {
				std::cerr << "unexpected end of file\n";
			}
			entries_.push_back(entry);
			return false;
		}
		if (ch == ',') {
			entries_.push_back(entry);
			entry.clear();
			ch = in.get();
			continue;
		}
		if (ch == '\r') {
			entries_.push_back(entry);
			if (in.get() != '\n') {
				std::cerr << "no dos line ending\n";
				return false;
			}
			return true;
		}
		if (ch == '"') {
			ch = in.get();
			for (;;) {
				if (ch == EOF) {
					std::cerr << "end of file in quoted entry\n";
					entries_.push_back(entry);
					return false;
				}
				if (ch == '"') {
					ch = in.get();
					if (ch != '"') {
						break;
					}
				}
				entry += (char) ch;
				ch = in.get();
			}
			continue;
		}
		entry += (char) ch;
		ch = in.get();
	}
@end(parse)
```

```
@add(impl)
	std::string Entries::escape(const std::string &value) {
		bool needs_escape { false };
		for (char ch : value) {
			switch (ch) {
				case '"':
				case ',':
				case '\r':
				case '\n':
					needs_escape = true;
					break;
				default:
					break;
			}
			if (needs_escape) { break; }
		}
		if (! needs_escape) { return value; }
		std::string escaped;
		escaped += '"';
		for (char ch : value) {
			escaped += ch;
			if (ch == '"') {
				escaped += ch;
			}
		}
		escaped += '"';
		return escaped;
	}
@end(impl)
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

```
@add(publics)
	bool write(const Ranges &rngs, bool first = true, bool with_eol = true) const;
	bool write(bool first = true, bool with_eol = true) const;
@end(publics)
```

```
@add(impl)
	#include "ranges.h"
	bool Entries::write(const Ranges &rngs, bool first, bool with_eol) const {
		for (const auto &r : rngs) {
			int f { r.from() };
			for (; f <= r.to() && f <= columns(); ++f) {
				if (first) {
					first = false;
				} else {
					std::cout << ',';
				}
				std::cout << escape(entries_[f - 1]);
			}
		}
		if (with_eol) { std::cout << "\r\n"; }
		return first;
	}
	bool Entries::write(bool first, bool with_eol) const {
		Ranges rngs;
		rngs.push_back(Range {});
		return write(rngs, first, with_eol);
	}
@end(impl)
```

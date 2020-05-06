# Ranges

```
@Def(file: ../src/libs/ranges.cpp)
	#define ranges_IMPL 1
	#include "ranges.h"
@End(file: ../src/libs/ranges.cpp)
```

```
@inc(file.md)
```

```
@Def(file: ../src/libs/ranges.h)
	#pragma once

	#include "file.h"
	#include <limits>
	#include <vector>
	#include <string>

	class Range {
		private:
			int from_;
			int to_;
		public:
			Range(int from = 1, int to = std::numeric_limits<int>::max()):
				from_ { from }, to_ { to }
			{}
			int from() const { return from_; }
			int to() const { return to_; }
	};

	using Ranges = std::vector<Range>;

	#if ranges_IMPL
		static int to_index(const File &in, const std::string &n) {
			for (int i { 1 }; i <= in.columns(); ++i) {
				if (in.header()[i] == n) {
					return i;
				}
			}
			return std::stoi(n);
		}
	#endif

	Range parse_range(const File &in, std::string rng)
	#if ranges_IMPL
		{
			size_t sep { rng.find('-') };
			int from { 0 };
			int to { std::numeric_limits<int>::max() };
			if (sep == std::string::npos) {
				from = to = to_index(in, rng);
			} else {
				if (sep > 0) {
					from = to_index(in, rng.substr(0, sep));
				}
				if (sep + 1 < rng.size()) {
					to = to_index(in, rng.substr(sep + 1));
				}
			}
			return Range { from, to };
		}
	#else
		;
	#endif

	Ranges parse_ranges(const File &in, const char **args, int cnt)
	#if ranges_IMPL
		{
			Ranges rngs;
			for (; cnt; --cnt, ++args) {
				@put(parse arg);
			}
			if (! rngs.size()) {
				rngs.emplace_back();
			}
			return rngs;
		}
	#else
		;
	#endif
@End(file: ../src/libs/ranges.h)
```

```
@def(parse arg)
	std::string arg { *args };
	size_t old { 0 };
	for (;;) {
		size_t pos { arg.find(',', old) };
		if (pos == std::string::npos) {
			rngs.push_back(parse_range(in, arg.substr(old)));
			break;
		} else {
			rngs.push_back(parse_range(in, arg.substr(old, pos - old)));
			old = pos + 1;
		}
	}
@end(parse arg)
```

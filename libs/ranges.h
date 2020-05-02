
#line 11 "ranges.md"

	#pragma once

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

	Range parse_range(std::string rng)
	#if ranges_IMPL
		{
			size_t sep { rng.find('-') };
			int from { 0 };
			int to { std::numeric_limits<int>::max() };
			if (sep == std::string::npos) {
				from = to = std::stoi(rng);
			} else {
				if (sep > 0) {
					from = std::stoi(rng.substr(0, sep));
				}
				if (sep + 1 < rng.size()) {
					to = std::stoi(rng.substr(sep + 1));
				}
			}
			return Range { from, to };
		}
	#else
		;
	#endif

	Ranges parse_ranges(const char **args, int cnt)
	#if ranges_IMPL
		{
			Ranges rngs;
			for (; cnt; --cnt, ++args) {
				
#line 73 "ranges.md"

	std::string arg { *args };
	size_t old { 0 };
	for (;;) {
		size_t pos { arg.find(',', old) };
		if (pos == std::string::npos) {
			rngs.push_back(parse_range(arg.substr(old)));
			break;
		} else {
			rngs.push_back(parse_range(arg.substr(old, pos - old)));
			old = pos + 1;
		}
	}

#line 59 "ranges.md"
;
			}
			if (! rngs.size()) {
				rngs.emplace_back();
			}
			return rngs;
		}
	#else
		;
	#endif

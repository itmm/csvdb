
#line 11 "entries.md"

	#pragma once
	
#line 27 "entries.md"

	#include <string>

#line 50 "entries.md"

	#include <vector>

#line 13 "entries.md"
;
	class Entries {
		private:
			
#line 56 "entries.md"

	std::vector<std::string> entries_;

#line 95 "entries.md"

	static std::string empty_;

#line 16 "entries.md"
;
		public:
			
#line 33 "entries.md"

	Entries() {}
	Entries(const std::string &line);

#line 107 "entries.md"

	const std::string &operator[](
		int i
	) const {
		
#line 118 "entries.md"

	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}

#line 111 "entries.md"
;
		return empty_;
	}

#line 128 "entries.md"

	int columns() const {
		return entries_.size();
	}

#line 18 "entries.md"
;
	};
	#if entries_IMPL
		
#line 40 "entries.md"

	Entries::Entries(
		const std::string &line
	) {
		
#line 62 "entries.md"

	size_t old { 0 };
	for (;;) {
		size_t pos { line.find(
			'\t', old
		) };
		if (pos == std::string::npos) {
			
#line 79 "entries.md"

	entries_.push_back(
		line.substr(old)
	);

#line 69 "entries.md"
;
			break;
		}
		
#line 87 "entries.md"

	entries_.push_back(
		line.substr(old, pos - old)
	);

#line 72 "entries.md"
;
		old = pos + 1;
	}

#line 44 "entries.md"
;
	}

#line 101 "entries.md"

	std::string Entries::empty_;

#line 21 "entries.md"
;
	#endif


#line 11 "file.md"

	#pragma once
	
#line 41 "file.md"

	#include <string>
	#include <vector>

#line 57 "file.md"

	#include <istream>

#line 13 "file.md"
;
	class File {
		private:
			
#line 48 "file.md"

	using Entries =
		std::vector<std::string>;
	Entries header_;
	Entries entries_;

#line 63 "file.md"

	std::istream &in_;

#line 121 "file.md"

	const std::string &get(
		int i, const Entries &entries
	) const {
		static std::string empty;
		
#line 153 "file.md"

	if (i > 0 && i <= static_cast<int>(
			entries.size()
	)) {
		return entries[i - 1];
	}

#line 126 "file.md"
;
		return empty;
	}

#line 16 "file.md"
;
		public:
			
#line 27 "file.md"

	bool next_line();

#line 66 "file.md"

	File(std::istream &in): in_ { in } {
		if (next_line()) {
			header_ = entries_;
		}
	}

#line 133 "file.md"

	const std::string &header(
		int i
	) const {
		return get(i, header_);
	}

#line 143 "file.md"

	const std::string &entry(
		int i
	) const {
		return get(i, entries_);
	}

#line 163 "file.md"

	int columns() const {
		return header_.size();
	}

#line 18 "file.md"
;
	};
	#if file_IMPL
		
#line 33 "file.md"

	bool File::next_line() {
		
#line 76 "file.md"

	std::string line;
	if (! std::getline(in_, line)) {
		return false;
	}
	entries_.clear();
	
#line 88 "file.md"

	size_t old { 0 };
	for (;;) {
		size_t pos { line.find(
			'\t', old
		) };
		if (pos == std::string::npos) {
			
#line 105 "file.md"

	entries_.push_back(
		line.substr(old)
	);

#line 95 "file.md"
;
			break;
		}
		
#line 113 "file.md"

	entries_.push_back(
		line.substr(old, pos - old)
	);

#line 98 "file.md"
;
		old = pos + 1;
	}

#line 82 "file.md"
;
	return true;

#line 35 "file.md"
;
	}

#line 21 "file.md"
;
	#endif

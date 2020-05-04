
#line 11 "entries.md"

	#pragma once
	
#line 27 "entries.md"

	#include <istream>

#line 51 "entries.md"

	#include <string>
	#include <vector>

#line 13 "entries.md"
;
	class Entries {
		private:
			
#line 58 "entries.md"

	std::vector<std::string> entries_;

#line 134 "entries.md"

	static std::string empty_;

#line 16 "entries.md"
;
		public:
			
#line 33 "entries.md"

	Entries() {}
	bool parse(std::istream &in);
	static std::string escape(const std::string &value);

#line 146 "entries.md"

	const std::string &operator[](
		int i
	) const {
		
#line 157 "entries.md"

	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}

#line 150 "entries.md"
;
		return empty_;
	}

#line 167 "entries.md"

	int columns() const {
		return entries_.size();
	}

#line 18 "entries.md"
;
	};
	#if entries_IMPL
		
#line 41 "entries.md"

	bool Entries::parse(
		std::istream &in
	) {
		
#line 64 "entries.md"

	entries_.clear();
	std::string entry;
	int ch { in.get() };
	for (;;) {
		if (ch == EOF) { return false; }
		if (ch == ',') {
			entries_.push_back(entry);
			entry.clear();
			ch = in.get();
			continue;
		}
		if (ch == '\r') {
			entries_.push_back(entry);
			return in.get() == '\n';
		}
		if (ch == '"') {
			ch = in.get();
			for (;;) {
				if (ch == EOF) { return false; }
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

#line 45 "entries.md"
;
	}

#line 102 "entries.md"

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

#line 140 "entries.md"

	std::string Entries::empty_;

#line 21 "entries.md"
;
	#endif


#line 11 "entries.md"

	#pragma once
	
#line 27 "entries.md"

	#include <istream>

#line 59 "entries.md"

	#include <string>
	#include <vector>
	#include <iostream>

#line 13 "entries.md"
;
	class Entries {
		private:
			
#line 67 "entries.md"

	std::vector<std::string> entries_;

#line 157 "entries.md"

	static std::string empty_;

#line 16 "entries.md"
;
		public:
			
#line 33 "entries.md"

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

#line 169 "entries.md"

	const std::string &operator[](
		int i
	) const {
		
#line 180 "entries.md"

	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}

#line 173 "entries.md"
;
		return empty_;
	}

#line 190 "entries.md"

	int columns() const {
		return entries_.size();
	}

#line 18 "entries.md"
;
	};
	#if entries_IMPL
		
#line 49 "entries.md"

	bool Entries::parse(
		std::istream &in
	) {
		
#line 73 "entries.md"

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

#line 53 "entries.md"
;
	}

#line 125 "entries.md"

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

#line 163 "entries.md"

	std::string Entries::empty_;

#line 21 "entries.md"
;
	#endif

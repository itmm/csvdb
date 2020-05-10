
#line 11 "entries.md"

	#pragma once
	
#line 30 "entries.md"

	#include <istream>

#line 62 "entries.md"

	#include <string>
	#include <vector>
	#include <iostream>

#line 13 "entries.md"

	#include <vector>
	class Range;
	using Ranges = std::vector<Range>;
	class Entries {
		private:
			
#line 70 "entries.md"

	std::vector<std::string> entries_;

#line 160 "entries.md"

	static std::string empty_;

#line 19 "entries.md"

		public:
			
#line 36 "entries.md"

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

#line 172 "entries.md"

	const std::string &operator[](
		int i
	) const {
		
#line 195 "entries.md"

	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}

#line 176 "entries.md"

		return empty_;
	}

#line 183 "entries.md"

	std::string &operator[](
		int i
	) {
		
#line 195 "entries.md"

	if (i > 0 && i <= static_cast<int>(
			entries_.size()
	)) {
		return entries_[i - 1];
	}

#line 187 "entries.md"

		std::cerr << "out of bounds write\n";
		std::exit(EXIT_FAILURE);
	}

#line 205 "entries.md"

	int columns() const {
		return entries_.size();
	}

#line 213 "entries.md"

	bool write(const Ranges &rngs, bool first = true, bool with_eol = true) const;
	bool write(bool first = true, bool with_eol = true) const;

#line 21 "entries.md"

	};
	#if entries_IMPL
		
#line 52 "entries.md"

	bool Entries::parse(
		std::istream &in
	) {
		
#line 76 "entries.md"

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

#line 56 "entries.md"

	}

#line 128 "entries.md"

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

#line 166 "entries.md"

	std::string Entries::empty_;

#line 220 "entries.md"

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

#line 24 "entries.md"

	#endif

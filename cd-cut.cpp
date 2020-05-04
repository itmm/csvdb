
#line 4 "cut.md"

	
#line 23 "cut.md"

	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <string>

#line 41 "cut.md"

	void write_line(
		const File &f, const Ranges &rngs,
		const Entries &entries
	) {
		bool first { true };
		for (const auto &r : rngs) {
			if (r.from() > entries.columns()) {
				std::cerr << "not enough columns in data\n";
			}
			for (int i { r.from() };
				i <= r.to() &&
					i <= entries.columns();
				++i
			) {
				if (first) { 
					first = false;
				} else {
					std::cout << ',';
				}
				std::cout << Entries::escape(entries[i]);
			}
		}
		std::cout << "\r\n";
	}

#line 5 "cut.md"
;
	int main(
		int argc, const char *argv[]
	) {
		
#line 32 "cut.md"

	File in { std::cin };
	Ranges rngs { parse_ranges(
		in, argv + 1, argc - 1
	) };

#line 70 "cut.md"

	write_line(in, rngs, in.header());
	while (in.next_line()) {
		write_line(in, rngs, in.entries());
	}

#line 9 "cut.md"
;
	}


#line 4 "cut.md"

	
#line 23 "cut.md"

	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <string>

#line 41 "cut.md"

	void write_line(
		const File &f, const Ranges &rngs,
		const std::string &(File::*fn)(int) const
	) {
		bool first { true };
		for (const auto &r : rngs) {
			for (int i { r.from() };
				i <= r.to() &&
					i <= f.columns();
				++i
			) {
				if (first) { 
					first = false;
				} else {
					std::cout << '\t';
				}
				std::cout << (f.*fn)(i);
			}
		}
		std::cout << '\n';
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

#line 67 "cut.md"

	write_line(in, rngs, &File::header);
	while (in.next_line()) {
		write_line(in, rngs, &File::entry);
	}

#line 9 "cut.md"
;
	}

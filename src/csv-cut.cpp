
#line 4 "cut.md"

	
#line 23 "cut.md"

	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>

#line 5 "cut.md"

	int main(
		int argc, const char *argv[]
	) {
		
#line 31 "cut.md"

	File in { std::cin };
	Ranges rngs { parse_ranges(
		in, argv + 1, argc - 1
	) };

#line 40 "cut.md"

	in.header().write(rngs);
	while (in.next_line()) {
		in.entries().write(rngs);
	}

#line 9 "cut.md"

	}

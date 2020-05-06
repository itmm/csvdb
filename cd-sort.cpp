
#line 4 "sort.md"

	
#line 27 "sort.md"

	#include "libs/cmp.h"
	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <string>
	#include <vector>

#line 47 "sort.md"

	#include <algorithm>

#line 5 "sort.md"
;
	int main(
		int argc, const char *argv[]
	) {
		
#line 38 "sort.md"

	File in { std::cin };
	Ranges rngs { parse_ranges(
		in, argv + 1, argc - 1
	) };

#line 53 "sort.md"

	in.header().write();
	std::vector<Entries> data;
	while (in.next_line()) {
		data.push_back(in.entries());
	}
	std::sort(data.begin(), data.end(),
		[&](
			const Entries &a,
			const Entries &b
		) -> bool {
			return compare(
				a, rngs, in.header(),
				b, rngs, in.header()
			) < 0;
		}
	);
	for (const Entries &e : data) {
		e.write();
	}

#line 9 "sort.md"
;
	}

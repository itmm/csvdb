
#line 4 "sort.md"

	
#line 23 "sort.md"

	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <string>
	#include <vector>

#line 42 "sort.md"

	void write_line(
		const Entries &entries
	) {
		bool first { true };
		for (int i { 1 }; i <= entries.columns(); ++i) {
			if (first) { 
				first = false;
			} else {
				std::cout << ',';
			}
			std::cout << Entries::escape(entries[i]);
		}
		std::cout << "\r\n";
	}

#line 61 "sort.md"

	#include <algorithm>

#line 5 "sort.md"
;
	int main(
		int argc, const char *argv[]
	) {
		
#line 33 "sort.md"

	File in { std::cin };
	Ranges rngs { parse_ranges(
		in, argv + 1, argc - 1
	) };

#line 67 "sort.md"

	write_line(in.header());
	std::vector<Entries> data;
	while (in.next_line()) {
		data.push_back(in.entries());
	}
	std::sort(data.begin(), data.end(), [&](const Entries &a, const Entries &b) -> bool {
		for (const auto &r : rngs) {
			for (int i { r.from() };
				i <= r.to() &&
					i <= in.columns();
				++i
			) {
				if (a[i] < b[i]) {
					return true;
				}
				if (a[i] > b[i]) {
					return false;
				}
			}
		}
		return false;
	});
	for (const Entries &e : data) {
		write_line(e);
	}

#line 9 "sort.md"
;
	}

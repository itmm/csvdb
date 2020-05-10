
#line 4 "replace.md"

	
#line 23 "replace.md"

	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <iostream>
	#include <fstream>

#line 32 "replace.md"

	std::string to {};
	std::string from {};
	const char *rngs { nullptr };

#line 55 "replace.md"

	static bool process(const std::string &name, Ranges &rs, bool first) {
		std::ifstream inf;
		bool from_stdin { name == "-" };
		if (! from_stdin) {
			inf.open(name.c_str());
			if (! inf) {
				std::cerr << "can't open " << name << "\n";
				return false;
			}
		}
		File in { from_stdin ? std::cin : inf};
		if (first) {
			in.header().write();
			if (rngs) {
				rs = parse_ranges(in, &rngs, 1);
			} else {
				rs.emplace_back();
			}
		}
		while (in.next_line()) {
			for (const auto &r : rs) {
				for(int cur { r.from() }; cur <= in.columns() && cur <= r.to(); ++cur) {
					if (in.entries()[cur] == from) {
						in.entries()[cur] = to;
					}
				}
			}
			in.entries().write();
		}
		return false;
	}

#line 5 "replace.md"

	int main(
		int argc, const char *argv[]
	) {
		
#line 40 "replace.md"

	--argc; ++argv;
	if (argc) {
		to = *argv++; --argc;
	}
	if (argc) {
		from = *argv++; --argc;
	}
	if (argc) {
		rngs = *argv++; --argc;
	}

#line 91 "replace.md"

	if (argc) {
		Ranges rs;
		bool first { true };
		for (; argc; --argc, ++argv) {
			first = process(*argv, rs, first);
		}
	} else {
		Ranges rs;
		process("-", rs, true);
	}

#line 9 "replace.md"

	}

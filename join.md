# Joining tables

```
@Def(file: cd-join.cpp)
	@put(globals);
	int main(
		int argc, const char *argv[]
	) {
		@put(main);
	}
@End(file: cd-join.cpp)
```

```
@inc(ranges.md)
```

```
@inc(file.md)
```

```
@def(globals)
	#include "libs/file.h"
	#include "libs/ranges.h"
	#include <fstream>
	#include <iostream>
	#include <string>
@end(globals)
```

```
@def(main)
	if (argc != 5) {
		std::cerr << "wrong number of arguments\n";
		std::exit(EXIT_FAILURE);
	}
	std::ifstream file1 { argv[1] };
	std::ifstream file2 { argv[2] };
	File in1 { file1 };
	File in2 { file2 };
	Ranges rngs1 { parse_ranges(
		in1, argv + 3, 1
	) };
	Ranges rngs2 { parse_ranges(
		in2, argv + 4, 1
	) };
@end(main)
```

```
@add(globals)
	void write_line(
		const Entries &entries1,
		const Entries &entries2
	) {
		bool first { true };
		for (int i { 1 }; i <= entries1.columns(); ++i) {
			if (first) { 
				first = false;
			} else {
				std::cout << ',';
			}
			std::cout << Entries::escape(entries1[i]);
		}
		for (int i { 1 }; i <= entries2.columns(); ++i) {
			if (first) { 
				first = false;
			} else {
				std::cout << ',';
			}
			std::cout << Entries::escape(entries2[i]);
		}
		std::cout << "\r\n";
	}
@end(globals)
```

```
@add(main)
	write_line(in1.header(), in2.header());
	bool has1 { in1.next_line() };
	bool has2 { in2.next_line() };
	Entries empty1; empty1.empty(in1.columns());
	Entries empty2; empty2.empty(in2.columns());
	while (has1 && has2) {
		int sort { 0 };
		auto rng1 { rngs1.begin() };
		auto rng2 { rngs2.begin() };
		if (rng1 != rngs1.end() && rng2 != rngs2.end()) {
			int from1 { rng1->from() };
			int to1 { rng1->to() };
			int from2 { rng2->from() };
			int to2 { rng2->to() };
			while (rng1 != rngs1.end() && rng2 != rngs2.end()) {
				if (from1 > to1 || from1 > empty1.columns()) {
					++rng1;
					if (rng1 != rngs1.end()) {
						from1 = rng1->from();
						to1 = rng1->to();
					}
					continue;
				}
				if (from2 > to2 || from2 > empty2.columns()) {
					++rng2;
					if (rng2 != rngs2.end()) {
						from2 = rng2->from();
						to2 = rng2->to();
					}
					continue;
				}
				if (in1.entries()[from1] < in2.entries()[from2]) {
					sort = -1;
					break;
				}
				if (in1.entries()[from1] > in2.entries()[from2]) {
					sort = 1;
					break;
				}
				++from1;
				++from2;
			}
		}
		if (sort < 0) {
			write_line(in1.entries(), empty2);
			has1 = in1.next_line();
		} else if (sort > 0) {
			write_line(empty1, in2.entries());
			has2 = in2.next_line();
		} else {
			write_line(in1.entries(), in2.entries());
			has1 = in1.next_line();
			has2 = in2.next_line();
		}
	}
	while (has1) {
		write_line(in1.entries(), empty2);
		has1 = in1.next_line();
	}
	while (has2) {
		write_line(empty1, in2.entries());
		has2 = in2.next_line();
	}
@end(main)
```


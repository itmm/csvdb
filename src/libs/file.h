
#line 11 "file.md"

	#pragma once
	
#line 45 "file.md"

	#include "entries.h"
	#include <iostream>

#line 59 "file.md"

	#include <istream>

#line 80 "file.md"

	#include <string>

#line 13 "file.md"

	class File {
		private:
			
#line 52 "file.md"

	Entries header_;
	Entries entries_;

#line 65 "file.md"

	std::istream &in_;

#line 16 "file.md"

		public:
			
#line 27 "file.md"

	bool next_line();

#line 68 "file.md"

	File(std::istream &in): in_ { in } {
		if (next_line()) {
			header_ = entries_;
		} else {
			std::cerr << "no header found\n";
		}
	}

#line 92 "file.md"

	Entries &header() { return header_; }
	const Entries &header() const {
		return header_;
	}

#line 101 "file.md"

	Entries &entries() { return entries_; }
	const Entries &entries() const {
		return entries_;
	}

#line 110 "file.md"

	int columns() const {
		return header_.columns();
	}

#line 18 "file.md"

	};
	#if file_IMPL
		
#line 33 "file.md"

	bool File::next_line() {
		
#line 86 "file.md"

	return entries_.parse(in_);

#line 35 "file.md"

	}

#line 21 "file.md"

	#endif

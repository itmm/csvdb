
#line 11 "file.md"

	#pragma once
	
#line 45 "file.md"

	#include "entries.h"

#line 58 "file.md"

	#include <istream>

#line 77 "file.md"

	#include <string>

#line 13 "file.md"
;
	class File {
		private:
			
#line 51 "file.md"

	Entries header_;
	Entries entries_;

#line 64 "file.md"

	std::istream &in_;

#line 16 "file.md"
;
		public:
			
#line 27 "file.md"

	bool next_line();

#line 67 "file.md"

	File(std::istream &in): in_ { in } {
		if (next_line()) {
			header_ = entries_;
		}
	}

#line 89 "file.md"

	const Entries &header() const {
		return header_;
	}

#line 97 "file.md"

	const Entries &entries() const {
		return entries_;
	}

#line 105 "file.md"

	int columns() const {
		return header_.columns();
	}

#line 18 "file.md"
;
	};
	#if file_IMPL
		
#line 33 "file.md"

	bool File::next_line() {
		
#line 83 "file.md"

	return entries_.parse(in_);

#line 35 "file.md"
;
	}

#line 21 "file.md"
;
	#endif

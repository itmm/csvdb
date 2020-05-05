
#line 4 "cmp.md"

	#pragma once
	
#line 23 "cmp.md"

	#include "entries.h"

#line 33 "cmp.md"

	#include "ranges.h"

#line 6 "cmp.md"

	
#line 39 "cmp.md"

	int compare(
		const Entries &en1,
		const Ranges &rn1,
		const Entries &en2,
		const Ranges &rn2
	)
	#if cmp_IMPL
		{
			
#line 57 "cmp.md"

	auto r1 { rn1.begin() };
	int f1, t1;
	auto r2 { rn2.begin() };
	int f2, t2;

#line 66 "cmp.md"

	if (r1 != rn1.end()) {
		f1 = r1->from();
		t1 = r1->to();
	}
	if (r2 != rn2.end()) {
		f2 = r2->from();
		t2 = r2->to();
	}

#line 79 "cmp.md"

	while (
		r1 != rn1.end() &&
		r2 != rn2.end()
	) {
		
#line 91 "cmp.md"

	if (f1 > t1 || f1 > en1.columns()) {
		++r1;
		if (r1 != rn1.end()) {
			f1 = r1->from();
			t1 = r1->to();
		}
		continue;
	}

#line 104 "cmp.md"

	if (f2 > t2 || f2 > en2.columns()) {
		++r2;
		if (r2 != rn2.end()) {
			f2 = r2->from();
			t2 = r2->to();
		}
		continue;
	}

#line 117 "cmp.md"

	if (en1[f1] < en2[f2]) {
		return -1;
	}
	if (en1[f1] > en2[f2]) {
		return 1;
	}

#line 128 "cmp.md"

	++f1; ++f2;

#line 84 "cmp.md"
;
	}
	return 0;

#line 48 "cmp.md"
;
		}
	#else
		;
	#endif

#line 7 "cmp.md"



#line 4 "cmp.md"

	#pragma once
	
#line 23 "cmp.md"

	#include "entries.h"

#line 33 "cmp.md"

	#include "ranges.h"

#line 6 "cmp.md"

	
#line 39 "cmp.md"

	
#line 120 "cmp.md"

	#if cmp_IMPL
		static bool is_numeric(
			const std::string &hd
		) {
			return hd.size() && hd[hd.size() - 1] == '#';
		}
	#endif

#line 40 "cmp.md"

	int compare(
		const Entries &en1,
		const Ranges &rn1,
		const Entries &header1,
		const Entries &en2,
		const Ranges &rn2,
		const Entries &header2
	)
	#if cmp_IMPL
		{
			
#line 60 "cmp.md"

	auto r1 { rn1.begin() };
	int f1, t1;
	auto r2 { rn2.begin() };
	int f2, t2;

#line 69 "cmp.md"

	if (r1 != rn1.end()) {
		f1 = r1->from();
		t1 = r1->to();
	}
	if (r2 != rn2.end()) {
		f2 = r2->from();
		t2 = r2->to();
	}

#line 82 "cmp.md"

	while (
		r1 != rn1.end() &&
		r2 != rn2.end()
	) {
		
#line 94 "cmp.md"

	if (f1 > t1 || f1 > en1.columns()) {
		++r1;
		if (r1 != rn1.end()) {
			f1 = r1->from();
			t1 = r1->to();
		}
		continue;
	}

#line 107 "cmp.md"

	if (f2 > t2 || f2 > en2.columns()) {
		++r2;
		if (r2 != rn2.end()) {
			f2 = r2->from();
			t2 = r2->to();
		}
		continue;
	}

#line 132 "cmp.md"

	if (is_numeric(header1[f1]) && is_numeric(header2[f2])) {
		
#line 153 "cmp.md"

	auto n1 { en1[f1] };
	auto n2 { en2[f2] };
	if (! n1.empty() && ! n2.empty()) {
		double d1 { std::stod(n1) };
		double d2 { std::stod(n2) };
		if (d1 < d2) {
			return -1;
		}
		if (d1 > d2) {
			return 1;
		}
	} else if (! n1.empty()) {
		return 1;
	} else if (! n2.empty()) {
		return -1;
	}

#line 134 "cmp.md"
;
	} else {
		
#line 142 "cmp.md"

	if (en1[f1] < en2[f2]) {
		return -1;
	}
	if (en1[f1] > en2[f2]) {
		return 1;
	}

#line 136 "cmp.md"
;
	}

#line 174 "cmp.md"

	++f1; ++f2;

#line 87 "cmp.md"
;
	}
	return 0;

#line 51 "cmp.md"
;
		}
	#else
		;
	#endif

#line 7 "cmp.md"


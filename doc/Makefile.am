docdir = $(datadir)/doc/@PACKAGE@
doc_DATA = add.html \
	add.md \
	cmp.html \
	cmp.md \
	cut.html \
	cut.md \
	entries.html \
	entries.md \
	file.html \
	file.md \
	hx_run \
	index.html \
	index.md \
	join.html \
	join.md \
	ranges.html \
	ranges.md \
	slides/bg.svg \
	slides/slides.css \
	sort.html \
	sort.md \
	TODOs.md

hx_run: add.md \
	cmp.md \
	cut.md \
	entries.md \
	file.md \
	index.md \
	join.md \
	ranges.md \
	sort.md
	cd $(srcdir) && hx
	date >$(srcdir)/$@


MDs=$(shell hx-srcs.sh)
FILEs=$(shell hx-files.sh $(MDs))
CPPs=$(filter %.cpp, $(FILEs))
Hs=$(filter %.h,$(FILEs))
OBJSRCs=$(filter libs/%,$(CPPs))
OBJs=$(OBJSRCs:.cpp=.o)
APPSRCs=$(filter-out libs/%,$(CPPs))
APPs=$(APPSRCs:.cpp=)
CXXFLAGS+=-Wall -std=c++17

.PHONY: clean all

all: hx-run

define MAKE_APP
$(1): $(1).cpp $$(OBJs) $$(Hs)
	@echo "C++ $$@"
	@$$(CXX) $$(CXXFLAGS) $(1).cpp $$(OBJs) -o $$@
endef

$(foreach i,$(APPs),$(eval $(call MAKE_APP,$(i))))

hx-run: $(MDs)
	@echo "HX"
	@hx
	@date >$@
	@make --no-print-directory $(APPs)

libs/%.o: libs/%.cpp $(Hs)
	@echo "C++ $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	@echo "RM"
	@rm -f $(APPs) $(OBJs) $(CPPs) hx-run


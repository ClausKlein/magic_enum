# Standard stuff

.SUFFIXES:

MAKEFLAGS+= --no-builtin-rules          # Disable the built-in implicit rules.
MAKEFLAGS+= --no-builtin-variables      # Disable the built-in variable settings.
MAKEFLAGS+= --warn-undefined-variables  # Warn when an undefined variable is referenced.

ifeq ($(origin CXX),default)
  export CC:=gcc-16
  export CXX:=g++-16
  export CXXFLAGS:=-stdlib=libstdc++
endif

.PHONY: all test check clean format find-package-test

all: build ## Build all
	ninja -C build all # TODO: all_verify_interface_header_sets

build: GNUmakefile CMakeLists.txt ## Configure with cmake
	cmake --version # NOTE: v4.5 expected! CK
	cmake -G Ninja -S . -B build --fresh \
	  -D CMAKE_SKIP_TEST_ALL_DEPENDENCY=NO -Wdeprecated -Wauthor -D MAGIC_ENUM_MODULE_WITH_FMT=ON \
	  -D MAGIC_ENUM_MODULE_IMPORT_STD=OFF -D MAGIC_ENUM_USE_MODULES=ON -D CMAKE_CXX_STANDARD=20 \
	  --debug-find-pkg=FMT --fresh
	ln -fs build/compile_commands.json .

find-package-test: install ## Test installed module
	cmake -G Ninja -S test/installed_module -B build/find-package-build -D MAGIC_ENUM_EXPECT_FMT=ON --fresh \
	  -D MAGIC_ENUM_EXPECT_IMPORT_STD=OFF -D CMAKE_CXX_STANDARD=20
	ninja -C build/find-package-build -v
	ninja -C build/find-package-build -t deps CMakeFiles/magic_enum_installed_module_test.dir/main.cpp.o | egrep -w '(fmt|magic_enum)'
	./build/find-package-build/magic_enum_installed_module_test

clean: ## Remove build directory
	rm -rf build

distclean: clean ## Remove all build arthefacts
	rm -rf stagedir .cache .init CMakeUserPresets.json compile_commands.json tags *.bak .*~
	find . -name '*~' -delete

# Helper targets
.PHONY: env info

env: ## Show env
	$(foreach v, $(.VARIABLES), $(info $(v) = $($(v))))

info: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[.a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

test: build ## Run ctest
	ninja -C build $(@)

# Anything we don't know how to build will use this rule.
% ::
	ninja -C build $(@)

cmake_policy(VERSION 3.24)

macro(fmt_provide_dependency method)
    # we use a shared $CPM_SOURCE_CACHE
    include(cmake/CPM.cmake)

    cpmaddpackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 12.2.1
        VERSION 12.2.1
        OPTIONS FMT_INSTALL
    )
endmacro()

# Accepts find_package() only
cmake_language(
    SET_DEPENDENCY_PROVIDER fmt_provide_dependency
    SUPPORTED_METHODS FIND_PACKAGE
)

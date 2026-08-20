include(FetchContent)
  FetchContent_Declare(
    doxygen-awesome-css
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css
    GIT_TAG d52eafe3e9303399fda15661f3d7bb8fe3d7eabc # v2.4.2
)
FetchContent_MakeAvailable(doxygen-awesome-css)
# Save the location the files were cloned into
# This allows us to get the path to doxygen-awesome.css
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)


set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
set(DOXYGEN_REPEAT_BRIEF NO)
set(DOXYGEN_SHOW_FILES NO)
set(DOXYGEN_SORT_MEMBER_DOCS NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_HTML_EXTRA_STYLESHEET "${AWESOME_CSS_DIR}/doxygen-awesome.css" "${AWESOME_CSS_DIR}/doxygen-awesome-sidebar-only.css")
doxygen_add_docs(docs "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/libalgea/include")

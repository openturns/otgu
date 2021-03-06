

ot_add_current_dir_to_include_dirs ()

ot_add_source_file ( KrigingAlgorithm.cxx )
ot_add_source_file ( GeneralLinearModelAlgorithm.cxx )
ot_add_source_file ( GeneralLinearModelResult.cxx )

ot_install_header_file ( KrigingAlgorithm.hxx )
ot_install_header_file ( GeneralLinearModelAlgorithm.hxx )
ot_install_header_file ( GeneralLinearModelResult.hxx )


include_directories (${INTERNAL_INCLUDE_DIRS})

add_library (otgu ${SOURCEFILES})
set_target_properties (otgu PROPERTIES POSITION_INDEPENDENT_CODE ON)
if (BUILD_SHARED_LIBS)
  set_target_properties (otgu PROPERTIES COMPILE_DEFINITIONS "OTGU_DLL_EXPORTS")
endif ()

if ( NOT DEFINED LIB_VERSION ) 
  set ( LIB_VERSION 0.0.0 )
endif ()
if ( NOT DEFINED LIB_SOVERSION ) 
  set ( LIB_SOVERSION 0 )
endif ()
set_target_properties ( otgu PROPERTIES VERSION ${LIB_VERSION} )
set_target_properties ( otgu PROPERTIES SOVERSION ${LIB_SOVERSION} )
target_link_libraries (otgu ${OPENTURNS_LIBRARY})

# Add targets to the build-tree export set
export (TARGETS otgu FILE ${PROJECT_BINARY_DIR}/OTGU-Targets.cmake)

# Install the export set for use with the install-tree
install(EXPORT OTGU-Targets
        DESTINATION "${OTGU_CONFIG_CMAKE_PATH}"
        COMPONENT Development)

install(TARGETS otgu
        EXPORT  OTGU-Targets 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${OTGU_LIBRARY_PATH}
        ARCHIVE DESTINATION ${OTGU_LIBRARY_PATH}
)


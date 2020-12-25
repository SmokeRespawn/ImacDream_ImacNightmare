#
# Find SDL_MIXER
#

# Additional modules
include(FindPackageHandleStandardArgs)

# Find include files
find_path(
  SDL_MIXER_INCLUDE_DIR
  PATHS
  /usr/include
  /usr/local/include
  /sw/include
  /opt/local/include
  ${SDL_MIXER_ROOT_DIR}/include
  DOC "The directory where SDL_mixer.h resides")

# Handle REQUIRD argument, define *_FOUND variable
#find_package_handle_standard_args(SDL_MIXER_INCLUDE_DIR)

# Hide some variables
mark_as_advanced(SDL_MIXER_INCLUDE_DIR)
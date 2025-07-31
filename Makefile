

OUT_NAME 		   = rebar
OUT_DIR	   		   = dist

ENTRIES 	   	   = main.cc cc/sdl.cc


ENTRIES_FMT		   = $(foreach e,$(ENTRIES),../src/$(e))


# === For Windows ===

# C:\Program Files (x86)\Microsoft Visual Studio\<???>
YEAR_MSVC		   = 2022

# C:\Program Files (x86)\Microsoft Visual Studio\<YEAR_MSVC>\BuildTools\VC\Tools\MSVC\<???>
VERSION_MSVC   	   = 14.44.35207

# C:\Program Files (x86)\Windows Kits\<???>
VERSION_WINDOWS	   = 10

# C:\Program Files (x86)\Windows Kits\<VERSION_WINDOWS>\Lib\<???>
VERSION_KITS   	   = 10.0.26100.0


# 1. Compiler, entry and out

CC_WIN			 = cl


# 2. Paths to Vulkan SDK, Windows Kits and Microsoft Build Tools

SDL_LIST_WIN	 = C:\SDL3-3.2.18 C:\SDL3_image-3.2.4
KITS	 	 	 = C:\Program Files (x86)\Windows Kits\$(VERSION_WINDOWS)
MSVC 	 	 	 = C:\Program Files (x86)\Microsoft Visual Studio\$(YEAR_MSVC)\BuildTools\VC\Tools\MSVC\$(VERSION_MSVC)


# 3. Include paths

INCL_SDL_WIN	 = $(foreach a,$(SDL_LIST_WIN),$(a)\include)
INCL_MSVC	 	 = $(MSVC)\include
INCL_UCRT		 = $(KITS)\Include\$(VERSION_KITS)\ucrt
INCL_UM			 = $(KITS)\Include\$(VERSION_KITS)\um


# 4. Library paths

LIB_SDL_WIN		 = $(foreach a,$(SDL_LIST_WIN),$(a)\lib\x64)
LIB_MSVC		 = $(MSVC)\lib\x64
LIB_UCRT		 = $(KITS)\Lib\$(VERSION_KITS)\ucrt\x64
LIB_UM			 = $(KITS)\Lib\$(VERSION_KITS)\um\x64


# 5. Flags

FLAGS_INCL_WIN 	 = $(foreach flag,$(INCL_SDL_WIN),/I"$(flag)") /I"$(INCL_MSVC)" /I"$(INCL_UCRT)" /I"$(INCL_UM)"
FLAGS_LIB_WIN    = $(foreach flag,$(LIB_SDL_WIN),/LIBPATH:"$(flag)") /LIBPATH:"$(LIB_MSVC)" /LIBPATH:"$(LIB_UM)" /LIBPATH:"$(LIB_UCRT)"

FLAGS_COMP_WIN	 = /EHsc /Fe"$(OUT_NAME).exe" $(FLAGS_INCL_WIN)
FLAGS_LINK_WIN	 = $(FLAGS_LIB_WIN) $(SUBSYSTEM) SDL3.lib /SUBSYSTEM:CONSOLE


# 6. Scripts

compile_win:
	cd .\$(OUT_DIR) && $(CC_WIN) $(subst /,\,$(ENTRIES_FMT)) $(FLAGS_COMP_WIN) /link $(FLAGS_LINK_WIN)

build_win: compile_win

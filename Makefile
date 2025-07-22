

OUT_NAME 		   = rebar
OUT_DIR_NAME	   = dist
VERSION_SDK 	   = 1.4.321.1



# === For Windows ===


# 1. Version names
# Check which ones you have and change accordingly before building!!!

# C:\Program Files (x86)\Microsoft Visual Studio\<???>
YEAR_MSVC		   = 2022

# C:\Program Files (x86)\Microsoft Visual Studio\YEAR_MSVC\BuildTools\VC\Tools\MSVC\<???>
VERSION_MSVC   	   = 14.44.35207

# C:\Program Files (x86)\Windows Kits\<???>
VERSION_WINDOWS	   = 10

# C:\Program Files (x86)\Windows Kits\VERSION_WINDOWS\Lib\<???>
VERSION_KITS   	   = 10.0.26100.0


# 2. Compiler, entry and out

WIN_CC		 = cl
WIN_ENTRY	 = ..\src\main.cpp



# 3. Paths to Vulkan SDK, Windows Kits and Microsoft Build Tools

WIN_SDK		 	 = C:\VulkanSDK\$(VERSION_SDK)
KITS	 	 	 = C:\Program Files (x86)\Windows Kits\$(VERSION_WINDOWS)
MSVC 	 	 	 = C:\Program Files (x86)\Microsoft Visual Studio\$(YEAR_MSVC)\BuildTools\VC\Tools\MSVC\$(VERSION_MSVC)


# 4. Include paths

INCL_WIN_SDK	 = $(WIN_SDK)\Include
INCL_MSVC	 	 = $(MSVC)\include
INCL_UCRT		 = $(KITS)\Include\$(VERSION_KITS)\ucrt
INCL_UM			 = $(KITS)\Include\$(VERSION_KITS)\um


# 5. Library paths

LIB_WIN_SDK		 = $(WIN_SDK)\Lib
LIB_MSVC		 = $(MSVC)\lib\x64
LIB_UCRT		 = $(KITS)\Lib\$(VERSION_KITS)\ucrt\x64
LIB_UM			 = $(KITS)\Lib\$(VERSION_KITS)\um\x64


# 6. Flags

WIN_INCL_FLAGS 	 = /I"$(INCL_WIN_SDK)" /I"$(INCL_MSVC)" /I"$(INCL_UCRT)" /I"$(INCL_UM)"
WIN_LIB_FLAGS    = /LIBPATH:"$(LIB_WIN_SDK)" /LIBPATH:"$(LIB_MSVC)" /LIBPATH:"$(LIB_UM)" /LIBPATH:"$(LIB_UCRT)" SDL2.lib

SUBSYSTEM_FLAG   = /SUBSYSTEM:CONSOLE

WIN_COMPILER_FLAGS = /EHsc /Fe"$(OUT_NAME).exe" $(WIN_INCL_FLAGS)
WIN_LINKER_FLAGS   = $(WIN_LIB_FLAGS) $(SUBSYSTEM_FLAG)


# 7. Scripts


compile_win:
	cd .\$(OUT_DIR_NAME) && $(WIN_CC) $(WIN_ENTRY) $(WIN_COMPILER_FLAGS) /link $(WIN_LINKER_FLAGS)

cleanup_win:
	del .\$(OUT_DIR_NAME)\*.obj

build_win: compile_win cleanup_win

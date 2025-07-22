

OUT_NAME 		   = rebar
OUT_DIR	   		   = dist
ENTRY_NAME		   = main.cpp
ENRTY_DIR		   = src

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

CC_WIN			 = cl
ENTRY_WIN		 = ..\$(ENRTY_DIR)\$(ENTRY_NAME)
SUBSYSTEM  		 = /SUBSYSTEM:CONSOLE


# 3. Paths to Vulkan SDK, Windows Kits and Microsoft Build Tools

SDK_WIN		 	 = C:\VulkanSDK\$(VERSION_SDK)
KITS	 	 	 = C:\Program Files (x86)\Windows Kits\$(VERSION_WINDOWS)
MSVC 	 	 	 = C:\Program Files (x86)\Microsoft Visual Studio\$(YEAR_MSVC)\BuildTools\VC\Tools\MSVC\$(VERSION_MSVC)


# 4. Include paths

INCL_SDK_WIN	 = $(SDK_WIN)\Include
INCL_MSVC	 	 = $(MSVC)\include
INCL_UCRT		 = $(KITS)\Include\$(VERSION_KITS)\ucrt
INCL_UM			 = $(KITS)\Include\$(VERSION_KITS)\um


# 5. Library paths

LIB_SDK_WIN		 = $(SDK_WIN)\Lib
LIB_MSVC		 = $(MSVC)\lib\x64
LIB_UCRT		 = $(KITS)\Lib\$(VERSION_KITS)\ucrt\x64
LIB_UM			 = $(KITS)\Lib\$(VERSION_KITS)\um\x64


# 6. Flags

FLAGS_INCL_WIN 	 = /I"$(INCL_SDK_WIN)" /I"$(INCL_MSVC)" /I"$(INCL_UCRT)" /I"$(INCL_UM)"
FLAGS_LIB_WIN    = /LIBPATH:"$(LIB_SDK_WIN)" /LIBPATH:"$(LIB_MSVC)" /LIBPATH:"$(LIB_UM)" /LIBPATH:"$(LIB_UCRT)" SDL2.lib

FLAGS_COMP_WIN	 = /EHsc /Fe"$(OUT_NAME).exe" $(FLAGS_INCL_WIN)
FLAGS_LINK_WIN	 = $(FLAGS_LIB_WIN) $(SUBSYSTEM)


# 7. Scripts


compile_win:
	cd .\$(OUT_DIR) && $(CC_WIN) $(ENTRY_WIN) $(FLAGS_COMP_WIN) /link $(FLAGS_LINK_WIN)

cleanup_win:
	del .\$(OUT_DIR)\*.obj

build_win: compile_win cleanup_win

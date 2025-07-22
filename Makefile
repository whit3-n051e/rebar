
# === For Windows ===


# 1. Version names
# Check which ones you have and change accordingly before building!!!

# C:\VulkanSDK\<???>
SDK_VERSION 	   = 1.4.321.1

# C:\Program Files (x86)\Microsoft Visual Studio\<???>
MSVC_YEAR		   = 2022

# C:\Program Files (x86)\Microsoft Visual Studio\MSVC_YEAR\BuildTools\VC\Tools\MSVC\<???>
MSVC_VERSION   	   = 14.44.35207

# C:\Program Files (x86)\Windows Kits\<???>
WINDOWS_VERSION	   = 10

# C:\Program Files (x86)\Windows Kits\WINDOWS_VERSION\Lib\<???>
KITS_VERSION   	   = 10.0.26100.0


# 2. Compiler, entry and out

WIN_CC		 = cl
WIN_ENTRY	 = .\src\main.cpp
WIN_OUT		 = .\dist\out.exe


# 3. Paths to Vulkan SDK, Windows Kits and Microsoft Build Tools

WIN_SDK		 	 = C:\VulkanSDK\$(SDK_VERSION)
KITS	 	 	 = C:\Program Files (x86)\Windows Kits\$(WINDOWS_VERSION)
MSVC 	 	 	 = C:\Program Files (x86)\Microsoft Visual Studio\$(MSVC_YEAR)\BuildTools\VC\Tools\MSVC\$(MSVC_VERSION)


# 4. Include paths

WIN_SDK_INCL	 = $(WIN_SDK)\Include
MSVC_INCL	 	 = $(MSVC)\include
UCRT_INCL		 = $(KITS)\Include\$(KITS_VERSION)\ucrt
UM_INCL			 = $(KITS)\Include\$(KITS_VERSION)\um


# 5. Library paths

WIN_SDK_LIB		 = $(WIN_SDK)\Lib
MSVC_LIB		 = $(MSVC)\lib\x64
UCRT_LIB		 = $(KITS)\Lib\$(KITS_VERSION)\ucrt\x64
UM_LIB			 = $(KITS)\Lib\$(KITS_VERSION)\um\x64


# 6. Flags

WIN_INCL_FLAGS = /I"$(WIN_SDK_INCL)" /I"$(MSVC_INCL)" /I"$(UCRT_INCL)" /I"$(UM_INCL)"
WIN_LIB_FLAGS  = /LIBPATH:"$(WIN_SDK_LIB)" /LIBPATH:"$(MSVC_LIB)" /LIBPATH:"$(UM_LIB)" /LIBPATH:"$(UCRT_LIB)" SDL2.lib

WIN_COMPILER_FLAGS = /EHsc /Fe"$(WIN_OUT)" $(WIN_INCL_FLAGS)
WIN_LINKER_FLAGS   = $(WIN_LIB_FLAGS) /SUBSYSTEM:CONSOLE


# 7. Scripts

build_win:
	$(WIN_CC) $(WIN_ENTRY) $(WIN_COMPILER_FLAGS) /link $(WIN_LINKER_FLAGS)

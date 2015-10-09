cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(cv2pdb)

if(NOT MSVC)
	message(FATAL_ERROR "MSVC only!")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DUNICODE /D_UNICODE /D_CRT_SECURE_NO_WARNINGS")

set(cv2pdb_SOURCES
	src/cv2pdb.cpp
	src/cvutil.cpp
	src/demangle.cpp
	src/dwarf2pdb.cpp
	src/dwarflines.cpp
	src/main.cpp
	src/mspdb.cpp
	src/PEImage.cpp
	src/readDwarf.cpp
	src/symutil.cpp
)

set(cv2pdb_HEADERS
	src/cv2pdb.h
	src/cvutil.h
	src/dcvinfo.h
	src/demangle.h
	src/dwarf.h
	src/LastError.h
	src/mscvpdb.h
	src/mspdb.h
	src/PEImage.h
	src/readDwarf.h
	src/symutil.h
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	list(
		APPEND
		cv2pdb_SOURCES
		src/cvt80to64.asm
	)
	enable_language(ASM_MASM)
endif()

add_executable(
	cv2pdb
	${cv2pdb_SOURCES}
	${cv2pdb_HEADERS}
)

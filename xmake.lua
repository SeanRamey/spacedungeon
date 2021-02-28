add_requires("sfml","doctest")

target("spacedungeon-lib")
	set_kind("static")
	set_languages("cxx17")
	add_packages("sfml","doctest")

	-- recursively search for .cpp files under the src directory, but exclude any .cpp files under src/unit-tests directory and the main.cpp file
	add_files("src/**.cpp|unit-tests/*.cpp|main.cpp")

	-- couldn't figure a way to recursively search for header files, so I just manually listed the directories
	add_includedirs("src")
	add_includedirs("src/entities")
	add_includedirs("src/entities/weapons")
	add_includedirs("src/gamestate")
	add_includedirs("src/ui")
	add_includedirs("src/util")
	add_includedirs("src/unit-tests")

target("spacedungeon")
	set_kind("binary")
	set_languages("cxx17")
	add_deps("spacedungeon-lib")
	add_packages("sfml","doctest")
	set_rundir("$(projectdir)")

	-- only need the main.cpp because the rest is in the spacedungeon-lib dependency
	add_files("src/main.cpp")

	-- couldn't figure a way to recursively search for header files, so I just manually listed the directories
	add_includedirs("src")
	add_includedirs("src/entities")
	add_includedirs("src/entities/weapons")
	add_includedirs("src/gamestate")
	add_includedirs("src/ui")
	add_includedirs("src/util")
	add_includedirs("src/unit-tests")

target("unit-tests")
	set_kind("binary")
	set_languages("cxx17")
	add_deps("spacedungeon-lib")
	add_packages("sfml","doctest")
	set_rundir("$(projectdir)")

	-- recursively search for .cpp files under the src/unit-tests directory
	add_files("src/unit-tests/**.cpp")

	-- couldn't figure a way to recursively search for header files, so I just manually listed the directories
	add_includedirs("src")
	add_includedirs("src/entities")
	add_includedirs("src/entities/weapons")
	add_includedirs("src/gamestate")
	add_includedirs("src/ui")
	add_includedirs("src/util")
	add_includedirs("src/unit-tests")

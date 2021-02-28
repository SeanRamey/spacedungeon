add_requires("sfml","doctest")
target("spacedungeon")
	set_kind("binary")
	set_languages("cxx17")
	add_packages("sfml","doctest")
	set_rundir("$(projectdir)")

	-- recursively search for .cpp files under the src directory, but exclude any .cpp files under src/unit-tests directory
	add_files("src/**.cpp|unit-tests/*.cpp")

	-- couldn't figure a way to recursively search for header files, so I just manually listed the directories
	add_includedirs("src")
	add_includedirs("src/entities")
	add_includedirs("src/entities/weapons")
	add_includedirs("src/gamestate")
	add_includedirs("src/ui")
	add_includedirs("src/util")
	add_includedirs("src/unit-tests")

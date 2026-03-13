add_rules("mode.debug", "mode.release")

add_requires("sdl2")

target("celeste")
do
    add_files("celeste.c")
    add_files("sdl12main.c")
    add_packages("sdl2")
    add_links("SDL2","SDL2main", "SDL2_test")
end
target_end()

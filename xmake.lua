add_rules("mode.release")
add_requires("levilamina")
target("MadenRadar")
    set_kind("shared")
    set_languages("cxx20")
    add_files("src/*.cpp")
    add_packages("levilamina")
    set_filename("libMadenRadar.so")
    if is_mode("release") then
        set_strip("all")
        add_cxxflags("-fvisibility=hidden","-ffunction-sections","-fdata-sections")
        add_ldflags("-Wl,--gc-sections")
    end

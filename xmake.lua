add_rules("mode.release")
add_requires("preloader_android")
target("MadenRadar")
    set_kind("shared")
    set_languages("cxx20")
    add_files("src/*.cpp")
    add_packages("preloader_android")
    set_filename("libMadenRadar.so")
    if is_mode("release") then
        set_strip("all")
        add_cxxflags("-fvisibility=hidden")
    end

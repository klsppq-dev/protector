# Пример программы, которая использует библиотеку

add_executable(app main.c)

target_link_libraries(app
    PRIVATE
        -Wl,--whole-archive hardcore -Wl,--no-whole-archive
        dl
)

target_link_options(app PRIVATE -rdynamic)

target_include_directories(app PRIVATE ../include)

add_library(
    hardcore STATIC
    hardcore/init.c
    hardcore/proc_check.c
    hardcore/secret.c
    hardcore/hardening_loader.c
)

target_include_directories(hardcore PRIVATE ../include)

add_library(
    hardening SHARED
    hardening/init.c
    hardening/integrity.c
    hardening/memory_check.c
    hardening/roundtrip.c
)

target_include_directories(hardening PRIVATE ../include)

set_target_properties(hardening PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    C_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

# Для выключения логов закомментируйте эти две строки
target_compile_definitions(hardcore PRIVATE PROTECTOR_LOG_ENABLED=1)
target_compile_definitions(hardening PRIVATE PROTECTOR_LOG_ENABLED=1)

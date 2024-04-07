set(srcs "main.c" "spp_server.c")

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS ".")

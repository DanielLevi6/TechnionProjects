#cmake_minimum_required(VERSION 3.0.0)
#project(MatamkiyaProject VERSION 0.1.0)

#set(CMAKE_C_STANDARD 99)


cmake_minimum_required(VERSION 3.0.0)

project(MatamkiyaProject VERSION 0.1.0 LANGUAGES C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror -DNDEBUG=1 -lm")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})


#set(MTM_FLAGS_DEBUG "-std=c99 -g --pedantic-errors -Wall -Werror -o  -L. -lmtm -lm -las")
#set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
#link_libraries(as mtm)



link_directories(.)
add_executable(matamikya amount_set.h list.h matamikya_print.h matamikya_print.c matamikya.h matamikya.c set.h order.h order.c product.c product.h biadsy_matamikya_tests.c)
#add_executable(matamikya amount_set.h list.h matamikya_print.h matamikya_print.c matamikya.h matamikya.c set.h order.h order.c product.c product.h tests/matamikya_tests.c tests/matamikya_main.c)
target_link_libraries(matamikya libas.a libmtm.a)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

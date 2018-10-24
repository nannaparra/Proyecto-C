cmake_minimum_required (VERSION 2.6)
project (planificador)

set(LISTA_SRC lista/lista.c)
set(COLACP_SRC colacp/colacp.c)
set(PLANIFICADOR_SRC planificador/planificador.c)
set(MAIN_SRC main.c)
set(SOURCE ${LISTA_SRC} ${COLACP_SRC} ${PLANIFICADOR_SRC} ${MAIN_SRC})

add_executable(planificador ${SOURCE})
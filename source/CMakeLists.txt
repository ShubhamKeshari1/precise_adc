# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(shell_module)

target_sources(app PRIVATE src/main.c src/adc_sampling.c src/calc_avg.c src/app_shellcmd_adc.c)
target_sources_ifdef(CONFIG_SHELL_BACKEND_SERIAL app PRIVATE src/uart_reinit.c)

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(adc)

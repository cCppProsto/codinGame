TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

SOURCES += main.c

HEADERS += \
    easy/the_descent.h \
    easy/chuck_norris.h \
    easy/ascii_art.h \
    easy/temperatures.h \
    easy/power_of_thor_episode_1.h \
    easy/defibrillators.h \
    easy/horse_racing_duals.h \
    easy/mime_type.h \
    easy/mars_lander_episode_1.h \
    medium/there_is_no_spoon_episode_1.h \
    medium/shadows_of_the_knight_episode_1.h \
    medium/bender_episode_1.h \
    medium/donot_panic_episode_1.h \
    medium/teads_sponsored_contest.h

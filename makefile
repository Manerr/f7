# ----------------------------
# Makefile Options
# ----------------------------

NAME = f7
ICON = icon.png
DESCRIPTION = "f7 by Paul_T_"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

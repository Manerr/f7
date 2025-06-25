# ----------------------------
# Makefile Options
# ----------------------------

NAME = f7
ICON = icon.png
DESCRIPTION = "File explorer for ticalcs"
COMPRESSED = NO
OUTPUT_MAP = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

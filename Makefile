.DEFAULT_GOAL := static
# Copyright (C)  2026 Emir Baha YILDIRIM <jayshozie@gmail.com>
# Copyright (C)  2026 terra2o <terra2o@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC = GCC

# ansi escapes
BK = \033[30m
R  = \033[31m
G  = \033[32m
Y  = \033[33m
B  = \033[34m
M  = \033[35m
C  = \033[36m
W  = \033[37m
BO = \033[1m
RS = \033[0m

help:
	@echo -e "$(M)$(BO)Usage:$(RS)"
	@echo -e "   $(C)$(BO)make static$(RS)         $(B)$(BO)Build a static version of the library$(RS)"
	@echo -e "   $(C)$(BO)make shared$(RS)         $(B)$(BO)Build a shared version of the library$(RS)"
	@echo -e "   $(C)$(BO)make test$(RS)           $(B)$(BO)Run all test suites$(RS)"
	@echo -e "   $(C)$(BO)make help$(RS)           $(B)$(BO)Print this message$(RS)"

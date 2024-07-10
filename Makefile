SRCSF = $(TEST) \
		IRCServer.cpp \
		IRCClient.cpp \
		IRCChannel.cpp \
		CommandBuilder.cpp \
		Command.cpp \
		BotResources/Bot.cpp \
		Commands/Invite.cpp \
		Commands/Join.cpp \
		Commands/Kick.cpp \
		Commands/CommandMode.cpp \
		Commands/Nick.cpp \
		Commands/Part.cpp \
		Commands/Pass.cpp \
		Commands/Privmsg.cpp \
		Commands/Quit.cpp \
		Commands/Topic.cpp \
		Commands/User.cpp

INCSF = IRCServer.hpp \
		IRCClient.hpp \
		IRCChannel.hpp \
		IRCRespondMacros.hpp \
		CommandBuilder.hpp \
		Command.hpp \
		CommandMode.hpp \
		AuthLevel.hpp \
		GlobalVariables.hpp \
		Bot.hpp

ifndef $(TEST)
TEST=main.cpp
endif

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))

NAME = ircserv

DIRSRC = src
DIROBJ = obj/$(CONF)
DIRINC = inc

# All relative to Makefile's folder
SRCS = $(patsubst %.cpp,$(DIRSRC)/%.cpp, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.cpp=$(DIROBJ)/%.o)
INCS = $(patsubst %.hpp,$(DIRINC)/%.hpp, $(INCSF))
DEPS = $(OBJS:.o=.d)

# import CXX environment variable otherwise use c++
ifeq ($(wildcard $(CXX)),)
CXX = c++
endif

WFLAGS =  -Wall -Werror -Wextra
CPPFLAGS = -I$(DIRINC) -MMD -MP
CXXFLAGS = $(DFLAGS) $(WFLAGS) -std=c++98 
LDFLAGS = $(DFLAGS)

OPTS = $(OPT)
SAN = address 

CONF = release
CONF_TARGET = .target

ifneq (,$(findstring debug,$(CONF)))
OPTS = fsan,debug
endif

ifneq (,$(findstring dsym,$(CONF)))
OPTS = debug
endif

ifneq (,$(findstring debug,$(OPTS)))
	DFLAGS += -g3
endif

ifeq ($(EXTRA),1)
CPPFLAGS += -D EXTRA
endif

# RULES
all: $(NAME)

# EVALUATE:
# 	grep -v -q $(CONF) $(CONF_TARGET) && echo $(CONF) > $(CONF_TARGET)


# marker for the last built architecture
BUILT_MARKER := $(CONF).built

$(BUILT_MARKER):
	@-rm -f *.built
	@touch $(BUILT_MARKER)

# OBJ TO PROJECT
$(NAME): $(OBJS) $(BUILT_MARKER)
	-@printf "${BLUE}"
	$(CXX) $(PGFLAGS) $(OBJS) $(LDFLAGS) -o $@
	-@printf "${NC}"

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.cpp $(INCS) | $(DIROBJ)
	-@mkdir -p $(dir $@)
	-@printf "${GREEN}"
	-$(CXX) $(PGFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
	-@printf "${NC}"

exec-clean:
	-@printf "${BRED}Cleaning executable!\n${RED}"
	-rm -f $(NAME)
	-@printf "${NC}"

obj-clean:
	-@printf "${BYELLOW}Cleaning objects!\n${RED}"
	-rm -rf obj
	-@printf "${NC}"

# CLEANING
fclean: exec-clean clean

clean: obj-clean

er: exec-clean all

re: fclean all

# Dependencies
-include $(DEPS)

# Folders
$(DIROBJ):
	-@printf "${CYAN}"
	-mkdir -p $(DIROBJ)
	-@printf "${NC}"

.PHONY: all re er fclean clean

# COLORS
export BGREEN = \033[1;32m
export GREEN = \033[0;32m
export BRED = \033[1;31m
export RED = \033[0;31m
export BYELLOW = \033[1;33m
export YELLOW = \033[0;33m
export BBLUE = \033[1;34m
export BLUE = \033[0;34m
export BCYAN = \033[1;36m
export CYAN = \033[0;36m
export NC = \033[0m

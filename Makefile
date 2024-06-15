SRCSF = $(TEST) \
		IRCServer.cpp \
		IRCClient.cpp \
		IRCChannel.cpp \
		CommandBuilder.cpp \
		Command.cpp \
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
		AuthLevel.hpp 

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
DIRLIB = lib

# All relative to Makefile's folder
SRCS = $(patsubst %.cpp,$(DIRSRC)/%.cpp, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.cpp=$(DIROBJ)/%.o)
INCS = $(patsubst %.hpp,$(DIRINC)/%.hpp, $(INCSF))
DEPS = $(OBJS:.o=.d)

LIB-I = $(patsubst %,-I%,$(dir $(LIBS))) -I$(DIRLIB)
LIB-l = $(subst lib,-l,$(basename $(notdir $(LIBSF))))
LIB-L = $(patsubst %,-L$(DIRLIB)/%, $(dir $(LIBSF)))

CXX = c++

WFLAGS =  #-Wall -Werror -Wextra
CPPFLAGS = -I$(DIRINC) $(LIB-I) -MMD -MP
CXXFLAGS = $(OPFLAG) $(DFLAGS) $(XCFLAGS) $(WFLAGS)
LDFLAGS = $(OPFLAG) $(DFLAGS) $(XLDFLAGS)
#OPFLAG = -O3 -flto -march=native -mtune=native -msse4.2 

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

ifneq (,$(findstring none,$(OPTS)))
OPFLAG = -O0
endif
ifneq (,$(findstring debug,$(OPTS)))
	OPFLAG = -O0
	DFLAGS += -g3
endif
ifneq (,$(findstring fdeb,$(OPTS)))
	OPFLAG = -O1 -march=native
	DFLAGS += -g3
endif
ifneq (,$(findstring fsan,$(OPTS)))

# -fno-sanitize-ignorelist -fsanitize-ignorelist=ignorelist.txt
# Compile with selected sanitizer:
# And when using other sanitizers such as memory or undefined, it may be useful to not prematurely stop,
# Use UBSAN_OPTIONS=halt_on_error=0 (need -fs..-recover=..) or equivelent
# Also might be nice to redirect stderr to a file
# USE 
	DFLAGS += -fsanitize=$(SAN) -fsanitize-recover=$(SAN) 
endif
ifneq (,$(findstring gmon,$(OPTS)))
	PGFLAGS += -pg
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
$(NAME): $(LIBS) $(OBJS) $(BUILT_MARKER)
	-@printf "${BLUE}"
	$(CXX) $(PGFLAGS) $(OBJS) $(LDFLAGS) -o $@
	-@printf "${NC}"

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.cpp $(INCS) | $(DIROBJ)
	-@mkdir -p $(dir $@)
	-@printf "${GREEN}"
	-$(CXX) $(PGFLAGS) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
	-@printf "${NC}"

# CLEANING
fclean: clean
	-@printf "${BRED}Cleaning executable!\n${RED}"
	-rm -f $(NAME)
	-@printf "${NC}"

clean:
	-@printf "${BYELLOW}Cleaning objects!\n${RED}"
	-rm -rf $(DIROBJ)
	-@printf "${NC}"

re: fclean all

# Dependencies
-include $(DEPS)

# Folders
$(DIROBJ):
	-@printf "${CYAN}"
	-mkdir -p $(DIROBJ)
	-@printf "${NC}"

.PHONY: all re fclean clean libclean

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

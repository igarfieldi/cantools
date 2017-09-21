CPP			:= g++
LD			:= g++

CPPFLAGS	+= --std=c++14

ANALYSESRC			:= src/cananalyse.cc
ANALYSEOBJ			:= obj/cananalyse.o
ANALYSEBIN			:= cananalyse
FILTERSRC			:= src/canfilter.cc
FILTEROBJ			:= obj/canfilter.o
FILTERBIN			:= canfilter
DIFFSRC				:= src/candiff.cc
DIFFOBJ				:= obj/candiff.o
DIFFBIN				:= candiff

.phony: all analyse filter diff

all: analyse filter freq

analyse:
	@$(CPP) -c $(ANALYSESRC) -o $(ANALYSEOBJ)
	@$(LD) -o $(ANALYSEBIN) $(ANALYSEOBJ)

filter:
	@$(CPP) -c $(FILTERSRC) -o $(FILTEROBJ)
	@$(LD) -o $(FILTERBIN) $(FILTEROBJ)
	
diff:
	@$(CPP) -c $(DIFFSRC) -o $(DIFFOBJ)
	@$(LD) -o $(DIFFBIN) $(DIFFOBJ)


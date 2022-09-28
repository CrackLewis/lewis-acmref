GENPDF = C:/Users/Dell/AppData/Roaming/npm/codes2pdf.cmd
OUTFILE = LewisManual.pdf
AUTHOR = "Lewis Lee"
INITIATE = "Tongji Univ."
WD = .

.PHONY: all

all: clear build

clear:
	del /s /q *.out 
	del /s /q *.exe 
	del /s /q *.in 

build:
	$(GENPDF) $(WD) -o $(OUTFILE) -a $(AUTHOR) -i $(INITIATE)
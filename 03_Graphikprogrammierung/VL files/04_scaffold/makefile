CC  = gcc
CXX = g++
CPPFLAGS = -DNDEBUG -I. -Os
CPDFLAGS = -D_DEBUG -I.

sources = decls.cxx pointer.cxx funcs.cxx main.cxx control.cxx ds.cxx func_over.cxx names.cxx references.cxx storage.cxx
src_names = $(basename $(notdir $(sources)))
release_objs = $(addsuffix .o,$(src_names))
debug_objs   = $(addsuffix _d.o,$(src_names))

.PHONY: all clean release debug

all: release
release: scaffold.exe
debug: scaffold_d.exe

clean:
	del *.o
	del *.exe

scaffold.exe: $(release_objs)
	$(CXX) $(CPPFLAGS) -o scaffold.exe $(release_objs)
decls.o: decls.cxx decls.h
	$(CXX) -c $(CPPFLAGS) decls.cxx
pointer.o: pointer.cxx decls.h
	$(CXX) -c $(CPPFLAGS) pointer.cxx
funcs.o: funcs.cxx
	$(CXX) -c $(CPPFLAGS) funcs.cxx
main.o: main.cxx
	$(CXX) -c $(CPPFLAGS) main.cxx
ds.o: ds.cxx
	$(CXX) -c $(CPPFLAGS) ds.cxx
storage.o: storage.cxx
	$(CXX) -c $(CPPFLAGS) storage.cxx
control.o: control.cxx
	$(CXX) -c $(CPPFLAGS) control.cxx
func_over.o: func_over.cxx
	$(CXX) -c $(CPPFLAGS) func_over.cxx
names.o: names.cxx
	$(CXX) -c $(CPPFLAGS) names.cxx
references.o: references.cxx
	$(CXX) -c $(CPPFLAGS) references.cxx

scaffold_d.exe: $(debug_objs)
	$(CXX) $(CPDFLAGS) -o scaffold_d.exe $(debug_objs)
decls_d.o: decls.cxx decls.h
	$(CXX) -c $(CPPFLAGS) decls.cxx -o decls_d.o
pointer_d.o: pointer.cxx decls.h
	$(CXX) -c $(CPDFLAGS) pointer.cxx -o pointer_d.o
funcs_d.o: funcs.cxx
	$(CXX) -c $(CPDFLAGS) funcs.cxx -o funcs_d.o
main_d.o: main.cxx
	$(CXX) -c $(CPDFLAGS) main.cxx -o main_d.o
ds_d.o: ds.cxx
	$(CXX) -c $(CPPFLAGS) ds.cxx -o ds_d.o
storage_d.o: storage.cxx
	$(CXX) -c $(CPPFLAGS) storage.cxx -o storage_d.o
control_d.o: control.cxx
	$(CXX) -c $(CPPFLAGS) control.cxx -o control_d.o
func_over_d.o: func_over.cxx
	$(CXX) -c $(CPPFLAGS) func_over.cxx -o func_over_d.o
names_d.o: names.cxx
	$(CXX) -c $(CPPFLAGS) names.cxx -o names_d.o
references_d.o: references.cxx
	$(CXX) -c $(CPPFLAGS) references.cxx -o references_d.o

CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL

OBJS = project2.o TEMPLATE_Subclass.o ModelView_Additions.o MonkeyBars.o Room.o Weights.o Disk.o Pole.o Cylinder.o Rwall.o Floor.o WeightHolder.o LiftingBar.o

project2: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o project2 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project2.o: project2.c++
	$(CPP) $(C_FLAGS) project2.c++
Room.o: Room.h Room.c++
	$(CPP) $(C_FLAGS) Room.c++
Disk.o: Disk.h Disk.c++
	$(CPP) $(C_FLAGS) Disk.c++
Rwall.o: Rwall.h Rwall.c++
	$(CPP) $(C_FLAGS) Rwall.c++
Floor.o: Floor.h Floor.c++
	$(CPP) $(C_FLAGS) Floor.c++
Pole.o: Pole.h Pole.c++
	$(CPP) $(C_FLAGS) Pole.c++
Cylinder.o: Cylinder.h Cylinder.c++
	$(CPP) $(C_FLAGS) Cylinder.c++
Weights.o: Weights.h Weights.c++
	$(CPP) $(C_FLAGS) Weights.c++
WeightHolder.o: WeightHolder.h WeightHolder.c++
	$(CPP) $(C_FLAGS) WeightHolder.c++
MonkeyBars.o: MonkeyBars.h MonkeyBars.c++
	$(CPP) $(C_FLAGS) MonkeyBars.c++
LiftingBar.o: LiftingBar.h LiftingBar.c++
	$(CPP) $(C_FLAGS) LiftingBar.c++
ModelView_Additions.o: ModelView_Additions.c++
	$(CPP) $(C_FLAGS) ModelView_Additions.c++
TEMPLATE_Subclass.o: TEMPLATE_Subclass.h TEMPLATE_Subclass.c++
	$(CPP) $(C_FLAGS) TEMPLATE_Subclass.c++

CC = gcc

CFLAGS = -O2 -Wall \
    -IConcretisation \
    -ISymbolicModel \
	-IProductSymbolicModel \
    -IReachabilityAnalysis \
	-IBitmap \
	-IBitmapList \
	-IMultiStageBitmap \
	-IMSBitMapList \
	-IModel_3D \
	-IKSI \
	-ISIGMA \
	-IReachability \
	-IExampleSpecification_3D_0 \
	-IRegions \
	-IAutomatonBasedController \
	-IProductReachabilityController \
	-IReachabilityController \
	-ISafetyController \
	-ISymbolicController \
	-Iboolean \
	-Iploting \
	-IVectorMath

# output directory
OUT = out

# sources
SRC = \
    main.c \
	BitMap/BitMap.c \
	BitMap/BitMapList.c \
	BitMap/MultiStageBitMap.c \
	BitMap/MSBitMapList.c \
    Concretisation/ConcreteModel.c \
	ContinuousSystem/Model_3D.c \
	Discretization/KSI.c \
	Discretization/SIGMA.c \
    ReachabilityAnalysis/Reachability.c \
	SpecificationAutomata/ExampleSpecification_3D_0.c \
	SpecificationAutomata/Regions.c \
	SymbolicController/AutomatonBasedController.c \
	SymbolicController/ProductReachabilityController.c \
	SymbolicController/SymbolicController.c \
	SymbolicController/SafetyController.c \
	SymbolicController/ReachabilityController.c \
	SymbolicModel/ProductSymbolicModel.c \
    SymbolicModel/SymbolicModel.c \
	Visualization/ploting.c \
	VectorMath.c

# object files live in OUT/
OBJ = $(SRC:%.c=$(OUT)/%.o)

ifeq ($(OS),Windows_NT)
    EXE = .exe
else
    EXE =
endif

TARGET = $(OUT)/main$(EXE)

# default rule
all: $(OUT) $(TARGET)

# create output directory (including subdirs)
$(OUT):
	mkdir -p $(OUT)/BitMap
	mkdir -p $(OUT)/Concretisation
	mkdir -p $(OUT)/ContinuousSystem
	mkdir -p $(OUT)/Discretization
	mkdir -p $(OUT)/SymbolicModel
	mkdir -p $(OUT)/ReachabilityAnalysis
	mkdir -p $(OUT)/SpecificationAutomata
	mkdir -p $(OUT)/SymbolicController
	mkdir -p $(OUT)/Visualization

# link step
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# compile each .c into out/… .o
$(OUT)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# run target
run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(OUT)

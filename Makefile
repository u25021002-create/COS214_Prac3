CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET   = eventflow

SRCS = EventComponent.cpp EventUnit.cpp EventGroup.cpp \
       EventNotice.cpp Observer.cpp Subject.cpp EventControl.cpp \
       DisplayZone.cpp PrepZone.cpp \
       MainGate.cpp MerchStall.cpp FoodStall.cpp AutographBooth.cpp \
       MedicalTent.cpp VehicleDisplay.cpp DroidShow.cpp AnnouncementBooth.cpp \
       main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean


all: programa

OCVFLAGS=`pkg-config --cflags --libs opencv`

programa:
	$(CXX) $(CXXFLAGS) $(OCVFLAGS) videocapture_camera.cpp -o programa


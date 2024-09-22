SOURCE="./src/main.cpp"
GLAD_SOURCE="./src/glad.c"
OUTPUT="main"

g++ $SOURCE $GLAD_SOURCE -o $OUTPUT -I./src/include -lglfw -ldl -lGL
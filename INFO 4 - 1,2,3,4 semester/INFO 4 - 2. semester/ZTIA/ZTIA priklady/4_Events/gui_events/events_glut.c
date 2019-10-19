// Event loop and callbacks using GLUT
// https://www.opengl.org/resources/libraries/glut/

#include <stdio.h>
#include <stdlib.h>
#include <glut/glut.h>

void mouseEventHandler(int button, int state, int x, int y) {
  printf("MouseEvent: button=%d state=%d x=%d y=%d\n", button, state, x, y);
}

void keyboardEventHandler(unsigned char key, int x, int y) {
  printf("KeyboardEvent: key=%d, x=%d, y=%d\n", key, x, y);
  if(key == 27) exit(0);
}

void displayEventHandler() {}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutCreateWindow("Glut Window");
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 320);

  glutMouseFunc(mouseEventHandler);
  glutKeyboardFunc(keyboardEventHandler);
  glutDisplayFunc(displayEventHandler);

  glutMainLoop();
}

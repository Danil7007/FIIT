// Event loop and callbacks using GTK2
// https://developer.gnome.org/gtk2/

#include <stdio.h>
#include <gtk/gtk.h>

int mouseEventHandler(GtkWidget *window, GdkEventButton *event, GdkWindowEdge edge) {
  printf("MouseEvent: button=%d, x=%f, y=%f\n", event->button, event->x, event->y);
  return 0;
}

int keyEventHandler(GtkWidget *widget, GdkEventKey *event) {
  printf("KeyboardEvent: key=%d\n", event->keyval);
  if(event->keyval == 65307) gtk_main_quit();
  return 0;
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GTK Window");
  gtk_window_move(GTK_WINDOW(window), 100, 100);
  gtk_window_set_default_size(GTK_WINDOW(window), 320, 320);
  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect(window, "key-press-event", G_CALLBACK(keyEventHandler), NULL);
  g_signal_connect(window, "button-press-event", G_CALLBACK(mouseEventHandler), NULL);

  gtk_widget_show(window);
  gtk_main();
  return 0;
}

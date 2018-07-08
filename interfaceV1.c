#include <stdio.h>
#include <gtk/gtk.h>

void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *grid;
  GtkWidget *view1;
  GtkTextBuffer *buffer1;
  GtkWidget *view2;
  GtkTextBuffer *buffer2;

//nova janela
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "My Little Proxy");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 400);


//grid para localizar as coisas na janela
  grid = gtk_grid_new();
//colocar o grid na janela
  gtk_container_add (GTK_CONTAINER (window), grid);
 

//botoes
  button1 = gtk_button_new_with_label ("Spider");
  g_signal_connect (button1, "clicked", G_CALLBACK (print_hello), NULL);
  //g_signal_connect_swapped (button1, "clicked", G_CALLBACK (gtk_widget_destroy), window);
//colocar o botao no grid
  gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

  button2 = gtk_button_new_with_label("Dump");
  g_signal_connect (button2, "clicked", G_CALLBACK (print_hello), NULL);
  //g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), window);
//colocar o botao no grid
  gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);


//visualizador de texto
  view1 = gtk_text_view_new();

//o que será escrito
  buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view1));
  gtk_text_buffer_set_text(buffer1, "I SAID HEY, WHAT'S GOING ON?", -1);
  gtk_grid_attach(GTK_GRID(grid), view1, 0,2,1,1);

//visualizador de texto
  view2 = gtk_text_view_new();

//o que será escrito
  buffer2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view2));
  gtk_text_buffer_set_text(buffer2, "HEY EI HEY HEY HEY HEY EI EI", -1);
  gtk_grid_attach(GTK_GRID(grid), view2, 4,2,1,1);


  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

#include <gtk/gtk.h>

typedef struct MinhaJanela {

	GtkWidget *window;
	GtkWidget *botao1;
	GtkWidget *botao2;
	GtkWidget *botao3;
	GtkWidget *botao4;
	GtkWidget *texto1;
	GtkWidget *texto2;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *grid;
  	GtkWidget *view1;
  	GtkTextBuffer *buffer1;
  	GtkWidget *view2;
  	GtkTextBuffer *buffer2;
  	GtkWidget *view3;
  	GtkTextBuffer *buffer3;
  	GtkWidget *view4;
  	GtkTextBuffer *buffer4;


	char *string1;
	char *string2;
	char *string3;
	char *string4;

} JanelaPrincipal;


static void botao_clicado1(GtkWidget *, gpointer);
static void botao_clicado2(GtkWidget *, gpointer);
static void botao_clicado3(GtkWidget *, gpointer);
static void botao_clicado4(GtkWidget *, gpointer);

/*! \brief Controi a janela e demais widgets
*
* Em GTK, as janelas, os botoes, a grade, entre outros, sao todos widgets do GTK que devem ter suas relacoes explicitadas
* na funcao activate
*/
static void activate (GtkApplication *app, gpointer user_data)
{
	JanelaPrincipal janela;
	char *teste = "testeste";

	janela.window = gtk_application_window_new(app);
	printf("janela.window = gtk_application_window_new\n");

	gtk_window_set_title(GTK_WINDOW(janela.window), "My little Proxy");
	gtk_window_set_default_size(GTK_WINDOW(janela.window), 1080, 980);
	gtk_window_set_position(GTK_WINDOW(janela.window), GTK_WIN_POS_CENTER);

	janela.grid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (janela.window), janela.grid);

	janela.view3 = gtk_text_view_new();

	//o que será escrito
  	janela.buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view3));
  	gtk_text_buffer_set_text(janela.buffer1, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view3, 0,3,1,1);
	
	janela.view4 = gtk_text_view_new();

	//o que será escrito
  	janela.buffer2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view4));
  	gtk_text_buffer_set_text(janela.buffer2, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view4, 270,3,1,1);

	janela.view1 = gtk_text_view_new();

	//o que será escrito
  	janela.buffer3 =gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view1));
  	gtk_text_buffer_set_text(janela.buffer3, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view1, 540,3,1,1);

	janela.view2 =gtk_text_view_new();

	//o que será escrito
  	janela.buffer4 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view2));
  	gtk_text_buffer_set_text(janela.buffer4, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view2, 810,3,1,1);

	//botoes
  	janela.botao1 = gtk_button_new_with_label ("Spider");
  	g_signal_connect (janela.botao1, "clicked", G_CALLBACK (botao_clicado1), &janela);
	//colocar o botao no grid
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.botao1, 5, 0, 1, 1);

	//botoes
  	janela.botao2 = gtk_button_new_with_label ("Dump");
  	g_signal_connect (janela.botao2, "clicked", G_CALLBACK (botao_clicado2), &janela);
	//colocar o botao no grid ao lado do botao1
  	gtk_grid_attach_next_to(GTK_GRID(janela.grid), janela.botao2, janela.botao1,GTK_POS_RIGHT, 1, 1);

	//botoes
  	janela.botao3 = gtk_button_new_with_label ("Request");
  	g_signal_connect (janela.botao3, "clicked", G_CALLBACK (botao_clicado3), &janela);
	//colocar o botao no grid ao lado do botao1
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.botao3,5, 1, 1, 1);
	//botoes
  	janela.botao4 = gtk_button_new_with_label ("Reply");
  	g_signal_connect (janela.botao4, "clicked", G_CALLBACK (botao_clicado4), &janela);
	//colocar o botao no grid ao lado do botao1
  	gtk_grid_attach_next_to(GTK_GRID(janela.grid), janela.botao4, janela.botao3,GTK_POS_RIGHT, 1, 1);

	janela.texto1 = gtk_entry_new();
	gtk_widget_set_size_request(janela.texto1, 90, 30);


	janela.label3 = gtk_label_new("Request");
	gtk_grid_attach(GTK_GRID(janela.grid), janela.label3, 0, 2, 1, 1);
	gtk_widget_set_size_request(janela.label3, 100, 30);

	janela.label4 = gtk_label_new("Reply");
	gtk_grid_attach(GTK_GRID(janela.grid), janela.label4, 270, 2, 1, 1);
	gtk_widget_set_size_request(janela.label4, 100, 30);

	janela.label1 = gtk_label_new("Spider");
	gtk_grid_attach(GTK_GRID(janela.grid), janela.label1, 540, 2, 1, 1);
	gtk_widget_set_size_request(janela.label1, 100, 30);

	janela.label2 = gtk_label_new("Dump");
	gtk_grid_attach(GTK_GRID(janela.grid), janela.label2, 810, 2, 1, 1);
	gtk_widget_set_size_request(janela.label2,100, 30);

	janela.string1 = "tuc tuc tuc\n";

	janela.string2 = "cut cut cut\n";

	janela.string3 = "cut cut tuuut\n";

	janela.string4 = "cut-t-t-t\n";

	gtk_widget_show_all(janela.window);
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

/*! \brief as funcoens botao_clicadon devem ser acionadas quando se clica no botao
*
* Ha um ponteiro para funcao no botao que chama essas funcoes. Essa funcao deveria ser substituida para uma funcao do proxy 
* no codigo principal.
*/
static void botao_clicado1(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer3, ((JanelaPrincipal *)data) -> string1, -1);


	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer4,((JanelaPrincipal *)data) -> string2, -1);

}


static void botao_clicado2(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer3, ((JanelaPrincipal *)data) -> string2, -1);
	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer4, ((JanelaPrincipal *)data) -> string1, -1);

}


static void botao_clicado3(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer1, ((JanelaPrincipal *)data) -> string3, -1);
	

}

static void botao_clicado4(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer2, ((JanelaPrincipal *)data) -> string4, -1);
	

}

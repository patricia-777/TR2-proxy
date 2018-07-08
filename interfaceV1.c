#include <gtk/gtk.h>

typedef struct MinhaJanela {

	GtkWidget *window;
	GtkWidget *botao1;
	GtkWidget *botao2;
	GtkWidget *texto1;
	GtkWidget *texto2;
	GtkWidget *label;
	GtkWidget *fixed1;
	GtkWidget *fixed2;
	GtkWidget *grid;
  	GtkWidget *view1;
  	GtkTextBuffer *buffer1;
  	GtkWidget *view2;
  	GtkTextBuffer *buffer2;
	char *string1;
	char *string2;

} JanelaPrincipal;
	
static void botao_clicado1(GtkWidget *, gpointer);
static void botao_clicado2(GtkWidget *, gpointer);

int main(int argc, char *argv[])
{
	JanelaPrincipal janela;
	char *teste = "testeste";

	gtk_init(&argc, &argv);

	janela.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(janela.window), "Minha Janela");
	gtk_window_set_default_size(GTK_WINDOW(janela.window), 800, 400);
	gtk_window_set_position(GTK_WINDOW(janela.window), GTK_WIN_POS_CENTER);

	janela.grid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (janela.window), janela.grid);

	janela.fixed1 = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(janela.window), janela.fixed1);

	janela.fixed2 = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(janela.window), janela.fixed2);

	janela.view1 = gtk_text_view_new();

	//o que será escrito
  	janela.buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view1));
  	gtk_text_buffer_set_text(janela.buffer1, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view1, 0,2,1,100);
	
	janela.view2 = gtk_text_view_new();

	//o que será escrito
  	janela.buffer2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (janela.view2));
  	gtk_text_buffer_set_text(janela.buffer2, teste, -1);
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.view2, 50,2,1,100);

	//botoes
  	janela.botao1 = gtk_button_new_with_label ("Spider");
  	g_signal_connect (janela.botao1, "clicked", G_CALLBACK (botao_clicado1), &janela);
  	//g_signal_connect_swapped (botao1, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	//colocar o botao no grid
  	gtk_grid_attach(GTK_GRID(janela.grid), janela.botao1, 5, 0, 1, 1);

	//botoes
  	janela.botao2 = gtk_button_new_with_label ("Dump");
  	g_signal_connect (janela.botao2, "clicked", G_CALLBACK (botao_clicado2), &janela);
  	//g_signal_connect_swapped (botao1, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	//colocar o botao no grid ao lado do botao1
  	gtk_grid_attach_next_to(GTK_GRID(janela.grid), janela.botao2, janela.botao1,GTK_POS_RIGHT, 1, 1);

	janela.texto1 = gtk_entry_new();
	//gtk_fixed_put(GTK_FIXED(janela.fixed1), janela.texto1, 15, 15);
	gtk_widget_set_size_request(janela.texto1, 90, 30);

	/*janela.botao = gtk_button_new_with_label("Botão");
	gtk_fixed_put(GTK_FIXED(janela.fixed), janela.botao, 115, 15);
	gtk_widget_set_size_request(janela.botao, 80, 30);*/

	janela.label = gtk_label_new("Label");
	//gtk_fixed_put(GTK_FIXED(janela.fixed1), janela.label, 190, 15);
	gtk_widget_set_size_request(janela.label, 100, 30);

	janela.string1 = "tuc tuc tuc\n";

	janela.string2 = "cut cut cut\n";



	gtk_widget_show_all(janela.window);
	gtk_main();

	return 0;
}

/* Função chamada */
static void botao_clicado1(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer2, ((JanelaPrincipal *)data) -> string1, -1);


	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer1, ((JanelaPrincipal *)data) -> string2, -1);

	gtk_label_set_text( GTK_LABEL( ((JanelaPrincipal *)data) -> label ),
				(gchar *)gtk_entry_get_text(GTK_ENTRY( ((JanelaPrincipal *)data)  -> texto1)) );
}


static void botao_clicado2(GtkWidget *widget, gpointer data){	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer2, ((JanelaPrincipal *)data) -> string2, -1);
	
	gtk_text_buffer_set_text(((JanelaPrincipal *)data) -> buffer1, ((JanelaPrincipal *)data) -> string1, -1);

	gtk_label_set_text( GTK_LABEL( ((JanelaPrincipal *)data) -> label ),
				(gchar *)gtk_entry_get_text(GTK_ENTRY( ((JanelaPrincipal *)data)  -> texto1)) );
}























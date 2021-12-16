#include <gtk/gtk.h>


void
on_button1_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button4_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_treeview_utilisateur_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_chercher_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data);


void
on_button_alarme_clicked               (GtkWidget       *objet,
                                        gpointer         user_data);

void
on_button_deconnecter_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_mod_retour_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_af_retour_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajout_retour_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_retour_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_alarme_retour_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_capteurs_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_stock_clicked                       (GtkButton       *button,
                                        gpointer         user_data);

void
on_reclamation_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_agent_de_foyer_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_nutrisioniste_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_gestion_utilisateur_enter           (GtkButton       *button,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_utilisateur_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "utilisateur.h"

int verification_bot = 0;
void
on_button1_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj_utilisateur, *dashboard_utilisateur;


dashboard_utilisateur=lookup_widget(objet,"dashboard_utilisateur");

gtk_widget_hide(dashboard_utilisateur);
aj_utilisateur=lookup_widget(objet,"aj_utilisateur");
aj_utilisateur=create_aj_utilisateur();

gtk_widget_show(aj_utilisateur);
}


void
on_button2_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod_utilisateur, *dashboard_utilisateur;


dashboard_utilisateur=lookup_widget(objet,"dashboard_utilisateur");

gtk_widget_hide(dashboard_utilisateur);
mod_utilisateur=lookup_widget(objet,"mod_utilisateur");
mod_utilisateur=create_mod_utilisateur();

gtk_widget_show(mod_utilisateur);
}


void
on_button3_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af_utilisateur, *dashboard_utilisateur;


dashboard_utilisateur=lookup_widget(objet,"dashboard_utilisateur");

gtk_widget_hide(dashboard_utilisateur);

af_utilisateur=create_af_utilisateur();

gtk_widget_show(af_utilisateur);

treeview=lookup_widget(af_utilisateur,"treeview_utilisateur");

afficher_utilisateur(treeview,"utilisateur.txt");
}


void
on_button4_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *alarme, *dashboard_utilisateur;
dashboard_utilisateur=lookup_widget(objet,"dashboard_utilisateur");
gtk_widget_hide(dashboard_utilisateur);
alarme=create_alarme();
gtk_widget_show(alarme);
treeview=lookup_widget(alarme,"treeview_alarme");
afficher_alarme(treeview);
}


void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *pInfo;
utilisateur u;
int c;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
u.id=atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
u.role = gtk_combo_box_get_active(GTK_COMBO_BOX(mod2))+1;
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(mod3)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(mod4)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(mod5)));
strcpy(u.password,gtk_entry_get_text(GTK_ENTRY(mod7)));
u.nv = gtk_combo_box_get_active(GTK_COMBO_BOX(mod6))+1;
modifier_utilisateur(u,"utilisateur.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur modifié avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod_erreur_id, *pInfo;
utilisateur p;
int a=0;
char ch[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod_erreur_id=lookup_widget(objet,"mod_erreur_id");
int id = atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));

gtk_widget_hide(mod_erreur_id);

if(strcmp(gtk_entry_get_text(GTK_ENTRY(mod1)),"")==0){
gtk_widget_show(mod_erreur_id);

}else {
f = fopen("utilisateur.txt","r");
if(f!=NULL){
while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
		if(p.id==id){
			a=1;
			break;
                 }
	}
fclose(f);
}
if(a==1){
gtk_combo_box_set_active(GTK_COMBO_BOX(mod2),p.role-1);
gtk_entry_set_text(GTK_ENTRY(mod3),p.prenom);
gtk_entry_set_text(GTK_ENTRY(mod4),p.nom);
gtk_entry_set_text(GTK_ENTRY(mod5),p.email);
gtk_entry_set_text(GTK_ENTRY(mod7),p.password);
gtk_combo_box_set_active(GTK_COMBO_BOX(mod6),p.nv-1);
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Utilisateur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}}
}


void
on_treeview_utilisateur_row_activated  (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gint id;
	utilisateur u;
	GtkWidget *pInfo;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	u.id=id;
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer cet utilisateur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer_utilisateur(u,"utilisateur.txt");
	afficher_utilisateur(treeview,"utilisateur.txt");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}
}


void
on_button_af_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af_utilisateur;


af_utilisateur=lookup_widget(objet,"af_utilisateur");

gtk_widget_destroy(af_utilisateur);
af_utilisateur=lookup_widget(objet,"af_utilisateur");
af_utilisateur=create_af_utilisateur();

gtk_widget_show(af_utilisateur);

treeview=lookup_widget(af_utilisateur,"treeview_utilisateur");

afficher_utilisateur(treeview,"utilisateur.txt");
}


void
on_button_aj_clicked                   (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *aj5, *aj6, *aj7, *h, *f;
GtkWidget *aj_erreur_prenom, *aj_erreur_nom, *aj_erreur_role, *aj_erreur_email, *aj_erreur_password;
GtkCalendar *ajc;
utilisateur u;
int pass = 1;
guint day, month, year;
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
ajc=lookup_widget(objet,"ajc");
h=lookup_widget(objet,"h");
f=lookup_widget(objet,"f");
aj4=lookup_widget(objet,"aj4");
aj5=lookup_widget(objet,"aj5");
aj6=lookup_widget(objet,"aj6");
aj7 = lookup_widget(objet,"aj7");

aj_erreur_prenom = lookup_widget(objet,"aj_erreur_prenom");
aj_erreur_nom = lookup_widget(objet,"aj_erreur_nom");
aj_erreur_role = lookup_widget(objet,"aj_erreur_role");
aj_erreur_email = lookup_widget(objet,"aj_erreur_email");
aj_erreur_password = lookup_widget(objet,"aj_erreur_password");


gtk_widget_hide(aj_erreur_prenom);
gtk_widget_hide(aj_erreur_nom);
gtk_widget_hide(aj_erreur_role);
gtk_widget_hide(aj_erreur_email);
gtk_widget_hide(aj_erreur_password);

u.id=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aj1));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(aj3)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(aj4)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(aj5)));
strcpy(u.password,gtk_entry_get_text(GTK_ENTRY(aj7)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(h))?0:1;
gtk_calendar_get_date(GTK_CALENDAR(ajc), &day, &month, &year);
u.d.j=year;
u.d.m=month+1;
u.d.a=day;
u.role = gtk_combo_box_get_active(GTK_COMBO_BOX(aj2))+1;
u.nv = u.role==6?gtk_combo_box_get_active(GTK_COMBO_BOX(aj6))+1:0;
if(strcmp(u.prenom,"")==0){
gtk_widget_show(aj_erreur_prenom);
pass = 0;
} 
if(strcmp(u.nom,"")==0){
gtk_widget_show(aj_erreur_nom);
pass = 0;
} 
if(strcmp(u.email,"")==0){
gtk_widget_show(aj_erreur_email);
pass = 0;
} 
if(strcmp(u.password,"")==0){
gtk_widget_show(aj_erreur_password);
pass = 0;
} 
if(gtk_combo_box_get_active(GTK_COMBO_BOX(aj2))<0){
gtk_widget_show(aj_erreur_role);
pass = 0;
}
if(pass == 1){
ajouter_utilisateur(u,"utilisateur.txt");
}
}


void
on_button5_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *recherche, *dashboard_utilisateur;


dashboard_utilisateur=lookup_widget(objet,"dashboard_utilisateur");

gtk_widget_hide(dashboard_utilisateur);
recherche=lookup_widget(objet,"recherche");
recherche=create_recherche();

gtk_widget_show(recherche);
}


void
on_chercher_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *r1, *r2, *r3, *r4, *r5, *r6, *r7, *r8, *rechercher_erreur_id, *pInfo;
char date_naissance[20], sexe[20], role[30], niveau[20];
r1=lookup_widget(objet,"r1");
r2=lookup_widget(objet,"r2");
r3=lookup_widget(objet,"r3");
r4=lookup_widget(objet,"r4");
r5=lookup_widget(objet,"r5");
r6=lookup_widget(objet,"r6");
r7=lookup_widget(objet,"r7");
r8=lookup_widget(objet,"r8");
rechercher_erreur_id=lookup_widget(objet,"rechercher_erreur_id");

gtk_widget_hide(rechercher_erreur_id);

if(strcmp(gtk_entry_get_text(GTK_ENTRY(r1)),"")==0){
	gtk_widget_show(rechercher_erreur_id);
} else {
int id = atoi(gtk_entry_get_text(GTK_ENTRY(r1)));
utilisateur p = chercher_utilisateur(id,"utilisateur.txt");
if (p.id==-1){
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"ID introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}
else{
sprintf(role,p.role==1?"Admin":p.role==2?"Technicien":p.role==3?"Responsable réclamations":p.role==4?"Agent de foyer":p.role==5?"Agent de restaurant":"Etudiant");
gtk_label_set_text(GTK_LABEL(r2),role);
gtk_label_set_text(GTK_LABEL(r3),p.prenom);
gtk_label_set_text(GTK_LABEL(r4),p.nom);
gtk_label_set_text(GTK_LABEL(r5),p.email);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
gtk_label_set_text(GTK_LABEL(r6),sexe);
sprintf(date_naissance,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
gtk_label_set_text(GTK_LABEL(r7),date_naissance);
sprintf(niveau,p.role==6?(p.nv==1?"1ère année":"%déme année"):"Employé",p.nv);
gtk_label_set_text(GTK_LABEL(r8),niveau);
}}
}




void
on_button_alarme_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *alarme;
alarme=lookup_widget(objet,"alarme");
gtk_widget_destroy(alarme);
alarme=lookup_widget(objet,"alarme");
alarme=create_alarme();
gtk_widget_show(alarme);
treeview=lookup_widget(alarme,"treeview_alarme");
afficher_alarme(treeview);
}


void
on_button_deconnecter_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *login;

login = create_login();
dashboard_utilisateur = lookup_widget(button,"dashboard_utilisateur");
gtk_widget_hide(dashboard_utilisateur);
gtk_widget_show(login);
}


void
on_button_mod_retour_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *mod_utilisateur;

dashboard_utilisateur = create_dashboard_utilisateur();
mod_utilisateur = lookup_widget(button,"mod_utilisateur");
gtk_widget_hide(mod_utilisateur);
gtk_widget_show(dashboard_utilisateur);
}


void
on_button_af_retour_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *af_utilisateur;

dashboard_utilisateur = create_dashboard_utilisateur();
af_utilisateur = lookup_widget(button,"af_utilisateur");
gtk_widget_hide(af_utilisateur);
gtk_widget_show(dashboard_utilisateur);
}


void
on_button_ajout_retour_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *aj_utilisateur;

dashboard_utilisateur = create_dashboard_utilisateur();
aj_utilisateur = lookup_widget(button,"aj_utilisateur");
gtk_widget_hide(aj_utilisateur);
gtk_widget_show(dashboard_utilisateur);
}


void
on_button_rechercher_retour_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *recherche;

dashboard_utilisateur = create_dashboard_utilisateur();
recherche = lookup_widget(button,"recherche");
gtk_widget_hide(recherche);
gtk_widget_show(dashboard_utilisateur);
}


void
on_button_alarme_retour_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *dashboard_utilisateur, *alarme;

dashboard_utilisateur = create_dashboard_utilisateur();
alarme = lookup_widget(button,"alarme");
gtk_widget_hide(alarme);
gtk_widget_show(dashboard_utilisateur);
}


void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
char email[50];
char password[50];
int pass = 0;

GtkWidget *entry2, *entry1, *label45, *login, *menu;

login = lookup_widget(button,"login");
entry1 = lookup_widget(login,"entry1");
entry2 = lookup_widget(login,"entry2");
label45 = lookup_widget(login,"label45");

strcpy(email,gtk_entry_get_text(GTK_ENTRY(entry1)));
strcpy(password,gtk_entry_get_text(GTK_ENTRY(entry2)));
pass = utilisateur_login(email, password, "utilisateur.txt");

if(pass == 1 && verification_bot == 1){
menu = create_menu();
gtk_widget_hide(login);
gtk_widget_show(menu);
}else{
gtk_widget_show(label45);
}
}


void
on_capteurs_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_stock_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_reclamation_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_agent_de_foyer_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_nutrisioniste_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton)){
		verification_bot = 1;
	} else {
		verification_bot = 0;
	}
}


void
on_utilisateur_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *menu, *dashboard_utilisateur;

	menu = lookup_widget(button,"menu");
	dashboard_utilisateur = create_dashboard_utilisateur();
	gtk_widget_show(dashboard_utilisateur);
	gtk_widget_hide(menu);
}


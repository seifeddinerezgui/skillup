#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilisateur.h"
#include "callbacks.h"
#include <gtk/gtk.h>

enum
{
	ID,
	ROLE,
	NOM_COMPLET,
	EMAIL,
	SEXE,
	DATE_NAISSANCE,
	NIVEAU,
	COLUMNS
};
enum
{
	JOUR,
	HEURE,
	NUM_CAPTEUR,
	TYPE_CAPTEUR,
	COLUMNS1
};

void ajouter_utilisateur(utilisateur u, char *fname){
GtkWidget *pQuestion, *pInfo;
FILE *f;
int b=0;
gpointer user_data;
utilisateur p;
f=fopen(fname,"a+");
if(f!=NULL)
{	while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email, p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{	
		if(u.id==p.id)
			b++;
	}
	if(b==0){
	u.nv=u.role==6?u.nv:0;
	fprintf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",u.id,u.role,u.prenom,u.nom,u.email,u.password,u.sexe,u.d.j,u.d.m,u.d.a,u.nv);
	pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur ajouté avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pQuestion);
	break;
	}
	}
	if(b!=0){
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Utilisateur déja existant !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	}
	fclose(f);
}
}

void modifier_utilisateur(utilisateur u, char *fname){
utilisateur p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
		if(p.id!=u.id)
			fprintf(g,"%d %d %s %s %s %s %d %d %d %d %d\n",p.id,p.role,p.prenom,p.nom,p.email,p.password,p.sexe,p.d.j,p.d.m,p.d.a,p.nv);
		else
			fprintf(g,"%d %d %s %s %s %s %d %d %d %d %d\n",p.id,u.role,u.prenom,u.nom,u.email,u.password,p.sexe,p.d.j,p.d.m,p.d.a,u.nv);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur modifié avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

void afficher_utilisateur(GtkWidget *liste, char *fname)
{
utilisateur p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar date_naissance[50], nom_complet[50], role[50], niveau[50], sexe[10];
FILE *f;


store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" ID", renderer,"text",ID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);
	
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Role", renderer,"text",ROLE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Nom complet", renderer,"text",NOM_COMPLET, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_resizable(column,TRUE);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Email", renderer,"text",EMAIL, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Sexe", renderer,"text",SEXE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Date de naissance", renderer,"text",DATE_NAISSANCE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);

	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes(" Niveau", renderer,"text",NIVEAU, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	gtk_tree_view_column_set_expand(column,TRUE);




store=gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
f=fopen(fname,"r");
if(f!=NULL)

{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
sprintf(role,p.role==1?"Admin":p.role==2?"Technicien":p.role==3?"Responsable réclamations":p.role==4?"Agent de foyer":p.role==5?"Agent de restaurant":"Etudiant");
sprintf(date_naissance,"%d/%d/%d",p.d.j,p.d.m,p.d.a);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
sprintf(nom_complet,"%s %s",p.prenom, p.nom);
sprintf(niveau,p.role==6?(p.nv==1?"1ère année":"%déme année"):"Employé",p.nv);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,ID,p.id,ROLE,role,NOM_COMPLET,nom_complet,EMAIL,p.email,SEXE,sexe,DATE_NAISSANCE,date_naissance,NIVEAU,niveau,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
gtk_tree_view_set_reorderable(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_search_column(GTK_TREE_VIEW(liste),2);
gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(liste),GTK_TREE_VIEW_GRID_LINES_BOTH);
}

void supprimer_utilisateur(utilisateur u, char *fname)
{
utilisateur p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
		if(p.id!=u.id)
			fprintf(g,"%d %d %s %s %s %s %d %d %d %d %d\n",p.id,p.role,p.prenom,p.nom,p.email,p.password,p.sexe,p.d.j,p.d.m,p.d.a,p.nv);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur supprimé avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}



utilisateur chercher_utilisateur(int id, char *fname){
utilisateur p, e;
FILE *f;
f=fopen(fname,"r");
if(f!=NULL){
	while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
		if(p.id==id)
			return p;
	}
	fclose(f);
}
e.id=-1;
return e;
}

int utilisateur_login(char email[], char password[], char *fname){
FILE *f;
utilisateur p;
int result = 0;
f=fopen(fname,"r");
if(f!=NULL){
	while(fscanf(f,"%d %d %s %s %s %s %d %d %d %d %d\n",&(p.id),&(p.role),p.prenom,p.nom,p.email,p.password,&(p.sexe),&(p.d.j),&(p.d.m),&(p.d.a),&(p.nv))!=EOF)
	{
		if(strcmp(p.email,email)==0 && strcmp(p.password,password)==0)
			result = 1;
	}
	fclose(f);
}
return result;

}

void afficher_alarme(GtkWidget *liste)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;

GtkListStore *store;
	int j;
	int h;
	int cap;
	int val;
alarme c;
char heure[50];
store =NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",JOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Heure",renderer,"text",HEURE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Numero de capteur",renderer,"text",NUM_CAPTEUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("type de capteur",renderer,"text",TYPE_CAPTEUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(COLUMNS1,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING);
f=fopen("mouvement.txt","r");
if(f==NULL)
{
return;
}
else
{
f=fopen("mouvement.txt","r");
	while(fscanf(f,"%d %d %d %d\n",&c.j,&c.h,&c.cap,&c.val)!=EOF)
	{
	if(c.val==1 && (c.h <7 || c.h==24))
	{
sprintf(heure,"%d:00H",c.h);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,JOUR,c.j,HEURE,heure,NUM_CAPTEUR,c.cap,TYPE_CAPTEUR,"mouvement", -1);
}
}
fclose(f);
}

f=fopen("fumee.txt","r");
if(f==NULL)
{
return;
}
else
{
f=fopen("fumee.txt","r");
	while(fscanf(f,"%d %d %d %d\n",&c.j,&c.h,&c.cap,&c.val)!=EOF)
	{
	if(c.val==1 && (c.h <7 || c.h==24))
	{
sprintf(heure,"%d:00H",c.h);
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,JOUR,c.j,HEURE,heure,NUM_CAPTEUR,c.cap,TYPE_CAPTEUR,"fumee", -1);
}
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}


void afficher_fume(GtkWidget *liste)
{
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;

GtkListStore *store;
	int j;
	int h;
	int cap;
	int val;
alarme c;
store =NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",JOUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Heure",renderer,"text",HEURE,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

renderer=gtk_cell_renderer_text_new ();
column=gtk_tree_view_column_new_with_attributes("Numero de capteur",renderer,"text",NUM_CAPTEUR,NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


}

store=gtk_list_store_new(COLUMNS1,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
f=fopen("fumee.txt","r");
if(f==NULL)
{
return;
}
else
{
f=fopen("fumee.txt","r");
	while(fscanf(f,"%d %d %d %d\n",&c.j,&c.h,&c.cap,&c.val)!=EOF)
	{
	if(c.val==1)
	{
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,JOUR,c.j,HEURE,c.h,NUM_CAPTEUR,c.cap, -1);
}
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}



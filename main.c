#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Max_size 120

/*****Menu*****/

void menu(){
                        puts("\n\n                        Services : \n\n ");
                        puts("                             1: Mise a jour des informations d’un compte existant\n");
                        puts("                             2: Afficher et gerer les transactions bancaires\n");
                        puts("                             3: Supprimer un compte existant\n");
                        puts("                             4: Afficher les details d’un compte existant\n");
                        puts("                             5: Afficher la liste des clients\n");
                        puts("                             6: Paiement de factures\n");
                        puts("                             7: Retrouver mon compte perdu\n");
                        puts("                             8: Modifier votre code secret \n");
                        puts("                             0: Quitter\n\n");
                    }
/*****Fin menu *****/

/*****Structures*****/

typedef struct{
int mois,jour,annee;
}date;

typedef struct depots {
    date date_depot;
    double montant_depot;
} depots;

typedef struct retraits {
    date date_retrait;
    double montant_retrait;
} retraits;

typedef struct{
char nom_facture[120];
double montant;
}facture;

typedef struct {
char nom[120],prenom[160] , code[12];
date naissance;
unsigned long numero_compte;
unsigned long telephone;
double solde;
depots liste_depots[Max_size];
int nb_depots;
retraits liste_retraits[Max_size];
int nb_retraits;
facture factures[Max_size];
int nb_factures;
}personne;

/*****Fin structures *****/

/*****Nouveau compte : partie 1*****/

int Existe(unsigned long numero_compte,char *nomfichier){
FILE *f=fopen(nomfichier,"rb");
personne p;
 int m=fread(&p,sizeof(personne),1,f);
                while( m>0){
                        if(p.numero_compte==numero_compte){
                                                              fclose(f);
                                                              return 1;
                                                            }
                    m=fread(&p,sizeof(personne),1,f);
                }
                fclose(f);
                return 0;
}

personne RechercherPersonne(unsigned long numero_compte){
FILE *f=fopen("account.bin","rb");
    personne p;
 int m=fread(&p,sizeof(personne),1,f);
                while( m>0){
                        if(p.numero_compte==numero_compte){
                                                             fclose(f);
                                                             return p;
                                                            }
                    m=fread(&p,sizeof(personne),1,f);
                }
                fclose(f);
 }

void new_account(void){
 personne p;
 printf("\n    ******************************Fiche d'inscription***************************************   \n\n");
 printf("               Nom : ");
 scanf("%s",&p.nom);
 puts("\n");
 printf("               Prenom : ");
 scanf("%s",&p.prenom);
 puts("\n");
 printf("               Entrer votre code secret : \n\n");
 puts("Conseils: entrez entre 8 et 12 caracteres constitues de lettres et de chiffres ...\n");
scanf("%s",&p.code);
puts("\n");
 printf("               Anniversaire : \n\n");
 date d;
 printf("                   jour : ");
 scanf("%d",&d.jour);
puts("\n");
 puts("\n");
 printf("                   mois : ");
 scanf("%d",&d.mois);
 puts("\n");
 printf("                   Annee : ");
 scanf("%d",&d.annee);
 puts("\n");
 p.naissance=d;
 printf("               Numero de Telephone : ");
 scanf("%lu",&p.telephone);
 puts("\n");
 printf("               Numero du compte : ");
 scanf("%lu",&p.numero_compte);
 unsigned long n=Existe(p.numero_compte,"account.bin");
 while(n){
    puts("\n            Erreur, ce numero de compte existe deja , SVP entrez un autre :  ");
    n=Existe(p.numero_compte,"account.bin");
    scanf("%lu",&p.numero_compte);
 }
 puts("\n");
//Transactions
 p.nb_depots=p.nb_retraits=0;p.nb_factures=0;
 p.solde=0;
//Ajout dans la base de donnée
FILE *f = fopen("account.bin","ab+");
fwrite(&p,sizeof(personne),1,f);
fclose(f);
puts("\n\n          La souscription a ete effectuee, merci pour la confiance!\n\n");
}
/*****Fin New account *****/

/*****Infos d'un compte et modification : partie 2*****/

void menu_modification(void){
puts("\n\n------------------------------->>>>>Mise a jour du compte>>>>>--------------------------------------------------------\n\n");
puts("          1: Modifier le nom \n");
puts("          2: Modifier le prenom \n");
puts("          3: Modifier le telephone \n");
puts("          4: Modifier le numero du compte \n");
puts("          5: Rectifier le solde \n");
puts("          6: Modifier la date de naissance \n");
puts("          0: Quitter \n");
                        }

void Infos_compte(unsigned long numero_compte,char* nomfichier,int n){
        FILE *f=fopen(nomfichier,"rb+");
        unsigned long num;
        personne p;
        int m=fread(&p,sizeof(personne),1,f);
        while( (m>0) && (p.numero_compte!=numero_compte))
             m=fread(&p,sizeof(personne),1,f);
        if(m<=0){
            puts ("\n     Ce compte est inexistant, svp entrez un numero de compte valide ! ");
        }

        else{
            printf("                Nom : %s\n\n",&p.nom);
            printf("                Prenom : %s\n\n",&p.prenom);
            printf("                Anniversaire : %d/%d/%d\n\n",p.naissance.jour,p.naissance.mois,p.naissance.annee);
            printf("                Telephone : %lu\n\n",p.telephone);
            printf("                Numero du compte : %lu\n\n",p.numero_compte);
            printf("                Solde disponible : %lf",p.solde);

        //Modification des parametres du compte
if(n!=2){       int test;
                printf("\n\nVoulez-vous modifier un parametre du compte ? Tapez 1 si oui ou toute autre numero sinon : ");
                scanf("%d",&test);
                if(test==1){
                    puts("----------------------------->>>Modification de parametre du compte<<<------------------------------\n\n");
                    int choice;
                    do{
                            if(!test){
                                menu_modification();
                                test=1;}

                            else{
                             menu_modification();
                             puts(" \n      SVP, veuillez faire un choix valide !");
                             }
                            scanf("%d",&choice);
                    }while(choice<0 || choice>6);

                    switch(choice){
                                        case 1: puts("              Entrez le nouveau nom :  ");
                                                scanf("%s",&p.nom);
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n                Modifie avec succes !\n\n");
                                                break;


                                        case 2:puts("               Entrez le nouveau Prenom :  ");
                                                scanf("%s",&p.prenom);
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n            Modifie avec succes !\n\n");
                                                break;


                                        case 3:puts("               Entrez le nouveau numero de telephone:  ");
                                                scanf("%lu",&p.telephone);
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n            Modifie avec succes !\n\n");
                                               break;


                                        case 4:puts("               Entrez le nouveau numero de compte :  ");
                                                scanf("%lu",&p.numero_compte);
                                                if(Existe(p.numero_compte,"account.bin"))
                                                {
                                                    puts("\n\n        Erreur, ce numero appartient a un autre compte !");
                                                    break;
                                                }
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n            Modifie avec succes !\n\n");
                                                break;


                                        case 5:puts("               Entrez le nouveau Solde :  ");
                                                scanf("%lf",&p.solde);
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n            Modifie avec succes !\n\n");
                                                break;


                                        case 6:puts("               Entrez la nouvelle date de naissance : \n ");
                                                printf("                        Jour : ");
                                                scanf("%d",&p.naissance.jour);
                                                printf("                        Mois : ");
                                                scanf("%d",&p.naissance.mois);
                                                printf("                        Annee : ");
                                                scanf("%d",&p.naissance.annee);
                                                fseek(f,-sizeof(personne),SEEK_CUR);
                                                fwrite(&p,sizeof(personne),1,f);
                                                printf("\n\n            Modifie avec succes !\n\n");
                                                break;

                                    case 0: break;
                                    default :
                                        puts("\n                    Veuillez faire un choix un valide ! \n");
                                        break;
                    }
                    }
        }
        }
        fclose(f);
}
/*****Fin partie 2*****/

/*****Partie 3: Afficher et gerer les transactions*****/

void menu_transaction(void){
puts("----------Bienvenue sur le service des transactions----------\n\n");
puts("          1: Afficher les depots effectues \n");
puts("          2: Afficher les retraits effectues \n");
puts("          3: Faire un nouveau depot \n");
puts("          4: Faire un nouveau retrait \n");
puts("          0: Quitter \n");
}

//Afficher les depots
void afficherListedepots(depots liste[Max_size],personne *p)
{
if (p->nb_depots!=0){
int i=1;
while(i<=p->nb_depots)
{printf("               Depot numero %d :---------------------------------------------------------------\n",i);
printf("                Date de depot: %2d/%2d/%4d\n", liste[i].date_depot.jour,liste[i].date_depot.mois,liste[i].date_depot.annee);
printf("                Montant : %lf\n\n",liste[i].montant_depot);
i++;
}
}else{
puts("\n                Aucun depot effectue   ! \n\n");}
}

//Afficher les retraits

void afficherListeretraits(retraits liste[Max_size],personne *p)
{ if (p->nb_retraits!=0){
int i=1;
while(i<=p->nb_retraits)
{
printf("                Retrait numero %d :---------------------------------------------------------------\n",i);
printf("                Date de retrait: %2d/%2d/%4d\n",liste[i].date_retrait.jour,liste[i].date_retrait.mois,liste[i].date_retrait.annee);
printf("                Montant : %lf\n\n",liste[i].montant_retrait);
i++;
}
}else{
puts("\n                Aucun retrait effectue !\n\n     ");}
}

//Fonction pour effectuer un depot

void Executer_Depot(personne* p, double montant) {
    //Mise a jour du solde
     p->solde+=montant;
    depots nouveau_depot;
   // Initialisez les valeurs de nouveau_depot
       printf("             Entrer la date de depot :  \n");
       printf("             Jour :  ");scanf("%2d",&nouveau_depot.date_depot.jour);
       printf("             Mois :  ");scanf("%2d",&nouveau_depot.date_depot.mois);
       printf("             Annee : ");scanf("%4d",&nouveau_depot.date_depot.annee);
       nouveau_depot.montant_depot=montant;
    // Ajoutez nouveau_depot à la liste des dépôts
p->nb_depots++;
p->liste_depots[p->nb_depots]=nouveau_depot;
}

// Fonction pour effectuer un nouveau retrait

void ExecuterRetrait(personne* p,double montant) {
    if(p->solde>=montant){
        retraits nouveau_retrait;
    // Mettez à jour le solde de la personne
        p->solde-= montant;
        // Initialisez les valeurs de nouveau_retrait a la date actuelle
       printf("                Entrer la date du retrait :  \n");
       printf("                 Jour :  ");scanf("%d",&nouveau_retrait.date_retrait.jour);
       printf("                 Mois :  ");scanf("%d",&nouveau_retrait.date_retrait.mois);
       printf("                 Annee : ");scanf("%d",&nouveau_retrait.date_retrait.annee);
       nouveau_retrait.montant_retrait=montant;

        // Ajoutez nouveau_retrait à la liste des retraits
p->nb_retraits++;
p->liste_retraits[p->nb_retraits]=nouveau_retrait;
    } else
        printf("\n\n            Solde insuffisant pour effectuer le retrait.\n");

}

void faire_transaction(double montant, unsigned long numero_compte,int n){
         FILE *f=fopen("account.bin","rb+");
         rewind(f);
         personne p;
        if(f!=NULL){
                int m=fread(&p,sizeof(personne),1,f);
                while( (m>0) && (p.numero_compte!=numero_compte))
                     m=fread(&p,sizeof(personne),1,f);
                if(m<=0){
                    puts ("\n   Ce compte est inexistant, svp entrez un numero de compte valide ! \n\n");
                }
                else{

                    if(n==3){   Executer_Depot(&p,montant);
                                fseek(f,-sizeof(personne),SEEK_CUR);
                                fwrite(&p,sizeof(personne),1,f);
                                fclose(f);
                                }

                    if(n==4){   ExecuterRetrait(&p,montant);
                                fseek(f,-sizeof(personne),SEEK_CUR);
                                fwrite(&p,sizeof(personne),1,f);fclose(f);}
                    }

 }else
    puts("\n        Erreur d'ouverture du fichier   !\n");
}

void programme_principale_3(void){
                int choice;
                int test=0;
                do{
                        if(!test){
                            menu_transaction();
                            test=1;}
                        else{
                         menu_transaction();
                         puts(" \nSVP, veuillez faire un choix valide !");
                         }
                        scanf("%d",&choice);

                }while(choice<0 || choice>4);

        switch(choice){
                        case 1:{
                                FILE *f=fopen("account.bin","rb+");
                                personne p;
                                unsigned long numero_compte;
                                printf("        Entrer le numero de compte :  ");scanf("%lu",&numero_compte);
                                if(f!=NULL){
                                        int m=fread(&p,sizeof(personne),1,f);
                                        while( (m>0) && (p.numero_compte!=numero_compte))
                                             m=fread(&p,sizeof(personne),1,f);
                                        if(m<=0){
                                            puts ("\n       Ce compte est inexistant, svp entrez un numero de compte valide ! ");
                                        }
                                        else{       char code[13];
                                                printf("\n              Taper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\n                Erreur, code incorrect !");
                                                break;
                                            }
                                            afficherListedepots(p.liste_depots,&p);
                                        }fclose(f);}else{puts("\n           Erreur d'ouverture du fichier!");}
                                        break;}

                        case 2:{
                                FILE *f=fopen("account.bin","rb+");
                                personne p;
                                unsigned long numero_compte;
                                printf("Entrez le numero de compte :   ");scanf("%lu",&numero_compte);
                                if(f!=NULL){
                                        int m=fread(&p,sizeof(personne),1,f);
                                        while( (m>0) && (p.numero_compte!=numero_compte))
                                             m=fread(&p,sizeof(personne),1,f);
                                        if(m<=0){
                                            puts ("\nCe compte est inexistant, svp entrez un numero de compte valide ! ");
                                        }
                                        else{char code[13];
                                            printf("\n        Taper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\n        Erreur, code incorrect !");
                                                break;
                                            }
                                           afficherListeretraits(p.liste_retraits,&p);
                                        }fclose(f);}
                                        else{puts("\n       Erreur d'ouverture du fichier !");}
                                        break;}

                    case 3:{ double montant; unsigned long numero_compte;
                             printf("           Entrez le montant a deposer :  "); scanf("%lf",&montant);
                             printf("           Entrez le numero de compte :   "); scanf("%lu",&numero_compte);
                             faire_transaction(montant,numero_compte,3);
                             puts("\n           Depot effectue avec succes, merci pour la confiance\n");
                             break;
                            }
                    case 4 :{ double montant; unsigned long numero_compte;
                             printf("           Entrez le montant a retirer :  "); scanf("%lf",&montant);
                             printf("           Entrez le numero de compte :   "); scanf("%lu",&numero_compte);
                             if (Existe(numero_compte,"account.bin")){
                                personne p=RechercherPersonne(numero_compte);
                                    char code[13];
                                            printf("\n          Taper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\nErreur, code incorrect !");
                                                break;
                                                        }
                                            }
                             faire_transaction(montant,numero_compte,4);
                             puts("\n           Merci pour la confiance\n");
                             break;
                            }
                    case 0:break;
                    default : { printf("\n         Veuillez SVP faire un choix valide ! ");
                                }
                        }

}

/*****Fin Partie 3*****/

/**Partie 4**/

int supprimerPersonne (unsigned long num,char* nomfichier) {
int m;
personne p;
FILE *temp,*f,*corb=fopen("corbeille.bin","ab+");
 if ((temp =fopen("temp.bin","wb")) != NULL &&
(f =fopen(nomfichier,"rb"))!= NULL){
m = fread(&p,sizeof(personne),1,f);
while(m>0){
if(p.numero_compte!=num)
fwrite(&p,sizeof(personne),1,temp);
else
    fwrite(&p,sizeof(personne),1,corb);
m=fread(&p,sizeof(personne),1,f);
}
fclose(temp);
fclose(f);
fclose(corb);
remove("account.bin");
rename("temp.bin","account.bin");
return 0;
 }
 else{
puts("\n            Erreur en ouvrant les fichier \n");
return 0;
 }
}

//Retrouver un compte

int supprimerPersonne_v2 (unsigned long num,char* nomfichier) {
int m;
personne p;
FILE *temp,*f;
 if ((temp =fopen("temp.bin","wb")) != NULL &&
(f =fopen(nomfichier,"rb"))!= NULL){
m = fread(&p,sizeof(personne),1,f);
while(m>0){
if(p.numero_compte!=num)
fwrite(&p,sizeof(personne),1,temp);
m=fread(&p,sizeof(personne),1,f);
}
fclose(temp);
fclose(f);
remove("corbeille.bin");
rename("temp.bin","corbeille.bin");
return 0;
}
 else{
        puts("\n            Erreur en ouvrant les fichiers ! \n");
        return 0;
    }
}

int RetrouverCompte(unsigned long num){
FILE *f=fopen("corbeille.bin","rb");
personne p;
if(f!=NULL){
    if(Existe(num,"corbeille.bin")){
        p=RechercherPersonne(num);
        Infos_compte(num,"corbeille.bin",2);
        int restaurer;
        printf("\n              Voullez vous restaurer ce compte? appuyer 1 si oui..  :  ");
        scanf("%d",&restaurer);
        if(!restaurer)
            return 0;
        FILE *fich=fopen("account.bin","ab+");
        fwrite(&p,sizeof(personne),1,fich);
        fclose(fich);
         fclose(f);
        supprimerPersonne_v2(num,"corbeille.bin");
        puts("\n                Compte restaure avec succes ! ");
        return 0;}
else{
    puts("\nCe           compte ne peut pas etre restaure !");
    return 0;
    }
}
puts("\n                Erreur d'ouverture de fichier !\n");
return 0;
}

void programme_principal(){
int choix ;
do{
    menu();
    scanf("%d",&choix);
 switch(choix){

                case 1 :{
                        puts("Donner le numero de votre compte : \n\n");
                        unsigned long numero;
                        scanf("%lu",&numero);
                        if (Existe(numero,"account.bin")){
                                personne p=RechercherPersonne(numero);
                                    char code[13];
                                            printf("\nTaper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\nErreur, code incorrect !");
                                                break;
                                                        }
                                            }
                        Infos_compte(numero,"account.bin",1);
                        puts("\n\n       ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                        break;}


                case 2: {programme_principale_3();
                        puts("\n\n       ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                        break;}

                case 3: {unsigned long num;
                        printf("Donner le numero de compte :  ");scanf("%lu",&num);
                        if (Existe(num,"account.bin")){
                                personne p=RechercherPersonne(num);
                                    char code[13];
                                            printf("\nTaper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\nErreur, code incorrect !");
                                                break;
                                                        }
                                            }
                                supprimerPersonne(num,"account.bin");
                                puts("\nCompte supprime avec succes !\n");
                                puts("\nVous pourrez au besoin retrouver votre compte!\n\n");

                       puts(" \n\n      ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                         break;}


                case 4:  {FILE *f = fopen("account.bin","rb");
                            personne p;
                           int m= fread(&p,sizeof(personne),1,f);
                           unsigned long numero;
                           printf("\nDonner le numero du compte :  ");scanf("%lu",&numero);
                          if (Existe(numero,"account.bin")){
                                personne p=RechercherPersonne(numero);
                                    char code[13];
                                            printf("\nTaper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\nErreur, code incorrect !");
                                                break;
                                                        }
                                            }
                            while(m>0){
                                if(p.numero_compte==numero){
                                    printf("\n\n-------------Infos du compte-------------------------\n\n");
                                    printf("Nom du detenteur : %s\n\n",p.nom);
                                    printf("Prenom du detenteur : %s\n\n",p.prenom);
                                    printf("Date de naissaine : %d/%d/%d\n\n",p.naissance.jour,p.naissance.mois,p.naissance.annee);
                                    printf("Tel : %lu\n\n",p.telephone);
                                    printf("Solde disponible : %lf\n\n",p.solde);
                                }
                                m=fread(&p,sizeof(personne),1,f);
                            }

                            fclose(f);
                            puts("\n\n ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                         break;}


                case 5 :{
                          FILE *f = fopen("account.bin","rb");
                            personne p;
                           int m= fread(&p,sizeof(personne),1,f);
                           int i=1;
                           printf("\n\n*********---------------------<<<<<LISTE DES CLIENTS>>>>>----------------------------------*********\n\n");
                            while(m>0){
                                    printf("Client numero : %d\n\n",i);
                                    printf(" Nom :%s \n\n",p.nom);
                                    printf(" Prenom : %s  \n\n",p.prenom);
                                    printf(" Date de naissance :%d/%d/%d   \n\n",p.naissance.jour,p.naissance.mois,p.naissance.annee);
                                    printf(" Tel : %lu      \n\n",p.telephone);
                                    printf(" Solde : %lf    \n",p.solde);
                                    puts("↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨↨\n");
                                    i++;
                                    m=fread(&p,sizeof(personne),1,f);
                                    }
                        fclose(f);
                        puts(" \n\n----------E-Bank,l'excellence a votre service---------- \n\n\n");
                         break;}


                case 6 :{
                        unsigned long numero;
                        char nom_fact[120];
                        double montant;
                        printf("                Entrer votre numero de compte :  "); scanf("%lu",&numero);
                        if (Existe(numero,"account.bin")){
                                personne p=RechercherPersonne(numero);
                                    char code[13];
                                            printf("\n              Taper votre code :  ");scanf("%s",code);
                                            if(strcmp(p.code,code)!=0){
                                                puts("\n            Erreur, code incorrect !");
                                                break;
                                                        }
                                            }
                        if(Existe(numero,"account.bin")){
                        facture nouvelle_facture;
                        nouvelle_facture.montant=montant;
                        printf("                Entrer le montant de la facture :  ");scanf("%lf",&montant);
                        printf("                Donner le type de facture :  ");scanf("%s",nouvelle_facture.nom_facture);
                        faire_transaction(montant,numero,4);
                        personne p=RechercherPersonne(numero);
                        p.nb_factures++;
                        p.factures[p.nb_factures]=nouvelle_facture;
                        }else
                        puts("\n                Ce compte n'existe pas!\n");
                        puts("\n\n ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                         break;}


            case 7: {puts("\n\n----------------------------Retrouver mon compte-----------------------------------------\n\n");
                    printf("                Donner le numero du compte :   ");
                    unsigned long num; scanf("%lu",&num);
                    RetrouverCompte(num);
                     puts("\n\n       ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                     break;}
            case 8:{puts("\n\n----------------------------Modifier votre code secret-----------------------------------------\n\n");
                    unsigned long numero_compte;
                    printf("\n\n                Entrez votre numero de compte : ");
                    scanf("%lu",&numero_compte);
                    printf("\n\n                Entrez votre ancien code secret :");
                    char code[13];
                    scanf("%s",&code);
                    personne p=RechercherPersonne(numero_compte);
                    if(!(strcmp(p.code,code)==0)){
                            puts("\n\n                Erreur,code incorrect !");
                            break;
                    }
                    puts("\n\n                Entrez le nouveau code : ");
                    scanf("%s",code);
                    puts("\n\n                Entrez de nouveau le nouveau code : ");
                    char code2[13];
                    scanf("%s",code2);
                    if(!(strcmp(code,code2)==0)){
                                    puts("\n\n              Erreur,les deux codes entres ne sont pas identiques !");
                                    break;
                                        }
                    strcpy(p.code,code2);
                    supprimerPersonne(numero_compte,"account.bin");
                    FILE *f=fopen("account.bin","ab+");
                    fwrite(&p,sizeof(personne),1,f);
                    fclose(f);
                    puts("\n\n              Votre code secret a ete modifie avec succes ! ");
                    puts("\n\n        ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                    break;
                    }

            case 0: break;

            default :{
                    printf("\n              Votre choix est invalide, veillez le revoir !");
                    puts(" \n\n       ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                    break;}
 }
}while(choix!=0);

}
/**********************Programme princiale******************************************/
int main()
{
int test;
do{
puts("\n\n      **************************************---<<<E-Bank>>>---**************************************\n\n");
puts("                  1:  Se connecter \n\n");
puts("                  2:  Creer un compte \n\n");
puts("                  0:  Quitter \n\n");
puts("\n\n Developpe  par Urie THIOMBIANO , contact : urie.thiombiano@ensi-uma.tn\n\n");

scanf("%d",&test);
switch(test){
                case 1 : {  unsigned long numero_compte; char code[13];
                            printf("\n\n              Entrez votre numero de compte:   ");scanf("%lu",&numero_compte);
                            printf("\n\n              Entrez votre numero de code secret:   ");scanf("%s",code);
                            personne p;
                            if(Existe(numero_compte,"account.bin")){
                                p=RechercherPersonne(numero_compte);
                                puts("\n\n      **************************************---<<<Bienvenue votre plateforme E-Bank>>>---**************************************\n\n");
                                printf("\n              Vous etes connecte en tant que : %s  %s",p.prenom,p.nom);
                                programme_principal();
                                break;
                            }}

                case 2 :{
                            new_account();
                            puts(" \n\n             ----------E-Bank,l'excellence a votre service---------- \n\n\n");
                            programme_principal();
                            break;
                        }

                case 0:{
                        printf("\n              Merci pour la visite ! Au revoir et a bientot sur nos services !\n\n");
                        puts("                  -------------------------------E-Bank,l'excellence a votre service--------------------------------\n\n\n");
                        break;
                        }

                default : {
                            puts("\n                Veuillez faire un choix valide SVP !\n");
                            break;
                            }
}
}while(test!=0);
}

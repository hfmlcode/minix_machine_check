#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Importation de notre librairie
#include <machine/machine_error.h>

int main(int argc, char ** argv) {


	if(argc!=2){
		printf("argument missing \n");
	}else{
		//Configuration du contrôle machine.
		int mc_was_inited = mc_init();
		int geterror = NOERROR;
	
		if(atoi(argv[1])==1){
			//Si la configuration est bien faite
			if (mc_was_inited == MCINITSUCCES) {

				//Initialisation du tableau partagé
			 	reporting_init();
		 
				//Gestion des erreurs
				mce_handler(&tab_reporting, 1);
	
		
			} else {
				printf(" Your CPU not support machine check  instruction \n");
			}
			printf("begin mchandle  !\n");
		}else{
			//Demande d'arrêt de la gestion des erreurs
			geterror = mce_handler(&tab_reporting, 0);
			
			//copie du contenu du tableau partagé dans le fichier /etc/mce/mce.log
			int logstat = log_report_info();
		
			//Libération de l'espace alloué au tableau.
			if (logstat == 1) release_addr_space();
			printf("end mchandle  !\n");
		}
	}
	return 0;
}

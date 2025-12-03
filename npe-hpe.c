/* Programme de décodage des codes erreurs retournés par les commutateurs HPE sur le serveur NPS

Fonctionnement :
Code erreur en décimal à convertir en binaire sur 32 bits

Découpage : 4 bits (bourrage) - 4 bits/4 bits/8 bits (interface x/y/z) - 12 bits (id vlan)

Suivi des mises à jour

1.0 - 10/04/2024 : création

*/

#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>
int main(){
  
  int tab[32], code, i;  
  
  printf("******************************************************");
  printf("\n\tProgramme de decodage des codes erreurs \n\tretournes par un commutateur HPE \n\tsur le serveur NPS");
  printf("\n******************************************************\n\n");
  
  printf("Code erreur : ");  
  scanf("%d",&code);  
  
  //remplissage du tableau avec uniquement des 0
  for(i=0; i<32; i++)
  {
  	tab[i]=0;	
  }
  
  for(i=0; code > 0; i++)  
  {  
    tab[i] = code%2;  
    code = code/2;  
  } 
  
  
  printf("\nValeur binaire (32 bits) = ");
  //Affichage sous forme binaire avec les separations 4 4 4 8 12 - Bourrage (4 bits) Interface (4 bits/4 bits/8 bits) Id Vlan (12 bits)
  for(i=31; i >= 0; i--)  
  {  
    printf("%d",tab[i]);  
    if((i == 28 ) || (i == 24) || (i == 20) || (i == 12))
    	printf(" ");
  }  
  printf("\nBourrage (4 bits) Interface (4 bits/4 bits/8 bits) Id Vlan (12 bits)\n");
  //Calcul en décimal du membre
  int val=0;
  int j=0;
  for(i=27, j=3 ; i>23 ; i--, j--)
  {
  		val += tab[i]*pow(2, j);
  }

  printf("\nInterface : %d/", val);
  
  // Calcul en décimal /x/
  val=0;
  for(i=23, j=3 ; i>19 ; i--, j--)
  {
  		val += tab[i]*pow(2, j);
  }
  printf("%d/", val);
  
  //Calcul en décimal de l'interface physique du membre 
  val=0;
  for(i=19, j=7 ; i>11 ; i--, j--)
  {
  		val += tab[i]*pow(2, j);
  }
  printf("%d\t", val);
  
  //Calcul en décimal de l'id VLAN
  val=0;
  for(i=11, j=11 ; i>=0 ; i--, j--)
  {
  		val += tab[i]*pow(2, j);
  }
  printf("\nVLAN Id : %d\n\n", val);
  
  system("PAUSE");
  
  return 0;
}
